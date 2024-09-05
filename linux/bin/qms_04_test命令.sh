#!/bin/bash

read -p "input a file name : " filename

#-z 判断字符串是否为空，空为true
test -z ${filename} && echo -e "no input" && exit 0
 
#-e 判断文件是否存在，存在为true，!取反
test ! -e ${filename} && echo "${filename} don't exist" && exit 0

test -f ${filename} && echo "${filename} is a file"
test -d ${filename} && echo "${filename} is a directory"
test -r ${filename} && echo "${filename} can read"
test -w ${filename} && echo "${filename} can write"
test -e ${filename} && echo "${filename} can execute"

exit 0

 
