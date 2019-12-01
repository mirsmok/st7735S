#!/bin/bash
process=`ps -A | grep IQhome`
if [ -z "$process" ]
then
	echo "start IQhome..."
	(date && echo "start IQhome...") >> /var/logIQhome
	/usr/local/bin/IQhome&
fi
sleep(1)
while :
do
	id=`ps -A | grep IQhome`
	if [ -z "$id" ]
	then
		echo " "
		date
		echo "wznawiam IQhome..."
		(date && echo "wznawiam IQhome") >> /var/logIQhome
		/usr/local/bin/IQhome&
	fi
	sleep 60
done
