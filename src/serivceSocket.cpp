//
// Created by jon on 2020/11/29.
//
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/epoll.h>
#include<fcntl.h>
#include "serviceSocket.h"


serviceSocket::serviceSocket(unsigned short port) : port(port) {}

serviceSocket::~serviceSocket() {close(s_socket);}

void serviceSocket::init() {
    s_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (s_socket == -1)
        std::cout << "1unkown error,give over!" << std::endl;

    _bind();
}

void serviceSocket::_bind() {
    struct sockaddr_in sockadd_;
    sockadd_.sin_family = AF_INET;
    sockadd_.sin_addr.s_addr = htonl(INADDR_ANY);
    sockadd_.sin_port = htons(port);
    if (bind(s_socket, (struct sockaddr *) &sockadd_, sizeof(sockadd_)) == -1){
        std::cout << "2unkown error,give over!" << std::endl;
        _close();
    }

    _listen();
}

void serviceSocket::_listen() {
    if (listen(s_socket, 5) == -1){
        std::cout << "3unkown error,give over!" << std::endl;
        _close();
    }

    RunSocket();

}


[[noreturn]] void serviceSocket::RunSocket() {
    int epoll_fd=epoll_create(512);

    if(epoll_fd<0)
    {
        std::cout << "4unkown error,give over!" << std::endl;
        _close();
    }

    struct epoll_event _eve;
    struct epoll_event _ret_ev[MAX_POLL];
    _eve.events=EPOLLIN;
    _eve.data.fd=s_socket;
    if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,s_socket,&_eve)<0)
    {
        std::cout << "5unkown error,give over!" << std::endl;
        _close();
    }

    struct sockaddr_in client;
    socklen_t on_len=sizeof(client);
    bool isRun= true;
     while (isRun){

        int read_poll=epoll_wait(epoll_fd,_ret_ev,MAX_POLL,0);
        for(int i=0; i < read_poll; ++i){
            int _sock_fd=_ret_ev[i].data.fd;
            if(_sock_fd==s_socket&&(_ret_ev[i].events&EPOLLIN)){

                //新加入请求处理
                int n_sock=accept(_ret_ev[i].data.fd,(struct sockaddr*)&client,&on_len);
                if(n_sock<0){
                    std::cout << "6unkown error,give over!" << std::endl;
                    _close();
                    close(_sock_fd);
                }
                //设置epoll 为非阻塞模式
                //将新请求fd加入epoll中，并设置边缘触发
               add_sock_fd(epoll_fd,n_sock, true);

                //
            }else{
            //原有socket请求处理

            }

        }

    }
}
int serviceSocket::set_no_block(int _fd) {

    int old_fl=fcntl(_fd,F_GETFL);
    if(old_fl<0)
    {
        std::cout << "7unkown error,give over!" << std::endl;
        return -1;
    }
    if(fcntl(_fd,F_SETFL,old_fl|O_NONBLOCK))
    {
        std::cout << "8unkown error,give over!" << std::endl;
        return -1;
    }
    return 0;


}

void serviceSocket::add_sock_fd(int _epoll_fd, int _fd, bool _enable_) {
    struct epoll_event ev;
    ev.data.fd = _fd;
    ev.events = EPOLLIN;
    if( _enable_ )
        ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, _fd, &ev);
   int _is_add_fd= set_no_block(_fd);
   if(_is_add_fd<0)
        _close();
        close(_fd);



}
void serviceSocket::_close() {close(s_socket);}



