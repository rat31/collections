#!/bin/bash

echo :::::::::::::::::::::::::::::::
echo ::Simple Zone Transfer Script::
echo :::::::::::::::::::::::::::::::

#$1 is the argument of the 1st place, given after the bash script ($0)

#Check if an argument was given, if not, print usage

if [ -z "$1" ]; then
echo "[*] Make sure you defined a domain name"
echo "[*] Usage : $0 <domain name>"
exit 0
fi

#if an argument was given , Identify the DNS servers for the domain using the command:host -t ns <domain name>

for dnssvr in $(host -t ns $1 | cut -d" " -f 4);do

#for each of these servers got from host -t ns, attempt a zone transfer

host -l $1 $dnssvr | grep "has address"
done
