/*
 * file: USART.h
 * author: Trent Novelly
 *
 * function prototypes for interfacing with the USART peripheral
 *
 */


/*
 * initUSART: initializes the USART peripheral
 */
void initUSART(void);

/*
 * transmitByte: sends a byte via the USART peripheral
 */
void transmitByte(uint8_t byte);

/*
 * receiveByte: returns a byte receieved by the USART peripheral
 */
char receiveByte(void);

/*
 * printString: transmits each byte in a string
 */
void printString(char* string);
