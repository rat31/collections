#!/bin/bash

for ip in $(seq 70 90); do 
#echo 84.88.235.$ip
ping -c 1 84.88.235.$ip| grep "bytes from"|cut -d" " -f4| cut -d":" -f1 & 
done
