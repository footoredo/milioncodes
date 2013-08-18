#!/bin/bash

echo Renaming cpp files...
for file in ./*/*.cpp
do
	new_file=`echo $file|cut -d '/' -f 2`".cpp"
	echo Renaming $file to $new_file...
	mv $file $new_file
done
echo Completed.