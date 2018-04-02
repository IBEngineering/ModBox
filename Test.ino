#include "Arduino.h"
#include <Audio.h>
#include <U8g2lib.h>

#include "gui.h"
#include "hardware.h"
#include "pins.h"
#include "results.h"
#include "state_mgr.h"
#include "state_title.h"


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

void loop()
{
	u8g2.clearBuffer();

//	events();

	menu->show();
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
}
