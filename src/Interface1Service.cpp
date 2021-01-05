#include "Interface1Service.hpp"

#include <iostream>

#include <CommonAPI/CommonAPI.hpp>
#include "Interface1StubImpl.hpp"

#ifdef ANDROID
#define LOG_TAG "Interface1Service"
#endif

#include "nkh-lab/logger.hpp"

void Interface1Service::main()
{
    LOG_INF << "Hello from Interface1Service";

    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();

    std::string domain = "local";
    std::string instance = "commonapi.examples.Interface1";

    std::shared_ptr<Interface1StubImpl> myService = std::make_shared<Interface1StubImpl>();
    bool successfullyRegistered = runtime->registerService(domain, instance, myService);

    while (!successfullyRegistered)
    {
        LOG_INF << "Register Service failed, trying again in 100 milliseconds...";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        successfullyRegistered = runtime->registerService(domain, instance, myService);
    }

    LOG_INF << "Successfully Registered Service!";

    while (true)
    {
        LOG_INF << "Waiting for calls... (Abort with CTRL+C)";
        std::this_thread::sleep_for(std::chrono::seconds(60));
    }
}

void Interface1Service::start()
{
    mThread = std::thread(&Interface1Service::main, this);
}
