#!/usr/bin/env python

from optparse import OptionParser
import CherryTree
import sys
import os

def isset(var):
	try: var
	except NameError:
		return False
	return True

usage = "usage: %prog [options] arg1 arg2"
parser = OptionParser(usage=usage)

parser.add_option(
        "-d",
        "--debug",

        action  = "store_true",
        dest    = "debug",
        default = False,
        help    = "Add debugging"
)

parser.add_option(
        "-v",
        "--version",

        action  = "store_true",
        dest    = "version",
        default = False,
        help    = "Version of CherryTree"
)

(options, args) = parser.parse_args()

if options.version:
	print CherryTree.CherryTreeGlobals.CHERRYTREE_STRING
	exit

if options.debug:
	print "// Enable debugging mode. It's on."
	print "debugging_mode();";
	CherryTree.CherryTreeGlobals.DEBUGGING = 1


cc = CherryTree.CherryTree()
cc.compileProcesses( "./processes" )
