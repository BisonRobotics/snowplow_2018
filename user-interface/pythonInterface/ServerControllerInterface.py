#!/bin/python

import PythonServer

def main():

    #server = PythonServer('localhost', 8090)
    server = PythonServer('10.42.0.1', 8090)

    while 1:
        # first wait for data from client side
        data = server.conn.recv(4096)


    sys.exit(0)

if __name__ == '__main__':
    main()


