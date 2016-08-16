#!/bin/bash
#  /bin/bash -v，show the source code
who   		 #show who the users are
uptime         	#update description
echo $(date)    #show the cur-time
echo "hello,world"
echo "this is a #"
echo {a..z}	#show a b c .... z
a=3
b=7
echo $[ $a+$b]  #compute expression
for i in {1..10}
do 	
	echo -n "$i"
done
echo 
#kill -9 id   :kill the thread

