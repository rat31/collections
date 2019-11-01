import socket

print ("\nGetting IP Address of a Domain Name")
print ("\nAuthor st4rry")

dn = raw_input ("\nEnter the Domain Name: ")

data = socket.gethostbyname_ex(dn)
print ('\n \n The IP Address of the Domain Name is: '+ repr(data))

