/*
 * This file was generated by the CommonAPI Generators.
 * Used org.genivi.commonapi.someip 3.2.0.v202012231301.
 * Used org.franca.core 0.13.1.201807231814.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 */
#ifndef V0_COMMONAPI_EXAMPLES_INTERFACE1_SOMEIP_PROXY_HPP_
#define V0_COMMONAPI_EXAMPLES_INTERFACE1_SOMEIP_PROXY_HPP_

#include <v0/commonapi/examples/Interface1ProxyBase.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#define HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE
#endif

#include <CommonAPI/SomeIP/Factory.hpp>
#include <CommonAPI/SomeIP/Proxy.hpp>
#include <CommonAPI/SomeIP/Types.hpp>
#include <CommonAPI/SomeIP/Attribute.hpp>

#if defined (HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE)
#undef COMMONAPI_INTERNAL_COMPILATION
#undef HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE
#endif

#include <string>

# if defined(_MSC_VER)
#  if _MSC_VER >= 1300
/*
 * Diamond inheritance is used for the CommonAPI::Proxy base class.
 * The Microsoft compiler put warning (C4250) using a desired c++ feature: "Delegating to a sister class"
 * A powerful technique that arises from using virtual inheritance is to delegate a method from a class in another class
 * by using a common abstract base class. This is also called cross delegation.
 */
#    pragma warning( disable : 4250 )
#  endif
# endif

namespace v0 {
namespace commonapi {
namespace examples {

class Interface1SomeIPProxy
    : virtual public Interface1ProxyBase,
      virtual public CommonAPI::SomeIP::Proxy {
public:
    Interface1SomeIPProxy(
        const CommonAPI::SomeIP::Address &_address,
        const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection);

    virtual ~Interface1SomeIPProxy();

    virtual AStringAttribute& getAStringAttribute();

    virtual void setUInt32(uint32_t _value, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info);

    virtual std::future<CommonAPI::CallStatus> setUInt32Async(const uint32_t &_value, SetUInt32AsyncCallback _callback, const CommonAPI::CallInfo *_info);

    virtual void getUInt32(CommonAPI::CallStatus &_internalCallStatus, uint32_t &_value, const CommonAPI::CallInfo *_info);

    virtual std::future<CommonAPI::CallStatus> getUInt32Async(GetUInt32AsyncCallback _callback, const CommonAPI::CallInfo *_info);

    virtual void getOwnVersion(uint16_t &_major, uint16_t &_minor) const;

    virtual std::future<void> getCompletionFuture();

private:
    CommonAPI::SomeIP::ObservableAttribute<CommonAPI::SomeIP::Attribute<AStringAttribute, CommonAPI::SomeIP::StringDeployment>> aString_;

    std::promise<void> completed_;
};

} // namespace examples
} // namespace commonapi
} // namespace v0

#endif // V0_COMMONAPI_EXAMPLES_Interface1_SOMEIP_PROXY_HPP_
