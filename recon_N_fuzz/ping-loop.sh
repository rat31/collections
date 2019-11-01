#!/bin/bash

network=$1
for n in 0 36 48; do network=$1.$n; for ip in $(seq 1 254); do 
ping -c 1 $network.$ip| grep "bytes from"|cut -d" " -f4| cut -d":" -f1 & 
done; done 
