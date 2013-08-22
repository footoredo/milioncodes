#!/bin/bash

echo Getting rid of spaces...
for file in ./*/*/*/*/* 
do
        new_file=`echo $file|tr " " "_"`
        if [ "$new_file" != "$file" ] 
	then
		echo Renaming $file to $new_file...
		mv "$file" $new_file 
	fi
done
echo Completed.

