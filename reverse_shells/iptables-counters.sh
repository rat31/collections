#!/bin/bash
read -p 'source ip: ' soip
read -p 'dest ip: ' deip
#reset all counters and IP tables rules
iptables -Z && iptables -F
#measure incoming traffic
iptables -I INPUT 1 -s $soip -j ACCEPT
#measure incoming traffic
iptables -I OUTPUT 1 -d $deip -j ACCEPT
sleep 1
iptables -vn -L
