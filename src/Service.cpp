#include "Interface1Service.hpp"

#include <chrono>
#include <thread>

using namespace std::chrono_literals;

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    Interface1Service i1s;

    i1s.start();

    for (;;)
    {
        std::this_thread::sleep_for(1s);
    }

    return 0;
}
