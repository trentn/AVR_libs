/*
 * file: ADC.c
 * author: Trent Novelly
 *
 * definitions of functions in ADC.h
 */

#include <avr/io.h>



void initADC() {
	
	ADMUX &= ~0x0f;		//MUXn bits 0-3;
	ADMUX |= (1 << 5);	//ADLAR is bit 5
	ADMUX |= (1 << 6);	//refernce voltage
	ADMUX &= ~(1 << 7);



	ADCSRB &= ~0x07;	//Free running mode

	ADCSRA |= (1 << 7); 	//ADC enable bit
	ADCSRA |= (1 << 5);	//ADC auto trigger enable

	ADCSRA |= 0x03;		//setting prescaler
	ADCSRA &= ~(1 << 2);	//setting prescaler
	ADCSRA |= (1 << 6);	//start first conversion
}
