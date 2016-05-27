import os
import sys
import json
import time
import socket
import uuid
import logging

class DteBridgeClient:
	def __init__(self, ip_addr=None, tcp_port=9999, *args, **kwargs):
		if ip_addr is None:
			hostname = socket.gethostname()
			addrinfo = socket.getaddrinfo(hostname, None, socket.AF_INET)
			ip_addr = addrinfo[0][4][0]
		self.addr = (ip_addr, tcp_port)


	def communicate(self, cmd, params=None):
		"""
		cmd is one of 'Start', 'Load', 'Dut', 'Status'

		Parameters are optional. 
		The load command takes a sinlge parameter - pass it as a simple string.
		The dut command takes a dictionary of attributes. Pass these as
		a dictionary or something that can be trivially converted to a dictionary. 

		So, in other words, this fucntion expects params to be either
		a simple string, 
		or a dictionary like this...
		     {'cat':'meow','dog':'woof','pig':'oink'}
		or things that can trivially be converted to a dictionary like...
		     [('cat','meow'),('dog','woof'),('pig','oink')]
		or even a tuple of pairs like this...
		     (('cat','meow'),('dog','woof'),('pig','oink'))
		"""

		# TODO: sanity check the inputs and barf if fed garbage.

		
		# This TCP client talks to a TCP server in DTE Platform. The server
		# expects structured strings with the following general form:
		# <uid>;<cmd>;[<params>]
		# where params are name value pairs with each pair delimited by a comma
		# and a colon separating each name from its corresponding value. In other
		# words, the parameter list looks like a python dictionary without the
		# curly braces.

		# build the message string 
		
		deletechars = " '{}" # space, single quote, curly braces
		tag = uuid.uuid1().hex.upper()
		if params is None:
			msg = "{};{}".format(tag, cmd).translate(None, deletechars)
		elif type(params) is str or type(params) is unicode:
			msg = "{};{};{}".format(tag, cmd, params)
		else:
			d = dict(params) # this can raise and exception
			msg = "{};{};{}".format(tag, cmd, d).translate(None, "'{}")


		# send the message string and get a reply
		sock = socket.create_connection(self.addr, timeout=60)
		
		#TODO: this should be conditional upon successful socket creation. 
		sock.send(msg)
		try:
			reply = sock.recv(1024)
		except Exception as e:
			logging.debug(e)
			logging.debug(dir(e))
			logging.debug(e.message)
			
		sock.shutdown(socket.SHUT_RDWR)
		sock.close()

		#TODO: ??? transform reply from string to python list object
		return (msg, reply)

