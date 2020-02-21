#include <iostream>

int main(int argc, char *argv[])
{
    static_cast<void>(argc);
    static_cast<void>(argv);

    std::cout << "Hello from Interface1Client" << std::endl;

    return 0;
}
