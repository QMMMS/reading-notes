#!/bin/bash

users=$(cut -d ':' -f1 /etc/passwd)
for username in ${users}
do
	id ${username}
done

exit 0
