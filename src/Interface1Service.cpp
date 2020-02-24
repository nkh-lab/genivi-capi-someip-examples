#include <iostream>

#include <CommonAPI/CommonAPI.hpp>
#include "Interface1StubImpl.hpp"

int main(int argc, char *argv[])
{
    static_cast<void>(argc);
    static_cast<void>(argv);

    std::cout << "Hello from Interface1Service" << std::endl;

    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();

    std::string domain = "local";
    std::string instance = "commonapi.examples.Interface1";

    std::shared_ptr<Interface1StubImpl> myService = std::make_shared<Interface1StubImpl>();
    bool successfullyRegistered = runtime->registerService(domain, instance, myService);

    while (!successfullyRegistered) {
        std::cout << "Register Service failed, trying again in 100 milliseconds..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        successfullyRegistered = runtime->registerService(domain, instance, myService);
    }

    std::cout << "Successfully Registered Service!" << std::endl;

    while (true) {
        std::cout << "Waiting for calls... (Abort with CTRL+C)" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(60));
    }

    return 0;
}
