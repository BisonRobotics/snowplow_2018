import time
import serial

ser = serial.Serial(
	port='/dev/ttyS0',
	baudrate=115200,
	parity=serial.PARITY_ODD,
    	stopbits=serial.STOPBITS_TWO,
    	bytesize=serial.EIGHTBITS
)

ser.open
ser.isOpen()

ser.write('^RWD 0\r\n')
time.sleep(1)

#Both motors foward
ser.write('!G 1 400\r\n')
ser.write('!G 2 -400\r\n')

time.sleep(10)

#turn off motors
ser.write('!G 1 0\r\n')
ser.write('!G 2 0\r\n')

time.sleep(2)

ser.write('!G 1 -400\r\n')
ser.write('!G 2 400\r\n')

time.sleep(10)

ser.write('!G 1 0\r\n')
ser.write('!G 2 0\r\n')

ser.close
