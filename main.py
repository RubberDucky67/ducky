#TCP
import socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("127.0.0.1",1234))
s.listen(1)
print("TCP Server ready for addition")
c, addr = s.accept()
data = c.recv(1024).decode()
a, b = map(float, data.split())
print("Received: ", a, b)
c.send(str(a+b).encode())
c.close()
s.close()

import socket
c = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
c.connect(("127.0.0.1", 1234))
print("Connectd to Server")
a = float(input("Enter First Number: "))
b = float(input("Enter Second Number: "))
c.send(f"{a} {b}".encode())
print("Result from Server: ", c.recv(1024).decode())
c.close()

#UDP
import socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(("127.0.0.1", 1234))
print("UDP Server ready for addition.")
data, addr = s.recvfrom(1024)
a, b = map(float, data.decode().split())
result = a + b
print("Received: ", a, b)
s.sendto(str(result).encode(), addr)

import socket
c = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
a = float(input("Enter First Number: "))
b = float(input("Enter Second Number: "))
c.sendto(f"{a} {b}".encode(), ("127.0.0.1",1234))
data, addr = c.recvfrom(1024)
print("Result from Server: ", data.decode())