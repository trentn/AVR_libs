/*
 * file: ADC.c
 * author: Trent Novelly
 *
 * definitions of functions in ADC.h
 */

#include <avr/io.h>


int initADC(int pin) {
	if(pin > 5) {
		return -1;
	}	

	ADMUX &= ~0x0f;		//MUXn bits 0-3
	ADMUX |= pin;		//set pin

	ADMUX |= (1 << 5);	//ADLAR is bit 5


	//set reference voltage to AVcc
	ADMUX |= (1 << 6);
	ADMUX &= ~(1 << 7);


	ADCSRB &= ~0x07;	//Free running mode

	ADCSRA |= (1 << 7); 	//ADC enable bit
	ADCSRA |= (1 << 5);	//ADC auto trigger enable

	ADCSRA |= 0x03;		//setting prescaler
	ADCSRA &= ~(1 << 2);	//setting prescaler
	ADCSRA |= (1 << 6);	//start first conversion
}

int getConversion(void) {
	return (int)ADCH;
}
