#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2018-04-02 17:38:10

#include "Arduino.h"
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
extern U8G2_ST7920_128X64_F_SW_SPI u8g2;
extern EncoderCapsule encc1;
extern EncoderCapsule encc2;
extern EncoderCapsule encc3;
extern EncoderCapsule encc4;
extern Menu* menu;
extern Popup* popup;
extern StateManager stateManager;
extern TitleState titleState;
#define FLANGE_DELAY_LENGTH (6*AUDIO_BLOCK_SAMPLES)
extern short delayline[];
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

void setup() ;
void events() ;
void loop() ;


#include "Test.ino"

#endif
