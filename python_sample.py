import serial #Raspberrypi should already come with PySerial library
import random as rand #generate random numbers
from time import sleep #not sure if time library already exists
serial_port = 'COM3' #In this example, using COM5 but this should be changed to
                     # serial_port = "/dev/ttyUSB0" or something like that
serial_baud = 9600
#Initialize serial
ser = serial.Serial(port=serial_port, baudrate=serial_baud, timeout=1)


###################### TO VERIFY IF SENDING ACCURATE DATA##########
for i in range(10):
    ser.write(str(i).encode()) #write data to serial 10 times
    print("Writing ",i)
    sleep(2)

#this correlates to arduino_sample1

##################### Sample more applicable to you ###############
#Send random data 10 times

for i in range(10):
    x_value = 300
    y_value = 300
    radius = 300
    data_to_send = str(x_value) + "," + str(y_value) + "," + str(radius)#prepare string
    ser.write(data_to_send.encode()) #send to serial
    print("Writing:\t",data_to_send)
    sleep(2)

#this correlates to arduino_sample2
