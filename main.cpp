
#include <iostream>
//#include "src/threadPool.h"
#include "src/serviceSocket.h"

int main() {



    serviceSocket sSocket(8888);
    sSocket.init();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
