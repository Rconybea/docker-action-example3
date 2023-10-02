#include <iostream>

int
main(int argc, char ** argv) {
    std::string subject = "World";

    if (argc >= 2)
        subject = argv[1];

    std::cout << "Hello, " << subject << "!" << std::endl;

    return 0;
}
