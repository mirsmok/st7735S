#!/bin/bash
while :
do
	id=`ps -A | grep IQhome`
	#echo $id
	if [ -z "$id" ]
	then
		echo "nie ma takiego proceu"
		date
		(date && echo "zatrzymany") >> log
	#	/usr/local/bin/IQhome&
	fi
	sleep 60
done
