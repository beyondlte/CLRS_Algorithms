import socket
import sys
import time

def client():
	# Create a TCP/IP socket
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

	# Connect the socket to the port where the server is listening
	# server_address = ('172.21.0.82', 2600)
	server_address = ('172.21.52.58', 7001)
	print >>sys.stderr, 'connecting to %s port %s' % server_address
	sock.connect(server_address)
	try:
		
		# Send data
		# message = 'This is the message.  It will be repeated.'

		# Look for the response
		amount_received = 0
		
		# while amount_received < amount_expected:
		runMode = True
		while runMode:
			sock.sendall("lotno:3\n")
			data = sock.recv(32)
			amount_received += len(data)
			print('len of data = ', len(data))
			print >>sys.stderr, 'received "%s"' % data
			time.sleep(2.0)

	except Exception as e:
		print e
		print 'something is wrong'
	finally:
		print >>sys.stderr, 'closing socket'
		sock.close()

if __name__ == '__main__':
	# this will create new connections, it's not waht I need
	for i in range(1):
		client()
		time.sleep(1.0)
