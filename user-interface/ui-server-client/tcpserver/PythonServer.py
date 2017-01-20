import socket
import sys

# xbox controller interface library
import xbox

class PythonServer:
    def __init__(self, host, port, q_size = 10):
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        print 'socket created'

        # define a few class variables
        self.HOST = host
        self.PORT = port

        try:
            self.s.bind((self.HOST, self.PORT))
            print 'Socket bind success'
        except socket.error, msg:
            print 'Bind failed. Error code: ' + str(msg[0]) + ' Message: ' + msg[1]
            sys.exit()

        self.s.listen(q_size) # will prolly never need to queue 10 different connections
        print 'Socket now listening'

        self.conn, addr = self.s.accept() # blocks until a connection is made

        print 'Connected with ' + addr[0] + ': ' + str(addr[1])

def main():

    server = PythonServer('10.42.0.1', 8090)
    server.s.settimeout(0) # wait no longer than this many seconds when reading

    # open xbox controller
    joystick = xbox.Joystick()

    prevL = 0.0
    prevR = 0.0
    prevA = 0
    prevB = 0

    printSignal = 'P\0'
    l = 'Ly\0'
    r = 'Ry\0'
    btnA = 'A\0'
    btnB = 'B\0'

    while 1:

        left = joystick.leftY()
        right = joystick.rightY()
        A_ = joystick.A()
        B_ = joystick.B()

        print 'Left stick:  ', str(left), '\nRight stick: ', str(right), '\nA: ', str(A_), '\tB: ', str(B_)

        # the following if statements ensure data is only sent if the controller state changes

        if prevL != left:
            prevL = left
            server.conn.send(l) # flag to client
            lDat = str(left + 1.0) + '\0'
            server.conn.send(lDat)
            server.conn.send(printSignal)

        if prevR != right:
            prevR = right
            server.conn.send(r) # flag to client
            rDat = str(right + 1.0) + '\0'
            server.conn.send(rDat)
            server.conn.send(printSignal)

        if prevA != A_:
            prevA = A_
            server.conn.send(btnA) # flag to client
            buttonData = str(A_) + '\0'
            server.conn.send(buttonData)
            server.conn.send(printSignal)

        if prevB != B_:
            prevB = B_
            server.conn.send(btnB) # flag to client
            buttonData = str(B_) + '\0'
            server.conn.send(buttonData)
            server.conn.send(printSignal)

    sys.exit(0)

if __name__ == '__main__':
    main()
