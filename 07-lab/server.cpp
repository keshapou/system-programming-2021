#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <array>

struct client_info
{
	int sockno;
	char ip[INET_ADDRSTRLEN];
};

std::array<int, 100> clients;

int n = 0;

std::mutex mx;

void send_to_all(char* msg, int curr)
{
	std::lock_guard<std::mutex> lock(mx);

	for (size_t i = 0; i < n; ++i) 
	{
		if (clients[i] != curr) 
		{
			if (send(clients[i], msg, strlen(msg), 0) < 0) 
			{
				std::cerr << "Error: sending failed\n";
				continue;
			}
		}
	}

}

void receive_msg(struct client_info sock)
{
	std::cout <<  "receive msg...\n";

	char msg[500];
	int len;
	int j;

	while ((len = recv(sock.sockno,msg,500,0)) > 0) 
	{
		msg[len] = '\0';
		send_to_all(msg, sock.sockno);
		memset(msg, '\0' ,sizeof(msg));
	}

	std::lock_guard<std::mutex> lock(mx);

	printf("%s disconnected\n", sock.ip);

	for(size_t i = 0; i < n; ++i) 
	{
		if (clients[i] == sock.sockno) 
		{
			j = i;
			while (j < n-1) 
			{
				clients[j] = clients[j+1];
				j++;
			}
		}
	}

	n--;
}

int main(int argc,char *argv[])
{
	std::cout << "Server is running" << std::endl;

	const std::string localhost = "127.0.0.1";
	struct sockaddr_in my_addr, their_addr;
	int their_sock;
	socklen_t their_addr_size;
	char msg[500];
	struct client_info cl;
	char ip[INET_ADDRSTRLEN];

	if (argc > 2) 
	{
		std::cout << "Usage: ./server <port>\n";
		exit(1);
	}

	int portno = atoi(argv[1]);
	int sock = socket(AF_INET,SOCK_STREAM,0);
	memset(my_addr.sin_zero, '\0', sizeof(my_addr.sin_zero));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(portno);
	my_addr.sin_addr.s_addr = inet_addr(localhost.c_str());
	their_addr_size = sizeof(their_addr);

	if (bind(sock,(struct sockaddr *)&my_addr, sizeof(my_addr)) != 0)  
	{
		std::cerr << "Error: binding failed\n";
		return -1;
	}

	if (listen(sock, 5) != 0) 
	{
		std::cerr << "Error: listening failed\n";
		return -1;
	}

	while (true) 
	{
		their_sock = accept(sock, (struct sockaddr *)&their_addr, &their_addr_size);
		if (their_sock < 0) 
		{
			std::cerr << "Error: accepting failed\n";
			return -1;
		}

		std::thread th;
		std::lock_guard<std::mutex> lock(mx);
		{
			inet_ntop(AF_INET, (struct sockaddr *)&their_addr, ip, INET_ADDRSTRLEN);
			printf("%s connected\n", ip);
			cl.sockno = their_sock;
			strcpy(cl.ip, ip);
			clients[n++] = their_sock;
			th = std::thread(receive_msg, cl);
		}

		th.detach();
	}

	close(sock);
	return 0;
}