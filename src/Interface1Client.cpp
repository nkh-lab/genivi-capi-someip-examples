#include "Interface1Client.hpp"

#include <iostream>

#include <CommonAPI/CommonAPI.hpp>
#include "v0/commonapi/examples/Interface1Proxy.hpp"

#ifdef ANDROID
#define LOG_TAG "Interface1Client"
#endif

#include "nkh-lab/logger.hpp"

#define VSOMEIP_ENV_APPLICATION_NAME            "VSOMEIP_APPLICATION_NAME"
#define VSOMEIP_ENV_CONFIGURATION               "VSOMEIP_CONFIGURATION"
#define VSOMEIP_ENV_BASE_PATH                   "VSOMEIP_BASE_PATH"
#define COMMONAPI_ENV_CONFIG                    "COMMONAPI_CONFIG"

using namespace v0::commonapi::examples;

uint32_t Interface1Client::mClientCounter = 0;

Interface1Client::Interface1Client(const std::string& clientName)
    : mClientName(clientName)
{
    ++mClientCounter;
    mClientID = mClientCounter;

    mClientInfo = getClientInfo();
}

void Interface1Client::main()
{
    LOG_INF << mClientInfo << ": Hello from Interface1Client";

    // check configured environment variables
    LOG_INF << "Check configured environment variables:";
    const char* env = nullptr;
    LOG_INF << "    " << VSOMEIP_ENV_APPLICATION_NAME << ": " << (env = getenv(VSOMEIP_ENV_APPLICATION_NAME), env ? env : "");
    LOG_INF << "    " << VSOMEIP_ENV_CONFIGURATION << ":    " << (env = getenv(VSOMEIP_ENV_CONFIGURATION), env ? env : "");
    LOG_INF << "    " << VSOMEIP_ENV_BASE_PATH << ":        " << (env = getenv(VSOMEIP_ENV_BASE_PATH), env ? env : "");
    LOG_INF << "    " << COMMONAPI_ENV_CONFIG << ":         " << (env = getenv(COMMONAPI_ENV_CONFIG), env ? env : "");

    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();

    CHECK(runtime, "%s: CommonAPI::Runtime::get() returned nullptr", mClientInfo.c_str());

    std::string domain = "local";
    std::string instance = "commonapi.examples.Interface1";

    std::shared_ptr<Interface1Proxy<>> myProxy =
        runtime->buildProxy<Interface1Proxy>(domain, instance);

    CHECK(myProxy, "%s: runtime->buildProxy() returned nullptr", mClientInfo.c_str());

    LOG_INF << mClientInfo << ": Checking availability!";

    while (!myProxy->isAvailable()) std::this_thread::sleep_for(std::chrono::microseconds(10));

    LOG_INF << mClientInfo << ": Available...";

    CommonAPI::CallStatus callStatus;

    uint32_t s = 0;
    uint32_t g = 0;
    std::string gS;

    myProxy->getAStringAttribute().getChangedEvent().subscribe(
        [this](std::string s) { LOG_INF << mClientInfo << ": aString was changed to: " << s; },
        [this](CommonAPI::CallStatus aStringCallStatus) {
            LOG_INF << mClientInfo << ": aString CallStatus: " << static_cast<int>(aStringCallStatus);
        });

    while (true)
    {
        myProxy->getAStringAttribute().setValue(std::to_string(s), callStatus, gS);

        if (CHECK(
                callStatus == CommonAPI::CallStatus::SUCCESS,
                "%s: getAStringAttribute().setValue() call failed!",
                mClientInfo.c_str()))
        {
            LOG_INF << mClientInfo << ": getAStringAttribute().setValue() was set to: " << gS;
        }

        LOG_INF << mClientInfo << ": setUInt32(): " << s;

        myProxy->setUInt32(s, callStatus);
        CHECK(
            callStatus == CommonAPI::CallStatus::SUCCESS,
            "%s: setUInt32() call failed!",
            mClientInfo.c_str());

        std::this_thread::sleep_for(std::chrono::seconds(3));

        myProxy->getUInt32(callStatus, g);
        CHECK(
            callStatus == CommonAPI::CallStatus::SUCCESS,
            "%s: getUInt32() call failed!",
            mClientInfo.c_str());

        LOG_INF << mClientInfo << ": getUInt32(): " << g;

        std::this_thread::sleep_for(std::chrono::seconds(3));

        ++s;
    }
}

void Interface1Client::start()
{
    mThread = std::thread(&Interface1Client::main, this);
}

std::string Interface1Client::getClientInfo()
{
    if (mClientName != "")
    {
        return mClientName;
    }
    else
    {
        return "Client" + std::to_string(mClientID);
    }
}
