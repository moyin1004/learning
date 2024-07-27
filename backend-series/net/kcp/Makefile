all:server client

server:kcp_echo_server.cc
	g++ -o server kcp_echo_server.cc ikcp.c -g -Wall -lpthread -std=c++20
client:kcp_client.cc
	g++ -o client kcp_client.cc ikcp.c -g -Wall -lpthread -std=c++20