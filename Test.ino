#include "Arduino.h"
#include <Audio.h>
#include <U8g2lib.h>

#include "gui.h"
#include "hardware.h"
#include "pins.h"
#include "results.h"
#include "state_mgr.h"
#include "state_title.h"
#include "stk_pitch_shift.h"


//U8G2_ST7920_128X64_F_HW_SPI u8g2(U8G2_R2, PIN_CS);
GDISPLAY u8g2(U8G2_R2, PIN_CLOCK, PIN_DATA, PIN_CS);

//TODO: add encc4
EncoderCapsule	encc1	= {Encoder(PIN_ENC1_A, PIN_ENC1_B), EncoderButton(PIN_ENC1_BTN)};
EncoderCapsule	encc2	= {Encoder(PIN_ENC2_A, PIN_ENC2_B), EncoderButton(PIN_ENC2_BTN)};
EncoderCapsule	encc3	= {Encoder(PIN_ENC3_A, PIN_ENC3_B), EncoderButton(PIN_ENC3_BTN)};
EncoderCapsule	encc4	= {Encoder(PIN_ENC4_A, PIN_ENC4_B), EncoderButton(PIN_ENC4_BTN)};

Menu *menu = new Menu(&u8g2, "-=Some Even Longer Menu=-", false);
Popup *popup = new Popup(&u8g2, "Some popup");

StateManager	stateManager(1, &encc1, &encc2, &encc3, &encc1, &u8g2);
TitleState		titleState(&stateManager);



#define FLANGE_DELAY_LENGTH (6*AUDIO_BLOCK_SAMPLES)
short delayline[FLANGE_DELAY_LENGTH];

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=148,280
StkPitchShift       ps3(4096); //xy=152,227
StkPitchShift       ps2(4096); //xy=157,180
StkPitchShift       ps1(4096);      //xy=159,126
AudioAnalyzeRMS          rms1;           //xy=355,409
AudioMixer4              mixer1;         //xy=414,199
AudioOutputI2S           i2s2;           //xy=710,194
AudioConnection          patchCord1(i2s1, 1, mixer1, 3);
AudioConnection          patchCord2(i2s1, 1, rms1, 0);

AudioConnection          patchCord30(i2s1, 1, ps3, 0);
AudioConnection          patchCord40(i2s1, 1, ps2, 0);
AudioConnection          patchCord50(i2s1, 1, ps1, 0);

AudioConnection          patchCord3(ps3, 0, mixer1, 2);
AudioConnection          patchCord4(ps2, 0, mixer1, 1);
AudioConnection          patchCord5(ps1, 0, mixer1, 0);

AudioConnection          patchCord6(mixer1, 0, i2s2, 0);
AudioConnection          patchCord7(mixer1, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=166,644
// GUItool: end automatically generated code



const int myInput = AUDIO_INPUT_LINEIN;

void setup()
{
	// Multiple purpose result/return
	result_t r;

	// Allocate audio memory
	AudioMemory(64);

	sgtl5000_1.enable();
	sgtl5000_1.inputSelect(myInput);
	sgtl5000_1.volume(0.5);


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

	ps1.shift(164.81f / 130.81f);
	ps2.shift(196.00f / 130.81f);
	ps3.shift(2.0f);


	// Init GUI
	// TODO: this should be somewhere in gui.h
	u8g2.begin();
	u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_4x6_tr);


	menu->push("THIS");
	menu->push("More Text");
	menu->push("Enum Value");
	menu->push("");
	menu->push("resonance");
	menu->push("frequency");
	menu->push("something else");
	menu->push("delay");
	r = menu->push("nothing");

	if(r != SUCCESS)
	{
		gdisp_showPopupResult(&u8g2, r, "Error?");
		u8g2.sendBuffer();

		delay(2000);
	}

	// State Managing
	r = stateManager.setState(0, &titleState);
	if(r < 0)
	{
		//TODO: error handling should use a popup feature in gui.h

		// Temporary error handling
//		u8g2.print(" give error:");
//		u8g2.setCursor(14,15);
//		u8g2.print(r);
//		u8g2.sendBuffer();
	}

	u8g2.sendBuffer();
	stateManager.setCurrentState(0);

	stateManager.setup();

	u8g2.sendBuffer();

	u8g2.setCursor(30,30);
	u8g2.print("text");
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
		r = stateManager.states[0]->onAnything();
		if(r != 0)
		{
			gdisp_showPopupResult(&u8g2, r, (r==1)?"consumed":"(?)");
		}
		else
		{
			u8g2.setCursor(0,63);
			u8g2.print("-.-");
		}
	}

	u8g2.setCursor(20,20);
	u8g2.printf("encc1: %d", encc1.c.current_read());
}

uint64_t tick = 0;
uint8_t currmode = 0;

void loop()
{
//	u8g2.clearBuffer();

//	events();

//	menu->show();
//	u8g2.setCursor(1,12);
//	u8g2.printf("count: %d", menu->count);
//
	encc1.c.read();
	encc2.c.read();
	encc3.c.read();
	encc4.c.read();
//
//	if(encc1.c.current_read())
//	{
//		gdisp_showPopupResult(&u8g2, UNIMPLEMENTED, "Unimplemented Method");
//	}


	u8g2.drawPixel(tick % 128, 64 - rms1.read() * 128);

//	float amp = rms1.read() * 32.0f;
//	if (amp > 3.0f) amp = 2.9f;
	mixer1.gain(0, 0.25f);
	mixer1.gain(1, 0.25f);
	mixer1.gain(2, 0.25f);
	mixer1.gain(3, 0.1f);

	uint8_t mode = analogRead(PIN_PEDAL)/256;
	if(currmode != mode)
	{
		currmode = mode;
		u8g2.setDrawColor(0);
		u8g2.drawBox(20,20, 80, 40);
		u8g2.setCursor(40,40);
		u8g2.setDrawColor(1);
		if(mode == 0)
		{
			u8g2.print("Chord: m/5");
			ps1.shift(155.56f / 130.81f);
			ps2.shift(185.00f / 130.81f);
		}
		else if(mode == 1)
		{
			u8g2.print("Chord: m");
			ps1.shift(155.56f / 130.81f);
			ps2.shift(196.00f / 130.81f);
		}
		else if(mode == 2)
		{
			u8g2.print("Chord: M");
			ps1.shift(164.81f / 130.81f);
			ps2.shift(196.00f / 130.81f);
		}
		else if(mode == 3)
		{
			u8g2.print("Chord: M/5");
			ps1.shift(164.81f / 130.81f);
			ps2.shift(185.00f / 130.81f);
		}
	}

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
