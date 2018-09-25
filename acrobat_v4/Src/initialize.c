/*
 * initialize.c
 *
 *  Created on: Aug 13, 2018
 *      Author: Henry
 */

#include "function.h"
#include "variables.h"

extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim14;
extern TIM_HandleTypeDef htim16;

void startPeripherals(){

	HAL_ADCEx_Calibration_Start(&hadc);					// Calibrate the ADC
	HAL_ADC_Start_DMA(&hadc, ADC_buffer, 2);			// Start to capture the ADC with DMA

	HAL_TIM_Base_Start_IT(&htim14);						// Timer responsible for time-keeping and triggers system state to be send
	HAL_TIM_Base_Start_IT(&htim16);						// Timer responsible for time-keeping and triggers system state to be send
	HAL_TIM_PWM_Start_IT(&htim3,TIM_CHANNEL_2);			// Start the Timer Module with PWM
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);	// Set duty cycle of PWM signal to 0%
	HAL_UART_Receive_IT(&huart1, &rx_byte, 1);			// Set interrupt to receive byte over UART


//	HAL_Delay(500);										// Delay for peripherals to settle
	HAL_GPIO_WritePin(DEBUG_LED1_GPIO_Port,DEBUG_LED1_Pin,1); // LED ON indicates system is ready

	//startval_sampledPotentiometer = ADC_buffer[1];

}


void init_variables(){

	rx_buffer = (uint8_t*)malloc(8*sizeof(uint8_t));
	memset(rx_buffer,0x00,8);

	verification = (uint8_t*)malloc(8*sizeof(uint8_t));
	memset(verification,0x00,8);

	// might to be larger to account for decimals
	data_buffer = (uint8_t*)malloc(72*sizeof(uint8_t));
	memset(data_buffer,0x00,72);

	// forming dat structure to be send
	memcpy(data_buffer, dollar, strlen((char*)dollar));


	ADC_buffer = (uint32_t*)malloc(2*sizeof(uint32_t));
	memset(ADC_buffer,0x00,2);

	atan_vals = (double*)malloc(100*sizeof(double));
	memset(atan_vals,0x00,100);

	scratchpad = (char*)malloc(5*sizeof(char));
	memset(scratchpad,0x00,5);

	send_q1 = (char*)malloc(10*sizeof(char));
	memset(send_q1,0x00,10);
	send_q2 = (char*)malloc(32*sizeof(char));
	memset(send_q2,0x00,32);
	send_torque = (char*)malloc(4*sizeof(char));
	memset(send_torque,0x00,4);
	send_time = (char*)malloc(4*sizeof(char));
	memset(send_time,0x00,4);


	sprintf(send_q2,"%d", q2_steps);

	// temporary, this should be done where the variables are measured

}

void discretize_arctan(){
	for(int i = 0; i < 100; i++){
		atan_vals[i] = atan(i/100);
	}
}

