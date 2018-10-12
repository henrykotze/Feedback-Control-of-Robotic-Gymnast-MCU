/*
 * user_main.c
 *
 *  Created on: Aug 13, 2018
 *      Author: Henry
 */

#include "function.h"
#include "variables.h"

extern UART_HandleTypeDef huart1;
extern TIM_HandleTypeDef htim14;
void user_main(){

	if(uart_flag == 1){
		uart_flag = 0;
		uart_request();

	}


	if(encoder_flag == 1){
		encoder_flag = 0;
		read_motor_position();
	}


	if(adc_flag == 1){
		adc_flag = 0;
		get_current_potentiometer();
	}


	if(enable_data_aquisition){
		if(data_flag == 1){ // send system variables over UART
			time += 1;
			sprintf(send_time,"%lu", time);
			data_flag = 0;
			data_aquisition();
		}
	}

	if(send_data_flag && enable_data_aquisition && receive_send){
		send_data_flag = 0;
		HAL_UART_Transmit_DMA(&huart1, ((uint8_t*)data_buffer),strlen((char*)data_buffer));
		receive_send = 0;
	}

//	time = htim14.Instance->CNT;


}

