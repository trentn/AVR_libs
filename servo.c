#include <avr/io.h>
#include <avr/interrupt.h>
#include "servo.h"

char servo_angles[8] = {7, 7, 7, 7, 7, 7, 7 ,7};
char servos = 0;

void initServoTimer(int tick_rate) {
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS11);
	TIMSK1 |= (1 << 1);

	OCR1A = tick_rate;
	sei();
}

void registerServo(int pin) {
	DDRB |= (1 << pin);
	servos |= (1 << pin);
}

void setServoAngle(int servo, char angle) {
	servo_angles[servo] = angle; //angle value from 7 to 27;
}

void pinControl(int pwm_counter) {
	if(pwm_counter == 0) {
		PORTB = servos;
	}

	if((servos & 0x01) == 0x01 && pwm_counter == servo_angles[0]) {
		PORTB &= 0xfe;
	}
	if((servos & 0x02) == 0x02 && pwm_counter == servo_angles[1]) {
		PORTB &= 0xfd;
	}
	if((servos & 0x04) == 0x04 && pwm_counter == servo_angles[2]) {
		PORTB &= 0xfb;
	}
	if((servos & 0x08) == 0x08 && pwm_counter == servo_angles[3]) {
		PORTB &= 0xf7;
	}
	if((servos & 0x10) == 0x10 && pwm_counter == servo_angles[4]) {
		PORTB &= 0xef;
	}
	if((servos & 0x20) == 0x20 && pwm_counter == servo_angles[5]) {
		PORTB &= 0xdf;
	}
	if((servos & 0x40) == 0x40 && pwm_counter == servo_angles[6]) {
		PORTB &= 0xbf;
	}
	if((servos & 0x80) == 0x80 && pwm_counter == servo_angles[7]) {
		PORTB &= 0x7f;
	}
}
