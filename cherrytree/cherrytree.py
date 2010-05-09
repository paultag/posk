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

parser.add_option(
	"-p",
	"--process-dir",
	action    = "store",
	type      = "string",
	default   = "./processes/",
	dest      = "process_path",
        help      = "Use this folder for the JSON process defaults"
)


(options, args) = parser.parse_args()

if options.version:
	print CherryTree.CherryTreeGlobals.CHERRYTREE_STRING
	sys.exit(0)


if options.debug:
	print "debugging_mode();";
	CherryTree.CherryTreeGlobals.DEBUGGING = 1


cc = CherryTree.CherryTree()
cc.compileProcesses( options.process_path )

