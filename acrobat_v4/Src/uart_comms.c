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
		rx_buffer_copy = rx_buffer;
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
				receive_send = 1;
			}
			else if(rx_buffer[3] == '0'){
				enable_data_aquisition = 0;
			}
			break;

		case 'T':
			torque_received = strtok((char*)rx_buffer_copy, "$T,");
			motor_dir = (strtok(NULL, ",\r\n"));

			//controller_torque = 100 - ( ( (float)torque_received)/100+312.52f)/15.828f;
			//output_torque(motor_dir,controller_torque);
			receive_send = 1;
			break;
//
//		case 'F':	// Changing the duty-cycle output or control speed of motor
////			data_buffer = rx_buffer;
//			memcpy(scratchpad, rx_buffer+3, strlen((char*)rx_buffer)-4);
//
//			//output_torque(motor_dir, duty_cycle);
//			duty_cycle = (uint8_t)strtol(scratchpad, (char**)NULL,10);
//			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, duty_cycle);
//
//
//			HAL_UART_Transmit_IT(&huart1, ((uint8_t*)rx_buffer),strlen((char*)rx_buffer));
//			break;
//
//		case 'I': // Change direction of motor
//			if(rx_buffer[3] == '1'){
//				motor_dir = 1;
//				output_torque(motor_dir, duty_cycle);
//			}
//			else if(rx_buffer[3] == '0'){
//				motor_dir = 0;
//				output_torque(motor_dir, duty_cycle);
//			}
//			HAL_UART_Transmit_IT(&huart1, ((uint8_t*)rx_buffer),strlen((char*)rx_buffer));
//
//			break;

			//memset(rx_buffer,0x00, 16);
			//memset(rx_buffer_copy,0x00, 16);

		}
		rx_buffer_cntr = 0;
	}
	HAL_UART_Receive_IT(&huart1, &rx_byte, 1);


}



