#!/bin/bash

function printInfo() {
	echo "your choice is ${1}"	#函数参数
}

case ${1} in 
 "one")
	printInfo 1
	;;
 "two")
	printInfo 2
	;;
 "three")
	printInfo 3
	;;
 *)
	echo "usage : ${0} {one|two|three}"
	;;
esac

exit 0;
