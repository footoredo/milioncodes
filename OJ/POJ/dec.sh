#!/bin/bash

echo Preparing to decompress files..
for file in ./*.7z
do
	new_file=`echo $file|tr " " "_"`
	echo Renaming $file to $new_file...
	mv "${file}" ${new_file}
done
echo Completed.

echo Decompressing files..
for file in ./*.7z
do
	d_dir=`echo $file|cut -d'.' -f 1-2`"/"
	echo Decompressing $file into $d_dir..
	7za X $file -o$d_dir
done
echo Completed.