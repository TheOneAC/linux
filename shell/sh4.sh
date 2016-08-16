#!/bin/bash

until [ -z "$1" ]       # untill all the arg used
do
	echo -n "$1 "	# show the first arg
        shift           # chane to the next arg, shift n move back n 
done
echo 
exit 0
