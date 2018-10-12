/*
 * functions.c
 *
 *  Created on: Aug 13, 2018
 *      Author: Henry
 */

#include "variables.h"
extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim14;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;


#define max_torque
#define KP
#define KI


// interrupt when byte is received on UART
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	uart_flag = 1;
}

//interrupt when encoder is experiencing an rising or falling edge
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	encoder_flag = 1;

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

	if(htim->Instance == htim16.Instance){
		send_data_flag = 1;
	}
	else if(htim->Instance == htim14.Instance){
		adc_flag = 1;
		data_flag = 1;
	}
//	data_flag = 1;
//	adc_flag = 1;
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim){
	// check what timer counter it is before setting flag
	pwm_flag = 1;
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	pwm_flag = 1;
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim){
	pwm_flag = 1;
}

void HAL_UART_TxCpltCallback (UART_HandleTypeDef *huart){
	memset(rx_buffer,0x00, 8);
	rx_buffer_cntr = 0;
	memset(data_buffer,0x00,40);
}


void read_motor_position(){

	prevprev_q2 = prev_q2;
	prev_q2 = q2;

	if(HAL_GPIO_ReadPin(DIR_GPIO_Port, DIR_Pin) == 1){ // actuated pendulum is turning clockwise
		q2_steps -= 1;
		q2 = q2_steps*dir_increment_size;
	}
	else{ // actuated pendulum is turning anti-clockwise
		q2_steps += 1;
		q2 = q2_steps*dir_increment_size;
	}
	sprintf(send_q2,"%d", q2_steps);

	//three point backward difference
//	q2dot = (prevprev_q2 - prev_q2<<2+3*q2)/(2*time); // time variable needs to change

}

void output_torque(uint8_t dir, uint8_t duty_cycle){
	if(duty_cycle < 30){ // safety percaustion to ensure safety
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 100 ); // stop motor

	}
	else{
		HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port,MOTOR_DIR_Pin,dir);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, duty_cycle );
	}
}

void control_law(){
//	if in the non-linear control region
//	q2dot = (prevprev_q2 - prev_q2*4+3*q2)/(2*time_del);
//	q1dot = (prevprev_q1 - prev_q1*4+3*q1)/(2*time_del);
////	time_del = htim14.Instance->CNT;
//	cos_q2 = cos(q2);
//	sin_q2 = sin(q2);
//	sin_q1_q2 = sin(q1+q2);
//
//	controller_torque = a*q2dot - a*q1dot + b*sin_q1_q2 + c*(q1dot*q1dot)*sin_q2 + \
//	((d*((cos_q2 + e)*(cos_q2 + e)))/(f*cos_q2 + g) - h)*(i*q2 + j*q2dot - k*atan(q1dot)) - \
//	(1.0*(l*cos_q2 + m)*(-n*sin_q2*(q2dot*q2dot) - o*q1dot*sin_q2*q2dot + p*sin_q1_q2 \
//	+ q*(float)sin(q1) + r))/(s*cos_q2 + t);
//
//	if(controller_torque > 0){
//		motor_dir = 1;
//	}
//	else {
//		motor_dir = 0;
//	}
//	output_torque(motor_dir, 100 -(controller_torque+312.52)/15.828);



// if we are in the null controllability region



}


