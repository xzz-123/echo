# socket 编程实践
client.cpp和server.cpp组成一个基于socket编程实现的回声系统  
其功能为：服务器从客户端接收字符串，并将该字符串传回给客户端。  

服务器端代码是运行在linux环境下的。  

客户端代码则是windows平台下运行。  

clientFile.cpp与serverFile.cpp实现的是服务器向客户端提供传输文件功能。   

clientUDP,serverUDP则使用UDP协议实现回声系统，其余的使用TCP协议  

