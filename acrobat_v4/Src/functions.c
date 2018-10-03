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
	error_step_prev = q2_steps;

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

/*Creates a discrete representation of the arctan function. The
 * discrete value is contained in a array
 */


void control_law(){

//	sin_q1_q2 = sin(q1+q2);
//	sin_q2 = sin(q2);
//	cos_q2 = cos(q2);
//	sin_q1 = sin(q1);
//
//	torque_controller = a*q2dot - a*q1dot + (b*sin_q1_q2) + (c*q1dot*q1dot*sin_q2) + (((d*cos_q2) + e)*((d*cos_q2) + e)/((f*cos_q2) + g) - h)*(58*q2 + (127*q2dot)/10 - (29*PI*atan(q1dot))/5) - (((i*cos_q2) + j)*((k*q1dot) + (l*sin_q1_q2) + (m*sin_q1) - (n*q2dot*q2dot*sin_q2) - (p*q1dot*q2dot*sin_q2)))/((q*cos_q2) + r);





//

}


void output_torque(uint8_t dir, uint8_t duty_cycle){
	if(duty_cycle > 30){ // safety percaustion to ensure safety
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 100 ); // stop motor

	}
	else{
		HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port,MOTOR_DIR_Pin,dir);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, duty_cycle );
	}




}
