#include <iostream>
#include <fstream>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    const char* device = "/dev/input/event4";
    int fd = open(device, O_RDONLY);
    if (fd == -1) {
        std::cerr << "Cannot open " << device << " (you might need to run this as root)" << std::endl;
        return 1;
    }

    struct input_event ev;

    while (true) {
        read(fd, &ev, sizeof(struct input_event));
        if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2) {
            std::cout << "Key " << ev.code << (ev.value == 1 ? " Pressed" : " Released") << std::endl;
        }
    }
    close(fd);
    return 0;
}
