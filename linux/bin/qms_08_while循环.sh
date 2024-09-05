#!/bin/bash

while [ "${yn}" != "yes" -a "${yn}" != "YES" ] 
do
	read -p "input yes/YES to end this script : " yn
done

echo "right input and script will exit"

exit 0
