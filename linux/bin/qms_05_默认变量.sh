#!/bin/bash

echo "script name is ${0}" 			#脚本名称
echo "total number of para is ${#}"	#参数总个数

#如果参数总个数小于2，则...
[ "${#}" -lt 2 ] && echo "number of para should larger or equal 2" && exit 0

echo "whole para is '${@}'"			#全部参数
echo "1st para is '${1}'"			#第一个参数
echo "2nd para is '${2}'"			#第二个参数

shift								#参数偏移，拿掉最前面的参数
echo "whole para is '${@}'"			

exit 0
