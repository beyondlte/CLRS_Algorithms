import os
import sys
import json
import time
import socket
import threading
import uuid
import getopt
import logging

import DteBridgeServer
import DteBridgeClient

logfilePath = r'c:\temp' 
if not os.path.exists(logfilePath):
    os.makedirs(logfilePath)

logging.basicConfig(filename =r'c:\temp\DteBridgeLog.txt',
					level=logging.DEBUG,
					format='[%(threadName)-10s] %(name)s: %(message)s',
					filemode='w',
					)
					

"""
The DTE Bridge serves as an intermediary between the MES and OPC Driver on one side
and the DTE Platform on the other. The Bridge has both a TCP server and a TCP client.
The OPC Driver connects to the TCP Server and the bridge uses the client to connect 
to a TCP server embedded in the DTE Platform (or, in the future, another intermediate).

The bridge server side maintains a conversation with MES/OPC and the client side 
communicates with the DTE platform. The Main purpose of the DTE bridge is to 
perform a simple translation from one protocol to another. 
"""


startTime = time.time()
runningTime = 0.0
configFileTime = None
config = None
default_config = None

def readConfig( configFile ):
	global configFileTime
	global config
	global default_config
	
	configModified = os.path.getmtime( configFile )
	if configModified == configFileTime:
		return( config, default_config )

	configFileTime = configModified

	hostname = socket.gethostname()
	addrinfo = socket.getaddrinfo(hostname, None, socket.AF_INET)
	myIpAddr = addrinfo[0][4][0]

	# this gives a hint about the expected format and content of the config file.
	default_config = dict()
	default_config["ListenAddr"] = myIpAddr # server listens on this IP Addr
	default_config["ListenPort"] = 7000 # server listens on this TCP port
	default_config["Timeout"] = 3600 # 3600 seconds is one hour
	default_config["AssetNum"] = r"A0001" 
	# the config file must/might? also contain a mapping
	# from InspectionPlanNumber to DTE config file name
	default_config["DteConfigMap"] = dict({"831909-03":r"\Program Files (x86)\Intuitive Surgical\DTE_Platform_1_6_1\Samples\MyFirstProject"})

	# we expect config to be a simple python dictionary representing "name : value" pairs
	# saved with a call to json.dump()
	config = dict()
	try:
		with open(configFile, "r") as f:
			config = json.load(f)
	except:
		print 'Could not read config file'

	return( config, default_config )


def verifyTags(msg,reply):
	(msgTag, msgCmd), msgParams = msg.split(';')[0:2], msg.split(';')[2:]
	(replyTag, replyCmd), replyParams = reply.split(';')[0:2], reply.split(';')[2:]
	return msgTag == replyTag
	
def DteBridge( *args, **kwargs):
	try:
		global startTime
		global runningTime

		config_file_path = kwargs.get( 'filename', '' )
		ipaddr = kwargs.get( 'ipaddr', '' )

		originPath = os.getcwd()

		config, default_config = readConfig( config_file_path )

		# build some convenient short-hand notation.
		asset_num = config.get("AssetNum", default_config["AssetNum"])
		dte_config = config.get("DteConfigMap", default_config["DteConfigMap"])

		# TODO: write some informational messages before dropping into the loop

		# start the server if it hasn't already been started.
		if not DteBridgeServer.SOCKETSTARTED:
			if ipaddr == '':
				ip_addr = config.get("ListenAddr", default_config["ListenAddr"])
			else:
				ip_addr = ipaddr

			tcp_port = config.get("ListenPort", default_config["ListenPort"])
			myServer = DteBridgeServer.openServer(ip_addr, 7000, True)
			t1 = threading.Thread(target = myServer.serve_forever)
			t1.setDaemon(True)

			youServer = DteBridgeServer.openServer(ip_addr, 7001, True)
			t2 = threading.Thread(target = youServer.serve_forever)
			t2.setDaemon(True)
			t1.start()
			t2.start()
			DteBridgeServer.SOCKETSTARTED = True

		# create a client too.

		myClient = DteBridgeClient.DteBridgeClient( ip_addr='127.0.0.1', tcp_port=9999 )

		while True: 
			# wait indefinitely for the state to change...
			# the state changes to 2 when we receive a 
			# 'StartTest' message with value equal to 1
			DteBridgeServer.DTESTATUS = asset_num
			while DteBridgeServer.DTESTATUS != '2':
				#print DteBridgeServer.DTESTATUS
				time.sleep(1.0)
				timenow = time.time()
				runningTime = timenow - startTime
				if runningTime > 8.0:
					print "shutdown the forever server"
					myServer.server_close()
					# myServer.shutdown()
				if (int(timenow)%5 == 0):
					print('(%s) DTESTATUS = %s, running time: %ds, waiting for "StartTest"' % (ipaddr, DteBridgeServer.DTESTATUS, runningTime))

			config, default_config = readConfig( config_file_path )

			# build some convenient short-hand notation.
			asset_num = config.get("AssetNum", default_config["AssetNum"])
			dte_config = config.get("DteConfigMap", default_config["DteConfigMap"])

			# once the start message is received, gather up all the other received messages
			tags = dict()
			tags['SerialNo']=DteBridgeServer.SERIALNO
			tags['WorkOrderNo']=DteBridgeServer.WORKORDERNO
			tags['ProductNo']=DteBridgeServer.PRODUCTNO
			tags['ScreenRefresh']=DteBridgeServer.SCREENREFRESH
			tags['Step']=DteBridgeServer.STEP
			tags['Operation']=DteBridgeServer.OPERATION
			tags['LotNo']=DteBridgeServer.LOTNO
			tags['SequenceNo']=DteBridgeServer.SEQUENCENO
			tags['UpdateOn']=DteBridgeServer.UPDATEON
			tags['InspectionPlanNo']=DteBridgeServer.INSPECTIONPLANNO
			tags['InspectionPlanRevision']=DteBridgeServer.INSPECTIONPLANREVISION
			tags['ProductID']=DteBridgeServer.PRODUCTID
			tags['EmployeeID']=DteBridgeServer.EMPLOYEEID
			tags['ResourceID']=DteBridgeServer.RESOURCEID
			tags['LotStartTest'] = DteBridgeServer.LOTSTARTTEST

			# doctor up some of the information received from the OPC driver

			# an instrument serial number is actually a composite of LotNr and SequenceNr
			# interpret the parts of this serial number as LotNr_SeqNr
			if '_' in tags['SerialNo']:
				s = tags['SerialNo']
				index = s.find('_')
				lot_nr = s[:index]
				sequence_nr = s[index+1:]
				tags['LotNo'] = lot_nr
				tags['SequenceNo'] = sequence_nr

			# do not leave undesireable characters in the LotNumber field. 
			if tags["LotNo"] == "-":
				tags["LotNo"] = ""

			print('Work Order nr: %s' % tags["WorkOrderNo"])
			print('Product nr: %s' % tags["ProductNo"])
			print('Serial nr: %s' % tags["SerialNo"])
			print('Inspection Plan nr: %s' % tags["InspectionPlanNo"])
			print('Inspection Plan rev: %s' % tags["InspectionPlanRevision"])

			time.sleep(1.0)

			# write the tags strings that we received from the OPC driver out to a file
			# DTE will pick this up in an event handler and decide what to do with the info.

			#with open(os.path.join(project_dir, 'tags.json'), "w") as f:
			#	json.dump(tags, f, indent=4)


			# Use the client socket to communicate to talk to DTE Platform

			# tell DTE which DTE project (which config.xml) to load
			# we lookup the name of the DTE config.xml file to use based upon the inspection plan number.
			dte_config_xml_filename = dte_config[tags['InspectionPlanNo']] 

			msg, reply = myClient.communicate("load", dte_config_xml_filename)
			if not verifyTags(msg, reply):
				print 'BAD REPLY'
			
			#TODO: error checking and handling.

			# send all the information (OPC tags) that we received from the OPC Driver to DTE
			msg, reply = myClient.communicate("dut", tags)
			if not verifyTags(msg, reply):
				print 'BAD REPLY'
						
			#TODO: error checking and handling.

			# Push the start button on the DTE GUI. 
			test_session_id = uuid.uuid1().hex.upper()
			msg, reply = myClient.communicate("start", test_session_id)
			if not verifyTags(msg, reply):
				print 'BAD REPLY'
			#TODO: error checking and handling.

			#TODO: What else?

			# something like this I guess...
			while True:
				time.sleep(1.0)
				msg, reply = myClient.communicate("status")
				if not verifyTags(msg, reply):
					print 'BAD REPLY'			
				reply = reply.split(';')
				print reply
				if len(reply) == 4:
					tag, resp, state, passfail = reply
					if state == '0':
						break

			# indicate that tags.json is written / DTE test has been started ?
			DteBridgeServer.DTESTATUS = '3'

			# TODO: HERE!
			# do we need to wait? 


			# check if the test is done or not by looking for a special file.
			#timeout= config.get("Timeout", default_config["Timeout"])
			#while not os.path.exists(done_file):
			#	time.sleep(1)
			#	timeout = timeout - 1
			#	if timeout <= 0:
			#		break

			print 'UPDATING STATUS TO 5'
			# Tell MES that DTE is done (Test Complete)
			DteBridgeServer.DTESTATUS = '5'

			time.sleep ( 5.0 )

		#if we ever break out of the infinite while loop, kill the server
		print("shuting down server now.")
		myServer.shutdown()
		myServer.server_close()
		return
	except KeyError, e:
		print 'KeyError: %s not found in DTEBridge.conf' % str(e)
		DteBridgeServer.DTESTATUS = '-1'
		time.sleep(1.0)
		# stop the socketServer thread using shared variable SOCKETSTARTED
		DteBridgeServer.SOCKETSTARTED = False
		raw_input("Found an error! Please check the error msg above and press any key to exit...")
	except:
		raise
		print 'Unknown error, re-raise it'
		DteBridgeServer.DTESTATUS = '-1'
		time.sleep(1.0)
		DteBridgeServer.SOCKETSTARTED = False
		raw_input("Found an error! Please check the error msg above and press any key to exit...")


if __name__ == '__main__':
	optlst, args = getopt.getopt( sys.argv[ 1: ], '', longopts=['filename=', 'ipaddr='] )
	optlst = dict( optlst )
	
	DteBridge( filename=optlst.get( '--filename', 'DteBridge.conf' ), ipaddr=optlst.get( '--ipaddr', socket.gethostbyname(socket.gethostname()) ) )
	sys.exit()

