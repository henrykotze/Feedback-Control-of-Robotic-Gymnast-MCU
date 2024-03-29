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
char* acrobat = "Feed22back Control Of A Robotic Gymnast\r\n";
char* dollar = "$";
char* comma = ",";
char* endSymbol = "\n";
uint8_t* verification = NULL;
uint8_t send_data_flag = 1;

//DMA for sampling potentiometer and current signal
uint32_t* ADC_buffer = NULL;
uint32_t sampledCurrent = 0;
uint32_t sampledPotentiometer = 0;
uint8_t adc_flag = 0;
uint16_t startval_sampledPotentiometer = 1600;

// Controlling torque of motor
uint8_t duty_cycle = 0;
uint8_t* discrete_arctan = NULL;
uint8_t motor_dir = 0;
uint8_t control_state = 0;


uint8_t error_step = 0;
uint8_t error_step_prev = 0;
uint8_t  torque = 0;

// Encoder angles
uint8_t encoder_1 = 0;
uint8_t encoder_2 = 0;
//uint8_t enable_encoder_reading = 1;
uint8_t encoder_flag = 0;
//float dir_increment_size = 0.015707;

// Modes of operations
uint8_t simulate = 1;
uint8_t start = 0;

// discretize arctan

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

int16_t q2_steps = 0;


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

// flags for sending and receiving
uint8_t send_flag = 0;





