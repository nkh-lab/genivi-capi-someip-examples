#include <iostream>

#include <CommonAPI/CommonAPI.hpp>
#include "v0/commonapi/examples/Interface1Proxy.hpp"

using namespace v0::commonapi::examples;

int main(int argc, char *argv[])
{
    static_cast<void>(argc);
    static_cast<void>(argv);

    std::cout << "Hello from Interface1Client" << std::endl;

    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();

    std::string domain = "local";
    std::string instance = "commonapi.examples.Interface1";

    std::shared_ptr<Interface1Proxy<>> myProxy = runtime->buildProxy<Interface1Proxy>(domain,
            instance);

    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    std::cout << "Available..." << std::endl;

    CommonAPI::CallStatus callStatus;

    uint32_t s=0;
    uint32_t g=0;
    std::string gS;

    myProxy->getAStringAttribute().getChangedEvent().subscribe([](std::string s)
    {
        std::cout << "aString was changed to: " << s << std::endl;
    });

    while (true) {

        myProxy->getAStringAttribute().setValue(std::to_string(s), callStatus, gS);

        if (callStatus != CommonAPI::CallStatus::SUCCESS) {
            std::cerr << "getAStringAttribute().setValue() call failed!\n";
            return -1;
        }
        else {
            std::cerr << "getAStringAttribute().setValue() was set to:" << gS << std::endl;
        }

        std::cout << "setUInt32: " << s << std::endl;
        myProxy->setUInt32(s, callStatus);
        if (callStatus != CommonAPI::CallStatus::SUCCESS) {
            std::cerr << "setUInt32() call failed!\n";
            return -1;
        }

        std::this_thread::sleep_for(std::chrono::seconds(3));


        myProxy->getUInt32(callStatus, g);
        if (callStatus != CommonAPI::CallStatus::SUCCESS) {
            std::cerr << "getUInt32() call failed!\n";
            return -1;
        }
        std::cout << "getUInt32(): " << g << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(3));

        ++s;
    }

    return 0;
}
