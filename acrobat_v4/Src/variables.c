/*
 * variables.c
 *
 *  Created on: Aug 13, 2018
 *      Author: Henry
 */
#include "variables.h" // contains explanations of variables



// UART COMMUNICATIONS
uint8_t	uart_flag = 0;
uint8_t* rx_buffer = NULL;
uint8_t rx_byte = 0;
uint8_t* data_buffer = NULL;
uint8_t rx_buffer_cntr = 0;
char* acrobat = "Feedback Control Of A Robotic Gymnast\r\n";
char* dollar = "$";
char* comma = ",";
char* endSymbol = "\n";
uint8_t* verification = NULL;
uint8_t send_data_flag = 1;

//DMA for sampling potentiometer and current signal
uint32_t* ADC_buffer = NULL;
uint32_t sampledCurrent = 0;
uint32_t sampledPotentiometer = 0;
uint8_t enable_ADC_interrupt = 1;
uint8_t adc_flag = 0;
uint32_t startval_sampledPotentiometer = 1211;

// Controlling torque of motor
uint8_t duty_cycle = 0;
uint8_t* discrete_arctan = NULL;
uint8_t motor_dir = 0;
uint8_t compensate = 0;
uint8_t control_state = 0;
float alpha = 0;

uint8_t error_step = 0;
uint8_t error_step_prev = 0;
uint8_t  torque = 0;
int16_t torque_prev = 0;

// Encoder angles
uint8_t encoder_1 = 0;
uint8_t encoder_2 = 0;
uint8_t enable_encoder_reading = 1;
uint8_t encoder_flag = 0;
float dir_increment_size = 0.0079;

// Modes of operations
uint8_t simulate = 1;
uint8_t start = 0;

// discretize arctan
float* atan_vals = NULL;

//scratchpad variables
char* scratchpad = NULL;

// data aquisition flag
uint8_t data_flag = 0;
uint8_t enable_data_aquisition = 0;


// temporary flag: PWM interrupt
uint8_t pwm_flag = 0;

// measured state variables
float q1 = 0;
float prev_q1 = 0;
float prevprev_q1 = 0;
float q1dot = 0;

float q2 = 0;
float prev_q2 = 0;
float prevprev_q2 = 0;
float q2dot = 0;

int32_t q2_steps = 0;


uint32_t time = 0;

// converted measured state variables to char format to be able to send over uart
char* send_q1 = NULL;
char* send_q2 = NULL;
char* send_torque = NULL;
char* send_time = NULL;

// System constant


// size of buffers
size_t size_data_buffer = 0;
size_t size_time = 0;
size_t size_q1 = 0;
size_t size_q2 = 0;
size_t size_torque = 0;

// constants
const float PI = 3.14159265359;
const float a = 0.008;
const float b =  1.0224;
const float c = 0.024492;
const float d = 0.024492;
const float e = 0.025643;
const float f = 0.048984;
const float g = 0.0794170;
const float h = 0.025643;
const float i = 58.0;
const float j = 12.7;
const float k = 60.737;
const float l = 0.024492;
const float m = 0.025643;
const float n = 0.024492;
const float o = 0.048984;
const float p  = 1.0224;
const float q  = 2.2984;
const float r  = 0.0071;
const float s = 0.048984;
const float t = 0.079417;


float cos_q2 = 0;
float sin_q2 = 0;
float sin_q1_q2 = 0;


// Torque
float controller_torque = 0;

float time_del = 0.008;



