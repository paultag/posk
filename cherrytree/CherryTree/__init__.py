import CherryTree.CherryTreeGlobals
import CherryTree.PoskBridge

import os
import sys

class CherryTree:

	def compileProcesses(self, dirname):
		for f in os.listdir(dirname):
			active = dirname + "/" + f
			if os.path.isfile( active ):
				try:
					data = CherryTreeGlobals.readConfig( active )
					resources = data['resources']
					rMask = 0 # ToDo: Fixme
					global RESOURCE
					PoskBridge.createProcess( data['time'], rMask, data['priority'], data['start'],  active )
				except KeyError as e:
					sys.stderr.write( "\n** Critical Error **\nMalformed config file. Check `" + active + "`\n\n" )
					sys.exit(-1)

