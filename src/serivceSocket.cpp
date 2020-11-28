//
// Created by jon on 2020/11/29.
//
#include <iostream>
#include <sys/socket.h>
#include<netinet/in.h>
#include "serviceSocket.h"
#include <unistd.h>

serviceSocket::serviceSocket(unsigned short port) : port(port) {}

serviceSocket::~serviceSocket() {close(s_socket);}

void serviceSocket::init() {
    s_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (s_socket == -1)
        std::cout << "unkown error,give over!" << std::endl;

    _bind();
}

void serviceSocket::_bind() {
    struct sockaddr_in sockadd_;
    sockadd_.sin_family = AF_INET;
    sockadd_.sin_addr.s_addr = htonl(INADDR_ANY);
    sockadd_.sin_port = htons(port);
    if (bind(s_socket, (struct sockaddr *) &sockadd_, sizeof(sockadd_)) == -1)
        std::cout << "unkown error,give over!" << std::endl;
        close(s_socket);
    _listen();
}

void serviceSocket::_listen() {
    if (listen(s_socket, 5) == -1)
        std::cout << "unkown error,give over!" << std::endl;
        close(s_socket);


}



