#!/bin/bash
for ip in $(seq 70 90);do
    host 38.100.193.$ip | grep "megacorp" |cut -d " " -f1,5
done
