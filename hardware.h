/*
 * hardware.h
 *
 *  Created on: Mar 31, 2018
 *      Author: MisterCavespider
 */

#ifndef HARDWARE_H_
#define HARDWARE_H_


#include <Arduino.h>
#include <Encoder.h>
#include <stdint.h>

#define ROTARY_CORRECTION(v)	v/4

#define ENC_PRESSEDV(enc)		enc.c.delta_read()
#define ENC_PRESSED(enc)		enc->c.delta_read()

#define	ENC_READV(enc)			enc.r.read()
#define ENC_READ(enc)			enc->r.read()
#define ENC_WRITEV(enc,v)		enc.r.write(v)
#define ENC_WRITE(enc,v)		enc->r.write(v)

/**
 * A button for when an encoder is pressed.
 * Stores current value, last value, and difference.
 * Everything is read and calculated at read().
 */
class EncoderButton
{
public:
	EncoderButton(uint8_t pin);
	void	read();
	uint8_t	current_read();
	uint8_t	last_read();
	int8_t	delta_read();
private:
	uint8_t pin;
	uint8_t curr, last, delta;
};

/**
 * Combines Teensy's rotary encoders
 * with custom click encoders.
 */
typedef struct EncoderCapsule
{
	/* 'Rotate' */
	Encoder			r;
	/* 'Click' */
	EncoderButton	c;
} EncoderCapsule;

#endif /* HARDWARE_H_ */
