#!/usr/bin/env python

import os

try:
	import json
except:
	import simplejson as json

def createProcess( name, time ):
	print "newTask( " + time + " );"

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
			createProcess( "Process", data['time'] )
		except KeyError as e:
			print "Malformed config file. Check " + active

