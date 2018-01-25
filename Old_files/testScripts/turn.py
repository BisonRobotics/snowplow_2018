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
ser.write('!G 1 200\r\n')
ser.write('!G 2 200\r\n')

time.sleep(3)

#turn off motors
ser.write('!G 1 0\r\n')
ser.write('!G 2 0\r\n')


ser.close
