#!/usr/bin/env python

import os

try:
	import json
except:
	import simplejson as json

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
		data = readConfig( active )
		print "Using process `" + data['name'] + "` ( expected run of " + data['time'] + " units )"
