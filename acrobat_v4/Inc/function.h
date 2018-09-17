/*
 * functions.h
 *
 *  Created on: Aug 13, 2018
 *      Author: Henry
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

void data_aquisition(); 			//	send data across UART
void user_main();					//	main loop
void uart_request();				//	respond to request across UART
void init_variables();				//	initialize variables with initial conditions
void get_current_potentiometer();	//	get current through motor and angle of non-actuated pendulum
void startPeripherals();			//	start peripherals of micro-controller
void torque_output();				// 	Determine the required torque to be outputted
void discretize_arctan();			// approximate arctan function using discrete number of quantities
void read_motor_position();			// get new position of actuated pendulum

#endif /* FUNCTION_H_ */
