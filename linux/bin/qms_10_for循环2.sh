#!/bin/bash


function processing() {
	flg=$((${1}*30/${2}))
	echo -ne "\rprocessing["		#\r表示跳到行开头覆盖输出
	for ((j=1; j<=${flg}; j=j+1))
	do
		echo -n "="					#-n表示不输出换行符
	done
	
	for ((j=$((${flg}+1)); j<=30; j=j+1))
	do
		echo -n " "
	done
	echo -n "]"
}


read -p "input a number : " num

sum=0
for ((i=1; i<=${num}; i=i+1))
do
	sum=$((${sum}+${i}))
	processing ${i} ${num}
done

echo ""
echo "1+2+3+....${num} = ${sum}"

exit 0
