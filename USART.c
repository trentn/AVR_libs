/*
 * file: USART.c
 * author: Trent Novelly
 *
 * function definitions for interfacing with the USART peripheral
 *
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>

#include "USART.h"
#include "utils.h"

int initUSART(int clock_speed) {

	if (clock_speed == 1) {
		UBRR0 = 6;
	}
	else if (clock_speed == 8) {
		UBRR0 = 53;
	}
	else {
		return -1;
	}
		

	//#if USE_2X
	//UCSR0A |= (1<<U2X0);
	//#else
	UCSR0A &= ~(1<<U2X0);
	//#endif

	UCSR0B |= (1<<RXCIE0);
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);

	sei();
	return 0;
}

void transmitByte(uint8_t byte) {
	while (!(UCSR0A & (1<<UDRE0))); //wait for empty transmit buffer
	UDR0 = byte;
}

char receiveByte(void) {
	while (!(UCSR0A & (1<<RXC0))); //wait to receive byte
	return UDR0;
}

void printString(char* string) {
	int len = strlen(string);
	for(int i = 0; i < len; i++) {
		transmitByte(string[i]);
	}
}
