import time
import serial

def main(argv):
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

<<<<<<< HEAD
#Both motors foward
ser.write('!G 1 400\r\n')
ser.write('!G 2 -400\r\n')

time.sleep(10)
=======
        #Both motors foward
        ser.write('!G 1 -200\r\n')
        ser.write('!G 2 200\r\n')

        time.sleep(5)
>>>>>>> f9b706bf9758e048bd04d20c4bd8bc69c2700ff7

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
