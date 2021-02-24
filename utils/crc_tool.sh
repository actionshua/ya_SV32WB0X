#!/bin/sh

crc=0
dec=$line

while read line
do
#echo "The line is $line ( $(($line)) )"

#echo "==============================="
while [ $(($line)) -gt 0 ]
do
crc=$(( $crc + 1 ))
line=$((line & $(( $line - 1))))
#echo "The crc is $(($crc))"
done
#echo "==============================="
done

#echo "The final crc is:"
echo "obase=10; $(( 511 - $crc ))"| bc| awk '{printf "%04X\n", $1}'| fold -w2| tac| tr -d "\n"

