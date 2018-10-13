# Data Aquisistion script for Feedback Contol Of Robotic Gymnast
# This script is compatible on Windows 7 and newer and Linux.
# Requirements: 
# Set PORT to correct variable depending on device
# set UART VARIABLES to desired settings

# importing pySerial packages to communicate over UART
import serial
# importing package that listen to keyboard inputs
import msvcrt

#importing package for math function
import math
#LINUX EXAMPLE
#PORTS="\\dev\\USBTTY1"
# WINDOWS EXAMPLE
PORT = 'COM11'

# UART VARIABLES
BUADRATE=230400
WORD_LENGHT=serial.EIGHTBITS   # OPTIONS: FIVEBITS,SIXBITS,SEVENBITS,EIGHTBITS
PARITY=serial.PARITY_NONE      # OPTIONS: PARITY_NONE, PARITY_EVEN, PARITY_ODD, PARITY_MARK, PARITY_SPACE
STOP_BITS=serial.STOPBITS_ONE  # OPTIONS: STOPBITS_ONE, STOPBITS_ONE_POINT_FIVE, STOPBITS_TWO




# Setting up chosen settings
ser = serial.Serial(PORT,BUADRATE,WORD_LENGHT,PARITY,STOP_BITS,timeout=100)
ser.close()
ser.open()
if(not ser.is_open):
    print('Port to device is not open')

# global variables
send_data = ''
header = "time,q1,q2,tau\n"
stop_experiment = "$X\n"
ack = '\n'


q1 = float(0)
q2 = float(0)
q1dot = float(0)
q2dot = float(0)
tau = float(0)

q1prev = float(0)
q2prev = float(0)
q1prevprev = float(0)
q2prevprev = float(0)

# variables used in sin/cos function to only compute once
sin_q1 = float(0)    # sin(q1)
sin_q2 = float(0)    # sin(q2)
sin_q1_q2 = float(0) # sin(q2+q1)
cos_q2 = float(0)    # cos(q2)

# time difference between data being sent
delta_t = float(0.001)

# string to send torque to be outputted
send_torque = "$T"

# measured tau 
tau_measured = 0

# Incremental size for encoder
q2_increment_size = float(1/896)

# sampled value measured at q1 = 0 rad
zero_potentiometer = 1600



filename = input('filename to save data: ')
description = input('write description for file: ')
description = description + '\n'
file_ = open(filename,"a")
file_.write(description)
file_.write(header)


while(send_data != '$B,1\n'): # if send_data = $B,1\r\n the experiment starts and data are streamed
    send_data = input('Enter Command to Send: ')
    if(send_data == '$B,1\n'):
        break
    send_data = send_data+ack
    print('Sent: ' + send_data)



    if(send_data == '$A\n'):      # Testing whether UART comms are working
        # Expect return_data: Feedback Control Of Robotic Gymnast
        ser.write(send_data.encode('utf-8'))
        return_data = ser.read_until('\n'.encode('utf-8'))
        print('ACK FROM DEVICE: ' + return_data.decode('utf-8'))
    
    elif(send_data == 'close\n'):    # Enable data aquisition of shaft angle  
        ser.close()

    elif(send_data == '$B,1\n'):    # Enable data aquisition of shaft angle   
        ser.write(send_data.encode('utf-8'))
        return_data = ser.read_until('\n'.encode('utf-8'))
        print('ACK FROM DEVICE: ' + return_data.decode('utf-8'))


        
# data grouping being received
# ${time},{q1},{q2},{tau}

print('Receiving data over UART')    
while True:#making a loop#finishing the loop
    return_data = (ser.read_until('\n'.encode('utf-8'))).decode('utf-8')
    state_variables = return_data.split(",");


    if(len(state_variables)) == 4:
        print(len(state_variables))
        print(state_variables)
        q1 = (float(state_variables[2])-zero_potentiometer)*0.00153
        q2 = (float(state_variables[3])*q2_increment_size)

        # assign previous values
        q1prev = q1
        q1prevprev = q1prev
        q2prev = q2
        q2prevprev = q2prev

        # three point difference for q1
        q1dot = (0.5*q1prevprev-2*q1prev+3/2*q1)/(delta_t)
        # three point difference for q2
        q2dot = (0.5*q2prevprev-2*q2prev+3/2*q2)/(delta_t)

        sin_q1 = math.sin(q1)           # sin(q1)
        sin_q2 = math.sin(q2)           # sin(q2)
        sin_q1_q2 = math.sin(q1+q2)     # sin(q2+q1)
        cos_q2 = math.cos(q2)           # cos(q2)
        atan_q2 = math.atan(q2)         # atan(q2)
         
        torque = 0.008*q2dot - 0.008*q1dot + 1.0224*sin_q1_q2 + 0.024492*q1dot**2*sin_q2 \
        + ((0.024492*cos_q2 + 0.025643)**2/(0.048984*cos_q2 + 0.079417) - 0.025643)*(58.0*q2\
        + 12.7*q2dot - 60.737*atan_q2) - (1.0*(0.024492*cos_q2 + 0.025643)*(- 0.024492*sin_q2*q2dot**2\
        - 0.048984*q1dot*sin_q2*q2dot + 1.0224*sin_q1_q2 + 2.2984*sin_q1 + 0.0071))/(0.048984*cos_q2\
        + 0.079417)

        send_torque = "$T,"+str(int(1000*torque))
        print(send_torque)
        ser.write(send_torque.encode('utf-8'))




   
 


    file_.write(return_data)

    if msvcrt.kbhit(): # The press of any key will results entering if
        break















# Sending mutiple stop experiments commands to ensure system stops
ser.write(stop_experiment.encode('utf-8'))
print("ACK FROM DEVICE: " + (ser.read_until('\n'.encode('utf-8'))).decode('utf-8') )
ser.write(stop_experiment.encode('utf-8'))
print("ACK FROM DEVICE: " + (ser.read_until('\n'.encode('utf-8'))).decode('utf-8') )
ser.write(stop_experiment.encode('utf-8'))
print("ACK FROM DEVICE: " + (ser.read_until('\n'.encode('utf-8'))).decode('utf-8') )
ser.write(stop_experiment.encode('utf-8'))
print("ACK FROM DEVICE: " + (ser.read_until('\n'.encode('utf-8'))).decode('utf-8') )
ser.write(stop_experiment.encode('utf-8'))
print("ACK FROM DEVICE: " + (ser.read_until('\n'.encode('utf-8'))).decode('utf-8') )
ser.write(stop_experiment.encode('utf-8'))
print("ACK FROM DEVICE: " + (ser.read_until('\n'.encode('utf-8'))).decode('utf-8') )
ser.write(stop_experiment.encode('utf-8'))
print("ACK FROM DEVICE: " + (ser.read_until('\n'.encode('utf-8'))).decode('utf-8') )
ser.write(stop_experiment.encode('utf-8'))
print("ACK FROM DEVICE: " + (ser.read_until('\n'.encode('utf-8'))).decode('utf-8') )
ser.write(stop_experiment.encode('utf-8'))
print("ACK FROM DEVICE: " + (ser.read_until('\n'.encode('utf-8'))).decode('utf-8') )
ser.write(stop_experiment.encode('utf-8'))
print("ACK FROM DEVICE: " + (ser.read_until('\n'.encode('utf-8'))).decode('utf-8') )
file_.close()
ser.close()
