//============================================================================
// Name        : SocketServer.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

#define PORT 1234
#define MAXDATASIZE 100
#define BACKLOG 1

int main(void) {
	int listenfd, connectfd;
	pthread_t tid;
	struct sockaddr_in server;
	struct sockaddr_in client;
//	socklen_t addrlen;
	unsigned int sin_size;

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket() error.");
		exit(-1);
	}

	int opt = SO_REUSEADDR;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(listenfd, (struct sockaddr *) &server, sizeof(server)) == -1) {
		cout << server.sin_addr.s_addr << endl;
		perror("bind() error");
		exit(1);
	}
	cout << "bind finish" << endl;

	if (listen(listenfd, BACKLOG) == -1) {
		perror("listen() error");
		exit(-1);
	}
	cout << "listen finish" << endl;

//	addrlen = sizeof(client);
	sin_size = sizeof(struct sockaddr_in);
	while (1) {
		if ((connectfd = accept(listenfd, (struct sockaddr *) &client, &sin_size))
				== -1) {
			perror("accept() error");
			exit(-1);
		}

	}
	close(listenfd);
}
