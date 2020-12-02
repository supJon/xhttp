
#include <iostream>
//#include "src/threadPool.h"
#include "src/serviceSocket.h"

int main() {


    std::cout<<"#####################################"<<std::endl;
    std::cout<<"#                                   #"<<std::endl;
    std::cout<<"#                                   #"<<std::endl;
    std::cout<<"#          xhttp start up           #"<<std::endl;
    std::cout<<"#                                   #"<<std::endl;
    std::cout<<"#                                   #"<<std::endl;
    std::cout<<"#                                   #"<<std::endl;
    std::cout<<"#####################################"<<std::endl;
    serviceSocket sSocket(8888);
    sSocket.init();
    return 0;
}
