#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <thread>
#include <iostream>
#include <string>

void receive_msg(int sock)
{
	const size_t buf_size = 500;
	char msg[buf_size];
	size_t len;

	while ((len = recv(sock, msg, buf_size, 0)) > 0) 
	{
		msg[len] = '\0';
		// fputs(msg,stdout);
		std::cout << msg << std::endl;
		memset(msg, '\0', sizeof(msg));
	}
}

int main(int argc, char *argv[])
{
	const std::string localhost = "127.0.0.1";
	struct sockaddr_in their_addr;
	int their_sock;
	int their_addr_size;
	char ip[INET_ADDRSTRLEN];

	if (argc > 3) 
	{
		std::cout << "Usage: ./client <username> <port>\n";
		return -1;
	}

	int portno = atoi(argv[2]);
	std::string username = argv[1];
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	memset(their_addr.sin_zero, '\0', sizeof(their_addr.sin_zero));
	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(portno);
	their_addr.sin_addr.s_addr = inet_addr(localhost.c_str());

	if (connect(sock, (struct sockaddr *)&their_addr, sizeof(their_addr)) < 0) 
	{
		std::cerr << "Error: connection not esatablished\n";
		return -1;
	}

	inet_ntop(AF_INET, (struct sockaddr *)&their_addr, ip, INET_ADDRSTRLEN);
	printf("connected to %s, start chatting\n",ip);
	std::thread th = std::thread(receive_msg, sock);

	std::string msg;
	// while (fgets(msg,500,stdin) > 0) 
	while (std::getline(std::cin, msg))
	{
		std::string res = username + std::string(": ") + msg;	
		size_t len = write(sock, res.c_str(), res.size());
		if (len < 0) 
		{
			std::cerr << "Error: sending failed\n";
			return -1;
		}

		msg = "";
	}

	th.join();
	close(sock);

	return 0;
}