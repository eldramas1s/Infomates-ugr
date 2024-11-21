import socket

s_client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s_client.sendto(b'Hola clase', ('localhost',12345))
data,serveraddr = s_client.recvfrom(12345)
print(data.decode()+ " desde el puerto " +str(serveraddr[1]))
s_client.close()
