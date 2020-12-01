//
// Created by jon on 2020/11/29.
//

#ifndef MYSERVICE_SERVICESOCKET_H
#define MYSERVICE_SERVICESOCKET_H
#define SOCKET int
#define MAX_POLL 1024
class serviceSocket{
public:
    serviceSocket(unsigned short port=8888);

    void init();
    void _bind();
    void _listen();
    void _close();

    [[noreturn]] void RunSocket();
    void add_sock_fd(int _epoll_fd, int _fd, bool _enable_ );
    int set_no_block(int _fd);
    ~serviceSocket();
private:

    SOCKET s_socket;
    unsigned short port;
};
#endif //MYSERVICE_SERVICESOCKET_H
