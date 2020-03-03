#include <iostream>

#include <CommonAPI/CommonAPI.hpp>
#include "Interface1StubImpl.hpp"

#ifdef ANDROID
#define LOG_TAG "Interface1Service.cpp"
#include "log/log.h"
#endif

int main(int argc, char *argv[])
{
    static_cast<void>(argc);
    static_cast<void>(argv);

#ifdef ANDROID
    ALOGI("Hello from Interface1Service");
#else
    std::cout << "Hello from Interface1Service" << std::endl;
#endif

    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();

    std::string domain = "local";
    std::string instance = "commonapi.examples.Interface1";

    std::shared_ptr<Interface1StubImpl> myService = std::make_shared<Interface1StubImpl>();
    bool successfullyRegistered = runtime->registerService(domain, instance, myService);

    while (!successfullyRegistered) {

#ifdef ANDROID
        ALOGI("Register Service failed, trying again in 100 milliseconds...");
#else
        std::cout << "Register Service failed, trying again in 100 milliseconds..." << std::endl;
#endif
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        successfullyRegistered = runtime->registerService(domain, instance, myService);
    }

#ifdef ANDROID
    ALOGI("Successfully Registered Service!");
#else
    std::cout << "Successfully Registered Service!" << std::endl;
#endif

    while (true) {

#ifdef ANDROID
        ALOGI("Waiting for calls... (Abort with CTRL+C)");
#else
        std::cout << "Waiting for calls... (Abort with CTRL+C)" << std::endl;
#endif
        std::this_thread::sleep_for(std::chrono::seconds(60));
    }

    return 0;
}
