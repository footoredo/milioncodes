#!/bin/bash

echo Deleting exes...
for file in ./*/*/*/*/*/* 
do
	#echo Checking file $file..
	if [ `echo $file | grep 'exe$'` ]
	then
		echo Deleting $file..
		rm $file
	fi
done
echo Completed.

