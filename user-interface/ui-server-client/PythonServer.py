import socket
import sys

class PythonServer:
    def __init__(self, host, port, q_size = 10):
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        print 'socket creaeted'

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

        conn, addr = self.s.accept() # blocks until a connection is made

        print 'Connected with ' + addr[0] + ': ' + str(addr[1])

def main():

    #server = PythonServer('localhost', 8090)
    server = PythonServer('10.42.0.1', 8090)

    while 1:


    sys.exit(0)

if __name__ == '__main__':
    main()
