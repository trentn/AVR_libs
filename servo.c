#include <avr/io.h>
#include <avr/interrupt.h>
#include "servo.h"

#define TICK_RATE 100

char servo_angles[8] = {17, 17, 17, 17, 17, 17, 17, 17};
char servos = 0;


int pwm_counter = 0;
ISR(TIMER1_COMPA_vect) {
        pwm_counter = (pwm_counter + 1)%200;

        pinControl(pwm_counter);
}

void initServoTimer() {
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS11);
	TIMSK1 |= (1 << 1);

	OCR1A = TICK_RATE;
	sei();
}

void registerServo(int pin) {
	DDRB |= (1 << pin);
	servos |= (1 << pin);
}

void setServoAngle(int servo, char angle) {
	//integer division should truncate to 18 discrete values
	angle = angle/10 + 8;
	
	//angle value now from 8 to 26;
	servo_angles[servo] = angle;
}

char getServoAngle(int servo) {
	return servo_angles[servo];
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
