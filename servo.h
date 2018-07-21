/**
 * @brief header file for servo functions
 * 
 * @file servo.h
 * @author Trent Novelly
 */
#ifndef SERVO_H
#define SERVO_H

#if defined(__SERVO_TIMER0__)

#   define TCCRnB TCCR0B
#   define TIMSKn TIMSK0
#   define OCRnA  OCR0A
#   define CSn1   CS01
#   define TIMERn_COMPA_vect TIMER0_COMPA_vect

#elif defined (__SERVO_TIMER1__)

#   define TCCRnB TCCR1B
#   define TIMSKn TIMSK1
#   define OCRnA  OCR1A
#   define CSn1   CS11
#   define TIMERn_COMPA_vect TIMER1_COMPA_vect

#endif


/**
 * @brief Number of clock ticks to reset timer
 * 
 */
#define TICK_RATE 100

/**
 * @brief Initialize the timer to count at a 
 * 			rate of 500 kHz (clock tick time 1 microsecond)
 * 			The timer should reset after 100 microseconds
 * 
 */
void initServoTimer(void);

/**
 * @brief Registers that a servo signal wire is connected
 * 			and enables the appropriate pin as output
 * 
 * @param pin PORTB pin that the servo signal is connected to
 */
void registerServo(int pin);

/**
 * @brief Set the Servo Angle
 * 
 * @param servo is the desired servo to set
 * @param angle is the angle to set the desired servo to
 */
void setServoAngle(int servo, char angle);

/**
 * @brief Get the Servo Angle
 * 
 * @param servo is the desired servo angle to read
 * @return char is the servo angle (in pulse width time/100)
 */
char getServoAngle(int servo);

/**
 * @brief sets all servo outputs when the counter is 0
 * 			and unsets any servo output whose pwm "angle"
 * 			is equal to the counter
 * 
 * @param pwm_counter is the current counter value.
 */

void pinControl(int pwm_counter);


#endif