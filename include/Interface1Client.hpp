#include <string>
#include <thread>

class Interface1Client
{
public:
    Interface1Client(const std::string& clientName = "");

    void start();

private:
    void main();

    std::string getClientInfo();

private:
    std::thread mThread;

    std::string mClientName;
    std::string mClientInfo;
    uint32_t mClientID;
    static uint32_t mClientCounter;
};