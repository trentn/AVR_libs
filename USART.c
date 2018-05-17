/*
 * file: USART.c
 * author: Trent Novelly
 *
 * function definitions for interfacing with the USART peripheral
 *
 */

#include <avr/io.h>
#include "USART.h"
#include <util/setbaud.h>

void initUSART(void) {
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

	#if USE_2X
	UCSR0A |= (1<<U2X0);
	#else
	UCSR0A &= ~(1<<U2X0);
	#endif

	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
}

void transmitByte(uint8_t byte) {
	while (!(UCSR0A & (1<<UDRE0))); //wait for empty transmit buffer
	UDR0 = byte;
}

char receiveByte(void) {
	while (!(UCSR0A & (1<<RXC0))); //wait to receive byte
	return UDR0;
}
