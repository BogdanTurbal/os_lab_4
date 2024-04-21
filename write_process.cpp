#include <iostream>
#include <unistd.h> 
#include <limits> 

int main() {
    char input[256]; 

    std::cout << "Process ID: " << getpid() << std::endl;
    std::cout << "Address of input variable: " << static_cast<void*>(input) << std::endl;
    std::cout << "Enter a value: ";
    std::cin.getline(input, sizeof(input));
    
    std::cout << "You entered: " << input << std::endl;
    
   
    std::cout << "Press enter to exit...";
    std::cin.get();
    return 0;
}
