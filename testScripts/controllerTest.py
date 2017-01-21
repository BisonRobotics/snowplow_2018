import time
import serial
import xbox

# Format floating point number to string format -x.xxx
def fmtFloat(n):
    return '{:.0f}'.format(n)

def fmtInt(n):
    return '{:d}'.format(n)

controllGain = 400
    
joy = xbox.Joystick()


ser = serial.Serial(
	port='/dev/ttyS0',
	baudrate=115200,
	parity=serial.PARITY_ODD,
    	stopbits=serial.STOPBITS_TWO,
    	bytesize=serial.EIGHTBITS
)

ser.open
ser.isOpen()


#print 'Enter your commands below.\r\nInsert "exit" to leave the application.'

#input=1
#while 1 :
    # get keyboard input
#    input = raw_input(">> ")
        # Python 3 users
        # input = input(">> ")
#    if input == 'exit':
#        ser.close()
#        exit()
#    else:
        # send the character to the device
        # (note that I happend a \r\n carriage return and line feed to the characters - this is requested by my device)
#        ser.write(input + '\r\n')
#        out = ''
        # let's wait one second before reading output (let's give device time to answer)
#        time.sleep(1)
#        while ser.inWaiting() > 0:
#            out += ser.read(1)
#
#        if out != '':
#            print ">>" + out

#Disable Watchdog

ser.write('^RWD 0\r\n')
time.sleep(1)
#ser.write('!G 1 100\r\n')
#ser.write('!G 2 -100\r\n')

cR = 0
cL = 0

while not joy.Back():
	XR = - controllGain * (joy.rightY())
	XL = controllGain * (joy.leftY())
	
	#cR = XR 
	#cL = XL

	XR = fmtFloat(XR)
	XL = fmtFloat(XL)

	print XR, XL

	print chr(13),

	ser.write('!G 2 ' + XR + '\r\n')
	ser.write('!G 1 ' + XL + '\r\n')

ser.write('!G 1 0\r\n')
ser.write('!G 2 0\r\n')
ser.close
joy.close 
