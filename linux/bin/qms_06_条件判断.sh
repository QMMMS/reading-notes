#!/bin/bash

read -p "please input (Y/N) : " yn

if [ "${yn}" == "Y" ] || [ "${yn}" == "y" ]; then
	echo "you input yes"
elif [ "${yn}" == "N" ] || [ "${yn}" == "n" ]; then
	echo "you input no"
else
	echo "wrong input"
fi			

exit 0
	
