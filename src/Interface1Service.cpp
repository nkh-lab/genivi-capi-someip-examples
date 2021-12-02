#include "Interface1Service.hpp"

#include <iostream>

#include <CommonAPI/CommonAPI.hpp>
#include "Interface1StubImpl.hpp"

#ifdef ANDROID
#define LOG_TAG "Interface1Service"
#endif

#include "nkh-lab/logger.hpp"

#define VSOMEIP_ENV_APPLICATION_NAME            "VSOMEIP_APPLICATION_NAME"
#define VSOMEIP_ENV_CONFIGURATION               "VSOMEIP_CONFIGURATION"
#define VSOMEIP_ENV_BASE_PATH                   "VSOMEIP_BASE_PATH"
#define COMMONAPI_ENV_CONFIG                    "COMMONAPI_CONFIG"

void Interface1Service::main()
{
    LOG_INF << "Hello from Interface1Service";

    // check configured environment variables
    LOG_INF << "Check configured environment variables:";
    const char* env = nullptr;
    LOG_INF << "    " << VSOMEIP_ENV_APPLICATION_NAME << ": " << (env = getenv(VSOMEIP_ENV_APPLICATION_NAME), env ? env : "");
    LOG_INF << "    " << VSOMEIP_ENV_CONFIGURATION << ":    " << (env = getenv(VSOMEIP_ENV_CONFIGURATION), env ? env : "");
    LOG_INF << "    " << VSOMEIP_ENV_BASE_PATH << ":        " << (env = getenv(VSOMEIP_ENV_BASE_PATH), env ? env : "");
    LOG_INF << "    " << COMMONAPI_ENV_CONFIG << ":         " << (env = getenv(COMMONAPI_ENV_CONFIG), env ? env : "");

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
