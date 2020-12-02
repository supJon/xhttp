//
// Created by jon on 2020/12/2.
//



#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include "httpAgree.h"

httpAgree::httpAgree() {
    std::cout<<"Initializes the HTTP protocol."<<std::endl;
    memset(char_buf,0,sizeof(char_buf));
    memset(data_buf,0,sizeof(data_buf));
}


void httpAgree::_http_handle() {
    memset(char_buf,0,sizeof(char_buf));
    memset(data_buf,0,sizeof(data_buf));
    char * buf_=(char*)malloc(128);
    strcat(char_buf, "GET /ymnets/p/6255674.html HTTP/1.1\n");
    strcat(char_buf,               "Host: www.cnblogs.com\n");
    strcat(char_buf,             "Content-Type: text/html\n");
    strcat(char_buf,                      "Content-Length: ");
    strcat(char_buf,                                       buf_);
    strcat(char_buf,                                  "\n\n");
    strcat(char_buf,                         "theDataToPost");
    strcat(char_buf,                              "\r\n\r\n");
}


void httpAgree::_http_request(int  _fd) {
    _http_handle();
    int _in_send=send(_fd,char_buf,sizeof(char_buf),0);

    std::cout<<"###########"<<_in_send<<std::endl;
    if(_in_send<0){
        std::cout<<"send data error."<<std::endl;
    }

}

void httpAgree::_http_response(int _fd) {

    if(recv(_fd,data_buf,sizeof(data_buf),0)<0){

    }


}


httpAgree::~httpAgree() {

    std::cout<<"溜了溜了 HTTP."<<std::endl;
}



