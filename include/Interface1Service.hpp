#include <thread>

class Interface1Service
{
public:
    void start();

private:
    void main();

private:
    std::thread mThread;
};
