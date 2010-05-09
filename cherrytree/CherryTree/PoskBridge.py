import CherryTree.CherryTreeGlobals

CHERRYTREE_CURRENT_PID = 0

def createProcess( time, resources, priority, start, name ):
	global CHERRYTREE_CURRENT_PID
	CHERRYTREE_CURRENT_PID += 1

	if CherryTree.CherryTreeGlobals.DEBUGGING == 1:
		print "d_printk(\"Creating new process ( %d ) -- %s\\n\", " + str(CHERRYTREE_CURRENT_PID) + ", \"" + name + "\");"

	print "newTask( " + str(CHERRYTREE_CURRENT_PID) + ", " + str(time) + ", " + str(resources) + ", " + str(priority) + ", " +str(start) + " ); // " + name


