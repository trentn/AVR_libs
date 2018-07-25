/**
 * @brief Servo control library
 * 
 * @file servo.c
 * @author Trent Novelly
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include "servo.h"

char servo_angles[8] = {17, 17, 17, 17, 17, 17, 17, 17};
char servos = 0;


int pwm_counter = 0;

/**
 * @brief Interrupt every time the timer resets
 * 			and check if a servo output needs to be toggled
 * 
 */
ISR(TIMERn_COMPA_vect) {
        pwm_counter = (pwm_counter + 1)%200;

        pinControl(pwm_counter);
}


void initServoTimer() {
	//configure timer to Clear Timer on Compare match mode (CTC)
	//this varies depending on which timer is being used
	#if defined (__SERVO_TIMER0__)
	TCCR0A |= (1 << WGM01);
	#elif defined (__SERVO_TIMER1__)
	TCCR1B |= (1 << WGM12);
	#endif

	//prescale timer to clock/8
	TCCRnB |= (1 << CSn1);

	//enable output compare A match interrupt
	TIMSKn |= (1 << 1);

	//set output compare register to tick rate (should be 100)
	OCRnA = TICK_RATE;
	
	//ensure interrupts are enabled
	sei();
}

void registerServo(int servo_num) {
	switch(servo_num) {
		case 0: DDRB |= (1 << 0);
				break;
		case 1: DDRB |= (1 << 1);
				break;
		case 2: DDRD |= (1 << 4);
				break;
		case 3: DDRD |= (1 << 5);
				break;
		case 4: DDRD |= (1 << 6);
				break;
		case 5: DDRD |= (1 << 7);
				break;
		case 6: DDRB |= (1 << 6);
				break;
		case 7: DDRB |= (1 << 7);
				break;
		default: break;
	}
	if (servo_num >= 0 && servo_num <= 7) {
		servos |= (1 << servo_num);
	}
}

void setServoAngle(int servo, char angle) {
	//integer division should truncate to 18 discrete values
	angle = angle/10 + 8;
	
	//angle value now from 8 to 26;
	servo_angles[servo] = angle;
}

char getServoAngle(int servo) {
	//TODO: convert PWM width to degrees

	return servo_angles[servo];
}

//TODO: pwm_counter probably can be read as global variable (may need to consider race conditions)
void pinControl(int pwm_counter) {
	if(pwm_counter == 0) {
		//mask out middle bits, which represent the servos on PD pins
		char b_temp = servos & 0xc3;
		PORTB |= b_temp;

		//mask out the PB pins, and shift to account for using last 4 PD pins (and not the middle ones)
		char d_temp = (servos & 0x3c) << 2;
		PORTD |= d_temp;
	}

	//TODO: convert hardcoded values to macros (to retain optimization but increase readability)
	if((servos & 0x01) == 0x01 && pwm_counter == servo_angles[0]) {
		PORTB &= 0xfe;
	}
	if((servos & 0x02) == 0x02 && pwm_counter == servo_angles[1]) {
		PORTB &= 0xfd;
	}
	if((servos & 0x04) == 0x04 && pwm_counter == servo_angles[2]) {
		PORTD &= 0xef;
	}
	if((servos & 0x08) == 0x08 && pwm_counter == servo_angles[3]) {
		PORTD &= 0xdf;
	}
	if((servos & 0x10) == 0x10 && pwm_counter == servo_angles[4]) {
		PORTD &= 0xbf;
	}
	if((servos & 0x20) == 0x20 && pwm_counter == servo_angles[5]) {
		PORTD &= 0x7f;
	}
	if((servos & 0x40) == 0x40 && pwm_counter == servo_angles[6]) {
		PORTB &= 0xbf;
	}
	if((servos & 0x80) == 0x80 && pwm_counter == servo_angles[7]) {
		PORTB &= 0x7f;
	}
}
