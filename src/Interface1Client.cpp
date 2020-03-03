#include <iostream>

#include <CommonAPI/CommonAPI.hpp>
#include "v0/commonapi/examples/Interface1Proxy.hpp"

#ifdef ANDROID
#define LOG_TAG "Interface1Service.cpp"
#include "log/log.h"
#endif

using namespace v0::commonapi::examples;

int main(int argc, char *argv[])
{
    static_cast<void>(argc);
    static_cast<void>(argv);

#ifdef ANDROID
    ALOGI("Hello from Interface1Client");
#else
    std::cout << "Hello from Interface1Client" << std::endl;
#endif

    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();

    if(!runtime)
    {
#ifdef ANDROID
        ALOGE("CommonAPI::Runtime::get() returned nullptr");
#else
        std::cerr << "CommonAPI::Runtime::get() returned nullptr" << std::endl;
#endif
        return -1;
    }

    std::string domain = "local";
    std::string instance = "commonapi.examples.Interface1";

    std::shared_ptr<Interface1Proxy<>> myProxy = runtime->buildProxy<Interface1Proxy>(domain, instance);

    if(!myProxy)
    {
#ifdef ANDROID
        ALOGE("runtime->buildProxy() returned nullptr");
#else
        std::cerr << "runtime->buildProxy() returned nullptr" << std::endl;
#endif
        return -1;
    }

#ifdef ANDROID
    ALOGI("Checking availability!");
#else
    std::cout << "Checking availability!" << std::endl;
#endif

    while (!myProxy->isAvailable())
        std::this_thread::sleep_for(std::chrono::microseconds(10));

#ifdef ANDROID
    ALOGI("Available...");
#else
    std::cout << "Available..." << std::endl;
#endif

    CommonAPI::CallStatus callStatus;

    uint32_t s=0;
    uint32_t g=0;
    std::string gS;

    myProxy->getAStringAttribute().getChangedEvent().subscribe([](std::string s)
    {
#ifdef ANDROID
        ALOGI("aString was changed to: %s", s.c_str());
#else
        std::cout << "aString was changed to: " << s << std::endl;
#endif
    });

    while (true) {

        myProxy->getAStringAttribute().setValue(std::to_string(s), callStatus, gS);

        if (callStatus != CommonAPI::CallStatus::SUCCESS) {
#ifdef ANDROID
            ALOGE("getAStringAttribute().setValue() call failed!");
#else
            std::cerr << "getAStringAttribute().setValue() call failed!" << std::endl;
#endif
            return -1;
        }
        else {
#ifdef ANDROID
            ALOGI("getAStringAttribute().setValue() was set to: %s", gS.c_str());
#else
            std::cout << "getAStringAttribute().setValue() was set to: " << gS << std::endl;
#endif
        }

#ifdef ANDROID
        ALOGI("setUInt32(): %d", s);
#else
        std::cout << "setUInt32(): " << s << std::endl;
#endif
        myProxy->setUInt32(s, callStatus);
        if (callStatus != CommonAPI::CallStatus::SUCCESS) {
#ifdef ANDROID
            ALOGE("setUInt32() call failed!");
#else
            std::cerr << "setUInt32() call failed!" << std::endl;
#endif
            return -1;
        }

        std::this_thread::sleep_for(std::chrono::seconds(3));

        myProxy->getUInt32(callStatus, g);
        if (callStatus != CommonAPI::CallStatus::SUCCESS) {
#ifdef ANDROID
            ALOGE("getUInt32() call failed!");
#else
            std::cerr << "getUInt32() call failed!" << std::endl;
#endif
            return -1;
        }
#ifdef ANDROID
        ALOGI("getUInt32(): %d", g);
#else
        std::cout << "getUInt32(): " << g << std::endl;
#endif

        std::this_thread::sleep_for(std::chrono::seconds(3));

        ++s;
    }

    return 0;
}
