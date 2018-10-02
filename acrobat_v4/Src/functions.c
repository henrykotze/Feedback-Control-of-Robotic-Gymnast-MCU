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
//	if in the non-linear control region









	if( (q1 < PI*0.3 || q1 < -PI*0.3 ) && control_state == 0){
		control_state = 1;
		alpha = PI/6;
	}
	else if( (q1 < PI*0.3 || q1 < -PI*0.3 ) && control_state == 1 ){
		control_state = 2;
		alpha = PI/6;
	}
	else if(  ( q1 > (PI-region_1) || q1 < (-PI+region_1) ) && (q2 < region_2 && q2 > -region_2) && control_state == 2){
		control_state = 3;
	}

	if(control_state == 0){ 			// swing-up controller

	}
	else if(control_state == 1){ 		// swing-up controller

	}
	else if(control_state == 2){ 		// balancing controller

	}


// if we are in the null controllability region


// System Identification test

//	"DB3".Unow := "DB3".kp * "DB3".Enow - "DB3".kp * "DB3".Eprev + "DB3".ki / (2 /
//	"DB3".Ts) * "DB3".Enow + "DB3".ki / (2 / "DB3".Ts) * "DB3".Eprev + "DB3".Uprev;


//
//	if(q2 > 0.f){
//		compensate = 1;
//		torque_prev = output_torque;
////		output_torque = 2*(q2_steps - error_step_prev) + (q2_steps + error_step_prev) + torque_prev;
//
//		if(50*(q2 - prev_q2) + 1*(q2 + prev_q2) + torque_prev>30){
//			output_torque = 30;
//		}
//		else{
//			output_torque = 50*(q2 - prev_q2) + 1*(q2 + prev_q2) + torque_prev;
//		}
//
//		duty_cycle = 100 - output_torque;
//	}
//	else if(q2 < 0.f){
//		compensate = 0;
//		torque_prev = output_torque;
//
//		if(50*(q2 - prev_q2) + 1*(q2 + prev_q2) + torque_prev < -30){
//			output_torque = -30;
//		}
//		else{
//			output_torque = 50*(q2 - prev_q2) + 1*(q2 + prev_q2) + torque_prev;
//		}
//
//
////		output_torque = 2*(q2_steps - error_step_prev) + (q2_steps + error_step_prev) + torque_prev;
//		duty_cycle = output_torque + 100;
//	}
//
//	if(compensate && q2_steps > 0.f){
//		motor_dir = 0;
//		HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port,MOTOR_DIR_Pin,motor_dir);
//		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, duty_cycle );
//	}
//
//	else if (!compensate && q2_steps < 0.f){
//		motor_dir = 1;
//		HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port,MOTOR_DIR_Pin,motor_dir);
//		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, duty_cycle );
//	}

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
