/*
 * dma_comms.c
 *
 *  Created on: Aug 13, 2018
 *      Author: Henry
 */

#include "function.h"
#include "variables.h"

void get_current_potentiometer(){
	//sampledCurrent = ADC_buffer[1];
	//sampledPotentiometer = ADC_buffer[0];
	sprintf(send_torque,"%lu", ADC_buffer[1]);
	sprintf(send_q1,"%lu", ADC_buffer);


	//prevprev_q1 = prev_q1;
	//prev_q1 = q1;
	//q1 = ((int32_t)sampledPotentiometer-(int32_t)startval_sampledPotentiometer)*0.00153f;
	//torque = (sampledCurrent<<9);


	//three-point backward difference
//	q1dot = (prevprev_q1 - prev_q1<<2+3*q1)/(time<<2); // time variable needs to change





}

