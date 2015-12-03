#!/bin/bash
# testing the if statement
if date
then 
	echo "it worked."
fi

testuser=test
if grep $testuser /etc/passwd
then
	echo The bash file for user $testuser are:
	ls -a /home/$testuser/.z*
else
	echo "The user named with $testuser don't exist at system."
fi
