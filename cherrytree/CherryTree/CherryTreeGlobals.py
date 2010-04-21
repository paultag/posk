import CherryTree.PoskBridge
import json

CHERRYTREE            = "CherryTree"
CHERRYTREE_VERSION    = "0.0zed1"
CHERRYTREE_NAME       = "Recursive Rock"

CHERRYTREE_COPYRIGHT_NAME  = "Paul Tagliamonte, Pat McDonnell"
CHERRYTREE_COPYRIGHT_PROF  = "Dr. Kirschenbaum"
CHERRYTREE_COPYRIGHT_ORG   = "John Carroll University"
CHERRYTREE_COPYRIGHT_DATE  = "2010"

CHERRYTREE_STRING = CHERRYTREE + " v" + CHERRYTREE_VERSION + " ( " + CHERRYTREE_NAME + " ) Copyright " + CHERRYTREE_COPYRIGHT_DATE + " (c) GPLv3.\n\nWritten by: " + CHERRYTREE_COPYRIGHT_NAME + ".\nAdvised by: " + CHERRYTREE_COPYRIGHT_PROF + " ( " + CHERRYTREE_COPYRIGHT_ORG + " )."


DEBUGGING = 0;


def readConfig( path ):
	try:
		file = open( path, 'r')
		data = json.load(file)
		return data
	except IOError:
		print path + " not found"

