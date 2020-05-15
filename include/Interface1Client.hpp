#include <thread>

class Interface1Client {
public:
    void start();

private:
    void main();

private:
    std::thread mThread;
};