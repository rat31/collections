#!/usr/bin/python
import socket
import sys
import time

if len(sys.argv) !=2: #sys.argv is argument after the name of the script
    print "[*] Usage: sys.argv[0] <filename.txt>" #sys.argv[0] = the name of the script
    sys.exit(0)

ip =raw_input("host number?: ")
usr = open(sys.argv[1])
# Create a Socket
s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Connect to the Server
connect=s.connect(('10.11.1.'+ip,25))
# Receive the banner
banner=s.recv(1024)
print banner
time.sleep(5)
# VRFY a user
for line in usr: 
    s.send('VRFY ' +line+ '\r')
    result=s.recv(1024)
    print result
    time.sleep(2)
# Close the socket
s.close()

