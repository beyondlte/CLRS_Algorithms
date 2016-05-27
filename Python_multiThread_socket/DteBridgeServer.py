import logging
import sys
import SocketServer
import time
import random


current_server = None

SOCKETSTARTED = False

DTESTATUS = 'None'
SERIALNO = 'None'
WORKORDERNO = 'None'
PRODUCTNO = 'None'
SCREENREFRESH = 'None'
STEP = 'None'
OPERATION = 'None'
LOTNO = 'None'
SEQUENCENO = 'None'
UPDATEON = 'None'
INSPECTIONPLANNO = 'None'
INSPECTIONPLANREVISION = 'None'
PRODUCTID = 'None'
EMPLOYEEID = 'None'
RESOURCEID = 'None'
LOTSTARTTEST = 'None'

def openServer_old(host='localhost', port=7000, _startServe=False):
	global current_server
	SocketServer.ThreadingTCPServer.allow_reuse_address = True
	current_server = SocketServer.ThreadingTCPServer((host,port), OpcRequestHandler)

	# if current_server is None:
	# 	SocketServer.ThreadingTCPServer.allow_reuse_address = True
	# 	current_server = SocketServer.ThreadingTCPServer((host,port), OpcRequestHandler)
	# 	"""
	# 	current_server = SocketServer.TCPServer((host,port), OpcRequestHandler)
	# 	"""
	current_server._startServe = _startServe
	print dir(current_server)
	return current_server

def openServer(host='localhost', port=7000, _startServe=False):
	# global current_server
	current_server = OpcServer((host,port), _startServe)
	print current_server
	return current_server



class OpcRequestHandler(SocketServer.StreamRequestHandler):
	def __init__(self, request, client_address, server, _startServe=True):
		self.logger = logging.getLogger('OpcRequestHandler')
		self.logger.debug('__init__')
		self._startServe = _startServe
		SocketServer.StreamRequestHandler.__init__(self, request, client_address, server)
		return

	def setup(self):
		# self.logger.debug('setup')
		return SocketServer.StreamRequestHandler.setup(self)

	def processMsg(self, recvdMsg):
		global DTESTATUS
		global SERIALNO
		global WORKORDERNO
		global PRODUCTNO
		global SCREENREFRESH
		global STEP
		global OPERATION
		global LOTNO
		global SEQUENCENO
		global UPDATEON
		global INSPECTIONPLANNO
		global INSPECTIONPLANREVISION
		global PRODUCTID
		global EMPLOYEEID
		global RESOURCEID
		global LOTSTARTTEST	
	
		tags = dict()
			
		recvdMsg = recvdMsg.strip()
		if recvdMsg == '':
			self.request.send("\n")
			return tags
			
		self.logger.debug('recv()->"%s"', recvdMsg)

		try:
			name, value = recvdMsg.split(':')
		except:
			self.logger.debug('bad msg recv()->"%s"', recvdMsg)
			self.request.send("\n")
			return tags

		tagName = name.strip()
		tagValue = value.strip()
		tags[tagName] = tagValue

		tagName = tagName.lower()

		sendMsg = 'OK\n'

		if tagName == 'dtestatus':
			sendMsg = "%s\n" % DTESTATUS

		elif tagName == 'serialno':
			SERIALNO = tagValue

		elif tagName == 'workorderno':
			WORKORDERNO = tagValue

		elif tagName == 'productno':
			PRODUCTNO = tagValue

		elif tagName == 'screenrefresh':
			SCREENREFRESH = tagValue

		elif tagName == 'step':
			STEP = tagValue

		elif tagName == 'operation':
			OPERATION = tagValue

		elif tagName == 'lotno':
			LOTNO = tagValue

		elif tagName == 'sequenceno':
			SEQUENCENO = tagValue

		elif tagName == 'updateon':
			UPDATEON = tagValue

		elif tagName == 'inspectionplanno':
			INSPECTIONPLANNO = tagValue

		elif tagName == 'inspectionplanrevision':
			INSPECTIONPLANREVISION = tagValue

		elif tagName == 'productid':
			PRODUCTID = tagValue

		elif tagName == 'employeeid':
			EMPLOYEEID = tagValue

		elif tagName == 'resourceid':
			RESOURCEID = tagValue

		elif tagName == 'lotstarttest':
			LOTSTARTTEST = tagValue

		elif tagName == 'starttest':
			print("--- start test: %s" % tagValue)
			if tagValue == '1':
				DTESTATUS = '2'
				sendMsg = '2\n'
			elif tagValue == '-1':
				DTESTATUS = '-1'
				sendMsg = '-1\n'
			else:
				DTESTATUS = '0'
				sendMsg = '0\n'

		else:
			print("Received an invalid tag name - '%s'" % tagName)
			self.logger.debug("Received an invalid tag name - '%s'" % tagName)

		# we always have something to say to the client.
		# so the client must always read after sending.
		self.logger.debug("Sending '%s'" % sendMsg)		
		self.request.send(sendMsg)
	
		return tags
	
	def handle(self):

		while self.server._startServe:

			recvdMsg = self.request.recv(1024)
				
			# break up individual messages
			msgs = recvdMsg.split('\n')
			for msg in msgs:
				if msg == '':
					continue
				
				tags = self.processMsg( msg )

				for key in tags:
					print("%s:%s" % (key, tags[key]))



	def finish(self):
		# self.logger.debug('finish')
		return SocketServer.StreamRequestHandler.finish(self)


class OpcServer(SocketServer.ThreadingMixIn, SocketServer.ThreadingTCPServer):
	def __init__(self, server_address, _startServe=False, handler_class= OpcRequestHandler):
		self._startServe = _startServe
		SocketServer.ThreadingTCPServer.__init__(self, server_address, handler_class)
		return

	def serve_forever(self):
		self.handle_request()

		# while self._startServe:
		# while True:
		# return
	def handle_request(self):
		return SocketServer.ThreadingTCPServer.handle_request(self)

	def shutdown(self):
		# self._startServe = False
		# looks like for this one, it shuts down the server 
		# but the request handler is not shutdown
		return SocketServer.ThreadingTCPServer.shutdown(self)

	def server_close(self):
		# here we stop the serve_forever
		self._startServe = False
		return SocketServer.ThreadingTCPServer.server_close(self)

