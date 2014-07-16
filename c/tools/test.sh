#!/bin/bash

CAT=./bin/cat
TESTFILE=./src/cat.c
testcat() {
	make cat
	if ! diff <($CAT $TESTFILE) <(cat $TESTFILE) > /dev/null
	then
		echo Cat test failed. $ourbin $testfile != cat $testfile
	else
		echo -n '.'
	fi
}

# add new tests here, have them do `echo -n '.'` if success.
testcat

echo
echo Tests complete.
make clean
