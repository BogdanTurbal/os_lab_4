#include <iostream>
#include <string>
#include <sstream>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h> 
#include <cstring> 

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <pid> <address>" << std::endl;
        return 1;
    }

    std::string pid = argv[1];
    unsigned long address;
    std::istringstream iss(argv[2]);
    iss >> std::hex >> address; 

    std::string memPath = "/proc/" + pid + "/mem";
    int memFd = open(memPath.c_str(), O_RDONLY);
    if (memFd == -1) {
        std::cerr << "Failed to open " << memPath << " - " << strerror(errno) << std::endl;
        return 2;
    }

    char value[256]; 
    ssize_t bytesRead = pread(memFd, value, sizeof(value) - 1, address);
    if (bytesRead == -1) {
        std::cerr << "Failed to read memory at address " << std::hex << address << " - " << strerror(errno) << std::endl;
        close(memFd);
        return 3;
    }

    value[bytesRead] = '\0';

    std::cout << "Value at address " << std::hex << address << ": " << value << std::endl;

    close(memFd);

    return 0;
}
