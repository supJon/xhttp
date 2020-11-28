//
// Created by jon on 2020/11/29.
//

#ifndef MYSERVICE_SERVICESOCKET_H
#define MYSERVICE_SERVICESOCKET_H
#define SOCKET int
class serviceSocket{
public:
    serviceSocket(unsigned short port=8888);

    void init();
    void _bind();
    void _listen();
    bool RunSocket();
    ~serviceSocket();
private:

    SOCKET s_socket;
    unsigned short port;
};
#endif //MYSERVICE_SERVICESOCKET_H
