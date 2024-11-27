import socket
s_server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s_server.bind(('',12345))

while(True):
    data, clientaddr = s_server.recvfrom(4096)
    print(clientaddr[0]+","+str(clientaddr[1])+ " ha dicho:", data.decode())
    s_server.sendto(b'Calvo', (clientaddr[0],clientaddr[1]))   
s_server.close()
