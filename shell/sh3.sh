#!/bin/bash
v=23
echo $v    # the simple of ${v}
a=$v
echo $a    # the assignment of varible
hello="A A A      D"
echo "$hello"   #A A A      D "" preserve the whitespace
echo $hello     #A A A D
echo '$hello'   #there is no escape in ''
hello=    
echo "\$hello(null)= $hello#"
read a
echo $a


a='ls -l'
echo $a
echo 
echo "$a"   ## no change

h=$(ls -l)  ##call son function
echo $h
exit 0
