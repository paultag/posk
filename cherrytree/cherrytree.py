#!/usr/bin/env python

import os

try:
	import json
except:
	import simplejson as json

current_pid = 0;

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
			createProcess( data['time'], rMask, data['priority'] )
		except KeyError as e:
			print "Malformed config file. Check " + active

