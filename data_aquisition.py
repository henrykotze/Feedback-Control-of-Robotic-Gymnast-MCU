# Data Aquisistion script for Feedback Contol Of Robotic Gymnast
# This script is compatible on Windows 7 and newer and Linux.
# Requirements: 
# Set PORT to correct variable depending on device
# set UART VARIABLES to desired settings

# importing pySerial packages to communicate over UART
import serial
# importing package that listen to keyboard inputs
import msvcrt

#LINUX EXAMPLE
#PORTS="\\dev\\USBTTY1"
# WINDOWS EXAMPLE
PORT = 'COM11'

# UART VARIABLES
BUADRATE=115200
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

    elif(send_data == '$C,1\n'):    #
        return_data = ser.read(4)
        print('ACK FROM DEVICE: ' + return_data.decode('utf-8'))

    elif(send_data == '$C,0\n'):    # Enable data aquisition of shaft angle
        return_data = ser.read(4)
        print('ACK FROM DEVICE: ' + return_data.decode('utf-8'))

    elif(send_data == '$D\n'):    # Enable  power to motor
        motor_enable = 1    
        return_data = ser.read(4) 
        print('ACK FROM DEVICE: ' + return_data.decode('utf-8'))

    elif(send_data == '$E\n'):    # 
        
        return_data = ser.read(4)
        print('ACK FROM DEVICE: ' + return_data.decode('utf-8'))

    elif( not (send_data.find("$F,")) ) :    # Set PWM duty Cycle
        ser.write(send_data.encode('utf-8'))
        return_data = ser.read_until('\n'.encode('utf-8'))
        print('ACK FROM DEVICE: ' + return_data.decode('utf-8'))


    elif(send_data == '$G\n'):    # Set Direction of motor
        return_data = ser.read(4)
        print('ACK FROM DEVICE: ' + return_data)

    
    elif(send_data == '$X\n'):    # Start experiment based on enable parameters
        return_data = ser.read(4)
        print('ACK FROM DEVICE: ' + return_data)
        
# data grouping being received
# ${time},{q1},{q2},{tau}

print('Receiving data over UART')    
while True:#making a loop#finishing the loop
    return_data = (ser.read_until('\n'.encode('utf-8'))).decode('utf-8')
    print(return_data)
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
