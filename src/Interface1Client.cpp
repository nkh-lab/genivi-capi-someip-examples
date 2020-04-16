#include <iostream>

#include <CommonAPI/CommonAPI.hpp>
#include "v0/commonapi/examples/Interface1Proxy.hpp"

#ifdef ANDROID
#define LOG_TAG "Interface1Client"
#endif

#include "nkh-lab/logger.hpp"

using namespace v0::commonapi::examples;

int main(int argc, char *argv[])
{
    static_cast<void>(argc);
    static_cast<void>(argv);

    LOG_INF << "Hello from Interface1Client";

    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();

    if(!CHECK(runtime, "CommonAPI::Runtime::get() returned nullptr")) return -1;

    std::string domain = "local";
    std::string instance = "commonapi.examples.Interface1";

    std::shared_ptr<Interface1Proxy<>> myProxy = runtime->buildProxy<Interface1Proxy>(domain, instance);

    if(!CHECK(myProxy, "runtime->buildProxy() returned nullptr")) return -1;

    LOG_INF << "Checking availability!";

    while (!myProxy->isAvailable())
        std::this_thread::sleep_for(std::chrono::microseconds(10));

    LOG_INF << "Available...";

    CommonAPI::CallStatus callStatus;

    uint32_t s=0;
    uint32_t g=0;
    std::string gS;

    myProxy->getAStringAttribute().getChangedEvent().subscribe(
    [](std::string s)
    {
        LOG_INF << "aString was changed to: " << s;
    }
    ,
    [](CommonAPI::CallStatus aStringCallStatus)
    {
        LOG_INF << "aString CallStatus: " << static_cast<int>(aStringCallStatus);
    }
    );

    while (true)
    {
        myProxy->getAStringAttribute().setValue(std::to_string(s), callStatus, gS);

        if (CHECK(callStatus == CommonAPI::CallStatus::SUCCESS, "getAStringAttribute().setValue() call failed!"))
        {
            LOG_INF << "getAStringAttribute().setValue() was set to: " << gS;
        }
        else return -1;

        LOG_INF << "setUInt32(): " << s;

        myProxy->setUInt32(s, callStatus);
        if (!CHECK(callStatus == CommonAPI::CallStatus::SUCCESS, "setUInt32() call failed!")) return -1;

        std::this_thread::sleep_for(std::chrono::seconds(3));

        myProxy->getUInt32(callStatus, g);
        if (!CHECK(callStatus == CommonAPI::CallStatus::SUCCESS, "getUInt32() call failed!")) return -1;

        LOG_INF << "getUInt32(): " << g;

        std::this_thread::sleep_for(std::chrono::seconds(3));

        ++s;
    }

    return 0;
}
