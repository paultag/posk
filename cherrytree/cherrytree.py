#!/usr/bin/env python

import os

try:
	import json
except:
	import simplejson as json

current_pid = 0;

RESOURCE_BITMASK_SSD = 0b1000000000000000
RESOURCE_BITMASK_NIC = 0b0100000000000000
RESOURCE_BITMASK_RE1 = 0b0010000000000000
RESOURCE_BITMASK_RE2 = 0b0001000000000000
RESOURCE_BITMASK_RE3 = 0b0000100000000000
RESOURCE_BITMASK_RE4 = 0b0000010000000000
RESOURCE_BITMASK_RE5 = 0b0000001000000000
RESOURCE_BITMASK_RE6 = 0b0000000100000000
RESOURCE_BITMASK_RE7 = 0b0000000010000000
RESOURCE_BITMASK_RE8 = 0b0000000001000000
RESOURCE_BITMASK_RE9 = 0b0000000000100000
RESOURCE_BITMASK_REA = 0b0000000000010000
RESOURCE_BITMASK_REB = 0b0000000000001000
RESOURCE_BITMASK_REC = 0b0000000000000100
RESOURCE_BITMASK_RED = 0b0000000000000010
RESOURCE_BITMASK_REE = 0b0000000000000001

#RESOURCE['ssd'][RESOURCE_BITMASK_SSD]
#RESOURCE['nic'][RESOURCE_BITMASK_NIC]
#RESOURCE['re1'][RESOURCE_BITMASK_RE1]
#RESOURCE['re2'][RESOURCE_BITMASK_RE2]
#RESOURCE['re3'][RESOURCE_BITMASK_RE3]
#RESOURCE['re4'][RESOURCE_BITMASK_RE4]
#RESOURCE['re5'][RESOURCE_BITMASK_RE5]
#RESOURCE['re6'][RESOURCE_BITMASK_RE6]
#RESOURCE['re7'][RESOURCE_BITMASK_RE7]
#RESOURCE['re8'][RESOURCE_BITMASK_RE8]
#RESOURCE['re9'][RESOURCE_BITMASK_RE9]
#RESOURCE['rea'][RESOURCE_BITMASK_REA]
#RESOURCE['reb'][RESOURCE_BITMASK_REB]
#RESOURCE['rec'][RESOURCE_BITMASK_REC]
#RESOURCE['red'][RESOURCE_BITMASK_RED]
#RESOURCE['ree'][RESOURCE_BITMASK_REE]

def createProcess( time, resources, priority ):
	global current_pid
	current_pid += 1
	# Pid, Time, Resources, Priority
	print "newTask( " + str(current_pid) + ", " + str(time) + ", " + str(resources) + ", " + str(priority) + " );"

def readConfig( path ):
	try:
		file = open( path, 'r')
		data = json.load(file)
		return data
	except IOError:
		print path + " not found"

dirname = "./processes"

for f in os.listdir(dirname):
	active = dirname + "/" + f
	if os.path.isfile( active ):
		try:
			data = readConfig( active )
			resources = data['resources']
			rMask = 0 # ToDo: Fixme
			global RESOURCE

#			for r in resources:
#				try:
#					rMask += RESOURCE[r]
#				except KeyError as e:
#					print "Error parsing resource " + r
			createProcess( data['time'], rMask, data['priority'] )
		except KeyError as e:
			print "Malformed config file. Check " + active

