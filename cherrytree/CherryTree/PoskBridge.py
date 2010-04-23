import CherryTree.CherryTreeGlobals

CHERRYTREE_CURRENT_PID = 0

def createProcess( time, resources, priority ):
	global CHERRYTREE_CURRENT_PID
	CHERRYTREE_CURRENT_PID += 1

	if CherryTree.CherryTreeGlobals.DEBUGGING == 1:
		print "d_printk(\"Creating new process ( %d )\\n\", " + str(CHERRYTREE_CURRENT_PID) + ");"

	print "newTask( " + str(CHERRYTREE_CURRENT_PID) + ", " + str(time) + ", " + str(resources) + ", " + str(priority) + " );"


