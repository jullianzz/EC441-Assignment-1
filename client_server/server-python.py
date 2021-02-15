###############################################################################
# server-python.py
# Name:
# BU ID:
# Email:
###############################################################################

import sys
import socket

RECV_BUFFER_SIZE = 2048
QUEUE_LENGTH = 10

def server(server_port):

    """TODO: Listen on socket and print received message to sys.stdout"""
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(('127.0.0.1', server_port)) #associates the socket with IP 127.0.0.1 and port number server_port

    while True:
        s.listen(QUEUE_LENGTH) #always listening and waiting to est. connections
        conn, addr = s.accept() #establish a connection with a client - three way handshake
        sys.stdout.flush()

        while True: # loop runs only when data !=0, i.e. there is data to be received
            data = conn.recv(RECV_BUFFER_SIZE) #receive data from client and returns a string
            if not data:
                break
            sys.stdout.write(data) #write data to stdout
            sys.stdout.flush() #push data into output file
        #Flow of control comes here when done receiving client msg (reached eof)
        conn.close() #close the current connection 


def main():
    """Parse command-line argument and call server function """
    if len(sys.argv) != 2:
        sys.exit("Usage: python server-python.py [Server Port]")
    server_port = int(sys.argv[1])
    server(server_port)

if __name__ == "__main__":
    main()
