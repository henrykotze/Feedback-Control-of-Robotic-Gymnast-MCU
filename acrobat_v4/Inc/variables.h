/*
 * variables.h
 *
 *  Created on: Aug 13, 2018
 *      Author: Henry
 */

#ifndef VARIABLES_H_
#define VARIABLES_H_

#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "stm32f0xx_hal.h"
#include <math.h>

// UART COMMUNICATIONS
extern uint8_t uart_flag;			// interrupt flag
extern uint8_t* rx_buffer;			// buffer containing received string
extern uint8_t rx_byte;				// immediate received byte;
extern uint8_t* data_buffer;		// buffer containing state-space variables
extern uint8_t rx_buffer_cntr;		// counter of the rx_buffer
extern char* acrobat;				// variable to send across UART to verify UART comms
extern char* dollar;					// $: indicating each start of time-step for variables of interest
extern char* comma;					// ,: separating variables of interest in data_buffer
extern char* endSymbol;				// every sent data must end with \r\n
extern uint8_t* verification;		// varible thats sends the verification of command receive
extern uint8_t send_data_flag;		// variable that gets sets to send data across uart


//DMA for sampling potentiometer and current signal
extern uint32_t* ADC_buffer;			// buffer containing sampled values
extern uint32_t sampledCurrent;			// Sampled value of current through motor
extern uint32_t sampledPotentiometer;	// sampled value of potentiometer
extern uint8_t adc_flag;				// interrupt sets the adc_flag
extern uint16_t startval_sampledPotentiometer; // first sampled value will be 0-reference angle

// Controlling torque of motor
extern uint8_t duty_cycle;				// duty cycle of PWM signal send to motor controller IC
extern uint8_t* discrete_arctan;		// array containing discretized arctan functions
extern uint8_t motor_dir;				// direction of motor: 0 ccw, 1 cw
extern uint8_t control_state;					// determines which controller is active


extern uint8_t error_step;				// error of desired q2 position
extern uint8_t error_step_prev;			// prevision error of actual q2 position
extern uint8_t  torque;					//
extern int16_t torque_prev;


// Encoder angles
extern uint8_t encoder_1;				// encoder 1 variable
extern uint8_t encoder_2;				// encoder 2 variable
extern uint8_t enable_encoder_reading;	// enable encoder interrupts
extern uint8_t encoder_flag;			// enable interrupt to set flag
//extern float dir_increment_size; 	// increment size of each rising/falling edge of pulses

// Modes of operations
extern uint8_t simulate;				// Determines whether state variables are supplied through UART or sensors
extern uint8_t start;					// Start control system

// discretize arctan
//extern float* atan_vals;				// Discretized values of arc tan

//scratchpad variables
extern char* scratchpad;				// variable to temporary store other variables

// data aquisition flag
extern uint8_t data_flag;				// set flag to send state variables across uart
uint8_t enable_data_aquisition;			// allow data aquisition to occur

// temporary flag: PWM interrupt
extern uint8_t pwm_flag;

// state variables
//extern float q1;						// angular state variable of non-actuated pendulum
//extern float prev_q1;					// previous value of non-actuated pendulum
//extern float prevprev_q1;				// previous previous value of non-actuaded pendulum
//extern float q1dot;					// angular velocity of non-actuated pendulum
//
//extern float q2;						// angular position state variable of actuated pendulum
//extern float prev_q2;					// previous value of state variable
//extern float prevprev_q2;				// previous previous value of actuaded pendulum
//extern float q2dot;					// angular velocity of actuated pendulum
extern int16_t q2_steps;				// number of steps


extern uint32_t time;					// time keeping variable

// converted measured state variables to char format to be able to send over uart
extern char* send_q1;					// state variable of non-actuated pendulum
extern char* send_q2;					// state variable of actuated pendulum
extern char* send_torque;				// torque by motor
extern char* send_time;					// time keeping variable

// size of buffers
extern size_t size_data_buffer;			// size of data_buffer
extern size_t size_time;				// size of time variable
extern size_t size_q1;					// size of send_q1 variable
extern size_t size_q2;					// size of send_q2 variable
extern size_t size_torque;				// size of send_torque variable

extern uint8_t send_flag;				// flag that must be set before it may send new data.


#endif /* VARIABLES_H_ */
