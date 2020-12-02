//
// Created by jon on 2020/12/2.
//

#ifndef MYSERVICE_HTTPAGREE_H
#define MYSERVICE_HTTPAGREE_H
#define BUF_SIZE  4096

//http协议
class httpAgree{
public:
    httpAgree();
    ~httpAgree();
    void _http_handle();
    void _http_request(int );
    void _http_response(int);

private:
    char char_buf[BUF_SIZE],data_buf[BUF_SIZE];



};



#endif //MYSERVICE_HTTPAGREE_H
