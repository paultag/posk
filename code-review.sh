#!/bin/bash

RS=0
WORD=0
FILE=0
COUNT=0

function checkMe() {
	if [ "x$(echo $WORD | grep fuck)" != "x" ]; then
		echo $FILE contains \"fuck\"
	fi
        if [ "x$(echo $WORD | grep shit)" != "x" ]; then
                echo $FILE contains \"shit\"
        fi
        if [ "x$(echo $WORD | grep sucks)" != "x" ]; then
                echo $FILE contains \"sucks\"
        fi
        if [ "x$(echo $WORD | grep ToDo)" != "x" ]; then
                echo $FILE contains items todo
        fi
}

FILES=$(find . -type f | grep -v .svn | grep -v devel-tools | grep -v docs)
for FILE in $FILES; do
	if [ "x$(file $FILE | grep text)" != "x" ]; then
	if [ "x$FILE" != "x$0" ]; then
# 		echo "Looking at non-binary file $FILE"
		CATSKI=$(cat $FILE)
		for WORD in $CATSKI; do
			checkMe;
			let COUNT=$COUNT+1
		done;
	fi
	fi
done;

echo "Reviewed $COUNT words."

