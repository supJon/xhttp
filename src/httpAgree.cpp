//
// Created by jon on 2020/12/2.
//



#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include "httpAgree.h"

httpAgree::httpAgree() {
    std::cout << "Initializes the HTTP protocol." << std::endl;
    memset(char_buf, 0, sizeof(char_buf));
    memset(data_buf, 0, sizeof(data_buf));
}


void httpAgree::_http_handle() {
//    memset(char_buf,0,sizeof(char_buf));
//    memset(data_buf,0,sizeof(data_buf));
//    char * buf_=(char*)malloc(128);
//    strcat(char_buf,                              "HTTP/1.1 200 OK");
//    strcat(char_buf, "GET /ymnets/p/6255674.html HTTP/1.1\n");
//    strcat(char_buf,               "Host: www.cnblogs.com\n");
//    strcat(char_buf,             "Content-Type: text/html\n");
//    strcat(char_buf,                      "Content-Length: ");
//    strcat(char_buf,                                       buf_);
//    strcat(char_buf,                                  "\n\n");
//    strcat(char_buf,                         "theDataToPost");
//    strcat(char_buf,                              "\r\n\r\n");




}


void httpAgree::_http_request(int _fd) {
    _http_handle();
    char Protocol[] = "HTTP/1.1 200 OK\r\n";
    char ServerType[] = "Server:MyWebServer\r\n";
    char ContentLen[] = "Content-length:2048\r\n";
    char ContentType[] = "Content-type:text/html\r\n";
    char *filename = "/home/jon/aio.html";
    char buffer[BUF_SIZE] = {0};
    FILE *fp;
    if ((fp = fopen(filename, "r")) != NULL) {

        // 传输头数据
        send(_fd, Protocol, strlen(Protocol), 0);
        send(_fd, ServerType, strlen(ServerType), 0);
        send(_fd, ContentLen, strlen(ContentLen), 0);
        send(_fd, ContentType, strlen(ContentType), 0);
        while (fgets(buffer, BUF_SIZE, fp) != NULL)
            send(_fd, buffer, strlen(buffer), 0);
        std::cout << "###########" << _fd << std::endl;

    }

}

void httpAgree::_http_response(int _fd) {

    if (recv(_fd, data_buf, sizeof(data_buf), 0) < 0) {

    }


}


httpAgree::~httpAgree() {

    std::cout << "溜了溜了 HTTP." << std::endl;
}



