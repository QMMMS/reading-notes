#!/bin/bash

ans=$((2 + 3))		#如果需要进行数值运算建议这么写
echo -e "2 + 3 = ${ans}"


#bash命令只支持整数的运算，如果需要小数运算，可以利用bc命令
ans=$(echo "123.123*55.9" | bc)
echo -e "123.123 * 55.9 = ${ans}"


exit 0
