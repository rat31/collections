#!/usr/bin/python
import argparse
from socket import *
import time
import sys

print """           _  _____  __ 
          | | |___ \/_ |
 _ __ __ _| |_  __) || |
| '__/ _` | __||__ < | |
| | | (_| | |_ ___) || |
|_|  \__,_|\__|____/ |_| """
print "\n"
print "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
print "@@Knock knock knocking on heaven's door@@"
print "@@-----------Author: rat31-------------@@"
print "@@-------Name: pk(portknocker)---------@@"
print "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
print "\n"


if len(sys.argv) < 2:
  print "Usage               : python pk.py <target IP> <port_sequence> <timeout>"
  print "Example             : python pk.py 10.11.0.100 '22 21 23' 500"
  sys.exit(0)

ip = sys.argv[1]
port = sys.argv[2]
d = sys.argv[3]
delay = (int(d)/1000)

intport = [int(p) for p in port.split( )]

#    ip = raw_input("Target IP address: ")
#    port = raw_input("A sequence of Target port number: ")
#    intport = [int(p) for p in port.split()]

for po in (intport):
    try:
        print ("knocking on port:", po)
        s = socket(AF_INET, SOCK_STREAM)
        s.settimeout(delay)
        s.connect((ip, po))
        #print s.recv(1024)
        rec = eval(s.recv(1024))
        print "received:", rec
    except:
        pass
        time.sleep(delay)
    print "knocked out"
print "DONE!"
