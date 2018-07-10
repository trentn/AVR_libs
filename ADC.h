/*
 * file: ADC.h
 * author: Trent Novelly
 *
 * function prototypes for interfacing with the ADC
 *
 */

#ifndef ADC_HEADER
#define ADC_HEADER
/*
 * initADC: configures the ADC peripheral
 * 8 bit resolution
 */
int initADC(int pin);

/*
 * getConversion: returns the value currently
 * 	in the conversion register ADCH
 */
int getConversion(void);

#endif
