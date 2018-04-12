#include "Arduino.h"
#include <Audio.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "gui.h"
#include "hardware.h"
#include "model_model.h"
#include "pins.h"
#include "results.h"
#include "state_graph.h"
#include "state_menu_main.h"
#include "state_mgr.h"
#include "state_title.h"
#include "stk_pitch_shift.h"
#include "value_bounded.h"

#include "modules/chorus.h"
#include "modules/input.h"
#include "modules/pitch_shifter.h"
#include "modules/output.h"


//U8G2_ST7920_128X64_F_HW_SPI u8g2(U8G2_R2, PIN_CS);
GDISPLAY u8g2(U8G2_R2, PIN_CLOCK, PIN_DATA, PIN_CS);

//TODO: add encc4
EncoderCapsule	encc1	= {Encoder(PIN_ENC1_A, PIN_ENC1_B), EncoderButton(PIN_ENC1_BTN)};
EncoderCapsule	encc2	= {Encoder(PIN_ENC2_A, PIN_ENC2_B), EncoderButton(PIN_ENC2_BTN)};
EncoderCapsule	encc3	= {Encoder(PIN_ENC3_A, PIN_ENC3_B), EncoderButton(PIN_ENC3_BTN)};
EncoderCapsule	encc4	= {Encoder(PIN_ENC4_A, PIN_ENC4_B), EncoderButton(PIN_ENC4_BTN)};

static Model model(4);

static InputModule modInput(1);
//static PitchShifterModule modPitchShifter(1);
static ChorusModule modChorus(2);
static OutputModule modOutput(3);

StateManager	stateManager(3, &encc1, &encc2, &encc3, &encc4, &u8g2);
TitleState		titleState(&stateManager);
MainMenuState	mainMenuState(&stateManager);
GraphState		graphState(&stateManager, "Tuner", &model);

#define FLANGE_DELAY_LENGTH (6*AUDIO_BLOCK_SAMPLES)
short delayline[FLANGE_DELAY_LENGTH];

/**
 * Now this function starts all audio
 */
void audio()
{
	AudioMemory(64);

//	sgtl = new AudioControlSGTL5000();

	model.modules[0] = &modInput;
	model.modules[1] = &modChorus;
	model.modules[2] = &modOutput;

	u8g2.setCursor(0,6);
	u8g2.print("1");
	u8g2.sendBuffer();

	modInput.getOutputs()[0] = 2;
	modChorus.getInputs()[0] = 1;
	modChorus.getOutputs()[0] = 3;
	modOutput.getInputs()[0] = 2;

	u8g2.setCursor(0,12);
	u8g2.print("2");
	u8g2.sendBuffer();

	result_t r = model.bakeAudioFrom(1);
	if(r != SUCCESS)	gdisp_showPopupResult(&u8g2, r, "Something's bad");
}

void setup()
{
	// Multiple purpose result/return
	result_t r;


	SPI.setSCK(PIN_CLOCK);
	SPI.setMOSI(PIN_DATA);
	SPI.setCS(PIN_CS);
//	SPI.setClockDivider(SPI_CLOCK_DIV128);


	//Set as inputs
	pinMode(PIN_ENC1_BTN, INPUT);
	pinMode(PIN_ENC2_BTN, INPUT);
	pinMode(PIN_ENC3_BTN, INPUT);
	pinMode(PIN_ENC4_BTN, INPUT);
	pinMode(PIN_SWITCH, INPUT);

	//Enable pullups on buttons
	digitalWrite(PIN_ENC1_BTN, HIGH);
	digitalWrite(PIN_ENC2_BTN, HIGH);
	digitalWrite(PIN_ENC3_BTN, HIGH);
	digitalWrite(PIN_ENC4_BTN, HIGH);
	digitalWrite(PIN_SWITCH, HIGH);


	// Init GUI
	// TODO: this should be somewhere in gui.h
	u8g2.begin();
	u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_4x6_tr);


	// Init Audio
	audio();


	// State Managing
	r = stateManager.setState(0, &titleState);
	if(r < 0)
	{
		gdisp_showPopupResult(&u8g2, r, "Could not load title!");
	}

	r = stateManager.setState(1, &mainMenuState);
	if(r < 0)
	{
		gdisp_showPopupResult(&u8g2, r, "Could not load main menu!");
	}

	r = stateManager.setState(2, &graphState);
	if(r < 0)
	{
		gdisp_showPopupResult(&u8g2, r, "Could not load graph!");
	}

	stateManager.setCurrentState(0);
	u8g2.sendBuffer();
}

void events()
{
	result_t r;

	encc1.c.read();
	encc2.c.read();
	encc3.c.read();
	encc4.c.read();

	if(encc1.c.current_read())
	{
		r = stateManager.onAnything();
		if(r == EVENT_IGNORED)
		{
			r = stateManager.onConfirm(0b00000000);
		}
	}

	if(encc2.c.current_read())
	{
		r = stateManager.onAnything();
		if(r == EVENT_IGNORED)
		{
			r = stateManager.onConfirm(0b00000001);
		}
	}

	int32_t v;

	// TODO: determine these flags
	// FIXME: use flags

	v = ROTARY_CORRECTION(encc1.r.read());
	if(v)
	{
		if(stateManager.onAnything() == EVENT_IGNORED)
		{
			stateManager.onScrollPri(0b00000000, v);
		}
		encc1.r.write(0);
	}

	v = ROTARY_CORRECTION(encc2.r.read());
	if(v)
	{
		if(stateManager.onAnything() == EVENT_IGNORED)
		{
			stateManager.onScrollPri(0b00000001, v);
		}
		encc2.r.write(0);
	}

	v = ROTARY_CORRECTION(encc3.r.read());
	if(v)
	{
		if(stateManager.onAnything() == EVENT_IGNORED)
		{
			stateManager.onScrollSec(0b00000000, v);
		}
		encc3.r.write(0);
	}

	v = ROTARY_CORRECTION(encc4.r.read());
	if(v)
	{
		if(stateManager.onAnything() == EVENT_IGNORED)
		{
			stateManager.onScrollSec(0b00000001, v);
		}
		encc4.r.write(0);
	}
}

uint64_t tick = 0;

void loop()
{
	events();
	stateManager.loop();

	u8g2.sendBuffer();

	tick ++;
}
