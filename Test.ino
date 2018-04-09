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
#include "state_menu_main.h"
#include "state_mgr.h"
#include "state_title.h"
#include "stk_pitch_shift.h"
#include "value_bounded.h"

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

StateManager	stateManager(2, &encc1, &encc2, &encc3, &encc4, &u8g2);
TitleState		titleState(&stateManager);
MainMenuState	mainMenuState(&stateManager);

static Popup *gPopup;
static Plot *plot;

#define FLANGE_DELAY_LENGTH (6*AUDIO_BLOCK_SAMPLES)
short delayline[FLANGE_DELAY_LENGTH];

// GUItool: begin automatically generated code
//AudioInputI2S            i2s1;           //xy=148,280
//StkPitchShift       ps3(4096); //xy=152,227
//StkPitchShift       ps2(4096); //xy=157,180
//StkPitchShift       ps1(4096);      //xy=159,126
//AudioAnalyzeRMS          rms1;           //xy=355,409
//AudioMixer4              mixer1;         //xy=414,199
//AudioOutputI2S           i2s2;           //xy=710,194
//AudioConnection          patchCord1(i2s1, 1, mixer1, 3);
//AudioConnection          patchCord2(i2s1, 1, rms1, 0);
//
//AudioConnection          patchCord30(i2s1, 1, ps3, 0);
//AudioConnection          patchCord40(i2s1, 1, ps2, 0);
//AudioConnection          patchCord50(i2s1, 1, ps1, 0);
//
//AudioConnection          patchCord3(ps3, 0, mixer1, 2);
//AudioConnection          patchCord4(ps2, 0, mixer1, 1);
//AudioConnection          patchCord5(ps1, 0, mixer1, 0);
//
//AudioConnection          patchCord6(mixer1, 0, i2s2, 0);
//AudioConnection          patchCord7(mixer1, 0, i2s2, 1);
//AudioControlSGTL5000     sgtl5000_1;     //xy=166,644
// GUItool: end automatically generated code


static InputModule modInput(0);
static PitchShifterModule modPitchShifter(1);
static OutputModule modOutput(2);

static AudioStream **streams;
static AudioConnection **conns;
static AudioControlSGTL5000 *sgtl;

/**
 * Temporary function to emulate everything in audio
 */
void audio()
{
	AudioMemory(64);

	sgtl = new AudioControlSGTL5000();
	sgtl->enable();
	sgtl->inputSelect(AUDIO_INPUT_LINEIN);
	sgtl->volume(.5f);
	sgtl->adcHighPassFilterDisable();

	streams = new AudioStream*[4];
	modInput.spStream(&streams[0]);
	modPitchShifter.spStream(&streams[1]);
//	streams[1] = new StkPitchShift(0x1000);
	modOutput.spStream(&streams[2]);
//	streams[2] = new AudioOutputI2S();
	streams[3] = new AudioAnalyzeRMS();


	AudioStream *fUse = NULL;
	AudioStream *tUse = NULL;
	int fPort = 0;
	int tPort = 0;
	conns = new AudioConnection*[4];

	/*
	 * The following code means: "
	 *   from input, get connection at output port 0
	 *   and connect that to input port 0 of the pitch shift
	 */
	modInput.spConnOut(&streams[0], &fUse, &fPort, 0);
	modPitchShifter.spConnIn(&streams[1], &tUse, &tPort, 0);
	conns[0] = new AudioConnection(*fUse, fPort, *tUse, tPort);

	modPitchShifter.spConnOut(&streams[1], &fUse, &fPort, 0);
	modOutput.spConnIn(&streams[2], &tUse, &tPort, 0);
	conns[1] = new AudioConnection(*fUse, fPort, *tUse, tPort);

	conns[2] = new AudioConnection(*streams[0], 1, *streams[3], 0);
}

void setup()
{
	// Multiple purpose result/return
	result_t r;

	audio();


//	u8g2.begin();
//	u8g2.clearBuffer();
//	u8g2.setFont(u8g2_font_4x6_tr);

	// Allocate audio memory
//	AudioMemory(64);

//	Model model = Model(3);
//
//	model.modules[0] = &modInput;
//	model.modules[1] = &modPitchShifter;
//	model.modules[2] = &modOuput;
//
//	modInput.getOutputs()[0] = 1;
//	modPitchShifter.getInputs()[0] = 0;
//
//	modPitchShifter.getOutputs()[0] = 2;
//	modOuput.getInputs()[0] = 1;
//
//	model.bakeAudioFrom(0);


//	sgtl5000_1.enable();
//	sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
//	sgtl5000_1.volume(0.5);
//	sgtl5000_1.adcHighPassFilterDisable();
//	sgtl5000_1.write(CHIP_ANA_POWER, 0x40EF);


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


//	flange1.begin(delayline, FLANGE_DELAY_LENGTH, FLANGE_DELAY_LENGTH/4, FLANGE_DELAY_LENGTH/4, .5);
//	waveform1.begin(0.5, 130.81f, WAVEFORM_SINE);
//	waveform2.begin(0.5, 155.56f, WAVEFORM_SINE);
//	waveform3.begin(0.5, 196.00f, WAVEFORM_SINE);

//	ps1.shift(164.81f / 130.81f);
//	ps2.shift(196.00f / 130.81f);
//	ps3.shift(2.0f);


	// Init GUI
	// TODO: this should be somewhere in gui.h
	u8g2.begin();
	u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_4x6_tr);

	plot = new Plot(&u8g2, "rms", WRAP, 0.0f, 0.45f, 4, 4);
	plot->show();
	u8g2.sendBuffer();

//	menu->push("THIS");
//	menu->push("More Text");
//	menu->push("Enum Value");
//	menu->push("");
//	menu->push("resonance");
//	menu->push("frequency");
//	menu->push("something else");
//	menu->push("delay");
//	r = menu->push("nothing");
//
//	if(r != SUCCESS)
//	{
//		gdisp_showPopupResult(&u8g2, r, "Error?");
//		u8g2.sendBuffer();
//
//		delay(2000);
//	}

//	// State Managing
//	r = stateManager.setState(0, &titleState);
//	if(r < 0)
//	{
//		gdisp_showPopupResult(&u8g2, r, "Could not load title!");
//		delay(1000);
//	}
//
//	r = stateManager.setState(1, &mainMenuState);
//	if(r < 0)
//	{
//		gdisp_showPopupResult(&u8g2, r, "Could not load main menu!");
//		delay(1000);
//	}
//
//	stateManager.setCurrentState(0);
//	u8g2.sendBuffer();
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
uint8_t currmode = 0;

void loop()
{
//	u8g2.clearBuffer();

//	events();
//	stateManager.loop();

//	menu->show();
//	u8g2.setCursor(1,12);
//	u8g2.printf("count: %d", menu->count);
//
//	encc1.c.read();
//	encc2.c.read();
//	encc3.c.read();
//	encc4.c.read();
//
//	if(encc1.c.current_read())
//	{
//		gdisp_showPopupResult(&u8g2, UNIMPLEMENTED, "Unimplemented Method");
//	}


	AudioAnalyzeRMS *rms = (AudioAnalyzeRMS *) streams[3];
	plot->put(tick % 124, rms->read());
//	u8g2.drawPixel(tick % 128, 64 - rms->read() * 128);

////	float amp = rms1.read() * 32.0f;
////	if (amp > 3.0f) amp = 2.9f;
//	mixer1.gain(0, 0.25f);
//	mixer1.gain(1, 0.25f);
//	mixer1.gain(2, 0.25f);
//	mixer1.gain(3, 0.25f);
//
//	uint8_t mode = analogRead(PIN_PEDAL)/200;
//	if(currmode != mode)
//	{
//		currmode = mode;
//		u8g2.setDrawColor(0);
//		u8g2.drawBox(20,20, 80, 40);
//		u8g2.setCursor(40,40);
//		u8g2.setDrawColor(1);
//		if(mode == 1)
//		{
//			u8g2.print("Chord: m/5");
//			ps1.shift(155.56f / 130.81f);
//			ps2.shift(185.00f / 130.81f);
//		}
//		else if(mode == 2)
//		{
//			u8g2.print("Chord: m");
//			ps1.shift(155.56f / 130.81f);
//			ps2.shift(196.00f / 130.81f);
//		}
//		else if(mode == 3)
//		{
//			u8g2.print("Chord: M");
//			ps1.shift(164.81f / 130.81f);
//			ps2.shift(196.00f / 130.81f);
//		}
//		else if(mode == 4)
//		{
//			u8g2.print("Chord: M/5");
//			ps1.shift(164.81f / 130.81f);
//			ps2.shift(185.00f / 130.81f);
//		}
//		else
//		{
//			u8g2.print("Chord: ----");
//			ps1.shift(1.0f);
//			ps2.shift(1.0f);
//			ps3.shift(1.0f);
//		}
//	}

//	waveform1.frequency(55.0f + 400.0f * analogRead(PIN_PEDAL)/1024.0f);
//	waveform1.amplitude(rms1.read() * 8.0f);

//	pitchShifter1.shift(1.0f + 0.5f * analogRead(PIN_PEDAL)/1024.0f);

//	u8g2.setCursor(1,12);
//	u8g2.printf("rot1: %d ; %d", encc1.r.read(), encc1.c.current_read());
//	u8g2.setCursor(1,18);
//	u8g2.printf("rot2: %d ; %d", encc2.r.read(), encc2.c.current_read());
//	u8g2.setCursor(1,24);
//	u8g2.printf("rot3: %d ; %d", encc3.r.read(), encc3.c.current_read());
//	u8g2.setCursor(1,30);
//	u8g2.printf("rot4: %d ; %d", encc4.r.read(), encc4.c.current_read());
//
//	u8g2.setCursor(1,36);
//	u8g2.printf("switch: %d", digitalRead(PIN_SWITCH));
//
//	u8g2.setCursor(1,42);
//	u8g2.printf("pedal: %d", analogRead(PIN_PEDAL));


	u8g2.sendBuffer();
//
//	stateManager.loop();

	tick ++;
}
