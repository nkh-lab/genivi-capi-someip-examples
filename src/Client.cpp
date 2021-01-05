#include "Interface1Client.hpp"

#include <chrono>
#include <thread>

using namespace std::chrono_literals;

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    Interface1Client i1c;

    i1c.start();

    for (;;)
    {
        std::this_thread::sleep_for(1s);
    }

    return 0;
}
