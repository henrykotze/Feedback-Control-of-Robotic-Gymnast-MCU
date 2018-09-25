/*
 * uart_comms.c
 *
 *  Created on: Aug 13, 2018
 *      Author: Henry
 */

#include "function.h"
#include "variables.h"
extern UART_HandleTypeDef huart1;
extern TIM_HandleTypeDef htim3;

void data_aquisition(){
	size_data_buffer = strlen((char*)data_buffer);
	size_time = strlen((char*)send_time);
	size_q1 = strlen((char*)send_q1);
	size_q2 = strlen((char*)send_q2);
	size_torque = strlen((char*)send_torque);

	//memset(data_buffer,0x00,40);
	memcpy(data_buffer+size_data_buffer, send_time, size_time);
	memcpy(data_buffer+size_time+size_data_buffer, comma, 1);
	memcpy(data_buffer+1+size_time+size_data_buffer, send_q1, size_q1);
	memcpy(data_buffer+1+size_q1+size_time+size_data_buffer, comma, 1);
	memcpy(data_buffer+2+size_q1+size_time+size_data_buffer, send_q2, size_q2);
	memcpy(data_buffer+2+size_q1+size_time+size_q2+size_data_buffer, comma, 1);
	memcpy(data_buffer+3+size_q1+size_time+size_q2+size_data_buffer, send_torque, size_torque);
	memcpy(data_buffer+3+size_q1+size_time+size_q2+size_torque+size_data_buffer, endSymbol, 1);

//	HAL_UART_Transmit_DMA(&huart1, ((uint8_t*)data_buffer),strlen((char*)data_buffer));
}


void uart_request(){

	rx_buffer[rx_buffer_cntr] = rx_byte;
	if(*rx_buffer == '$'){
		rx_buffer_cntr += 1;
	}
	if(rx_buffer_cntr > 10){
		rx_buffer_cntr = 0;
	}
	if(rx_buffer[0] == '$' && rx_buffer[rx_buffer_cntr-1] == '\n' && rx_buffer_cntr > 2){

		switch(rx_buffer[1]){
		case 'X':	// stop all operation
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
			enable_data_aquisition = 0;
			enable_encoder_reading = 0;
			enable_ADC_interrupt = 0;
			HAL_UART_Transmit_IT(&huart1, ((uint8_t*)rx_buffer),strlen((char*)rx_buffer));
			break;

		case 'A':	// verifying UART comms is working
			HAL_UART_Transmit_IT(&huart1, ((uint8_t*)acrobat),strlen((char*)acrobat));
			break;

		case 'B':	// enable data aquisition to occur
			if(*(rx_buffer+3) == '1'){
				HAL_UART_Transmit_IT(&huart1, ((uint8_t*)rx_buffer),strlen((char*)rx_buffer));
				enable_data_aquisition = 1;
			}
			else if(rx_buffer[3] == '0'){
				enable_data_aquisition = 0;
			}
			break;

		case 'C':	// send q1 values back
			if(*(rx_buffer+3) == '1'){
			}
			else if(*(rx_buffer+3) == '0'){

			}

			break;

		case 'D':	// Enable Control system to compute output torque
			if(rx_buffer[2] == 1){
				start = 1;
			}
			else if(rx_buffer[2] == 0){
				start = 0;
			}
			break;

		case 'F':	// Changing the duty-cycle output or control speed of motor
//			data_buffer = rx_buffer;
			memcpy(scratchpad, rx_buffer+3, strlen((char*)rx_buffer)-4);

			output_torque(motor_dir, duty_cycle);
			//duty_cycle = (uint8_t)strtol(scratchpad, (char**)NULL,10);
			//__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, duty_cycle);


			HAL_UART_Transmit_IT(&huart1, ((uint8_t*)rx_buffer),strlen((char*)rx_buffer));
			break;

		case 'G': //Enable interrupts for encoder pulses
			if(rx_buffer[3] == 1){
				enable_encoder_reading = 1;
			}
			else if(rx_buffer[3] == 0){
				enable_encoder_reading = 0;
			}
			break;

		case 'H': //Enable interrupts for ADC
			if(rx_buffer[3] == '1'){
				enable_ADC_interrupt = 1;
			}
			else if(rx_buffer[3] == '0'){
				enable_ADC_interrupt = 0;
			}
			break;

		case 'I': // Change direction of motor
			if(rx_buffer[3] == '1'){
				motor_dir = 1;
				output_torque(motor_dir, duty_cycle);
			}
			else if(rx_buffer[3] == '0'){
				motor_dir = 0;
				output_torque(motor_dir, duty_cycle);
			}
			HAL_UART_Transmit_IT(&huart1, ((uint8_t*)rx_buffer),strlen((char*)rx_buffer));

			break;


		}

	}

	HAL_UART_Receive_IT(&huart1, &rx_byte, 1);


}



