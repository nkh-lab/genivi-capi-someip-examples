/*
 * This file was generated by the CommonAPI Generators.
 * Used org.genivi.commonapi.someip 3.2.0.v202012231301.
 * Used org.franca.core 0.13.1.201807231814.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 */
#ifndef V0_COMMONAPI_EXAMPLES_INTERFACE1_SOMEIP_STUB_ADAPTER_HPP_
#define V0_COMMONAPI_EXAMPLES_INTERFACE1_SOMEIP_STUB_ADAPTER_HPP_

#include <v0/commonapi/examples/Interface1Stub.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#define HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE
#endif

#include <CommonAPI/SomeIP/AddressTranslator.hpp>
#include <CommonAPI/SomeIP/StubAdapterHelper.hpp>
#include <CommonAPI/SomeIP/StubAdapter.hpp>
#include <CommonAPI/SomeIP/Factory.hpp>
#include <CommonAPI/SomeIP/Types.hpp>
#include <CommonAPI/SomeIP/Constants.hpp>

#if defined (HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE)
#undef COMMONAPI_INTERNAL_COMPILATION
#undef HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE
#endif

namespace v0 {
namespace commonapi {
namespace examples {

template <typename _Stub = ::v0::commonapi::examples::Interface1Stub, typename... _Stubs>
class Interface1SomeIPStubAdapterInternal
    : public virtual Interface1StubAdapter,
      public CommonAPI::SomeIP::StubAdapterHelper< _Stub, _Stubs...>,
      public std::enable_shared_from_this< Interface1SomeIPStubAdapterInternal<_Stub, _Stubs...>>
{
public:
    typedef CommonAPI::SomeIP::StubAdapterHelper< _Stub, _Stubs...> Interface1SomeIPStubAdapterHelper;

    ~Interface1SomeIPStubAdapterInternal() {
        deactivateManagedInstances();
        Interface1SomeIPStubAdapterHelper::deinit();
    }

    void fireAStringAttributeChanged(const std::string &_value);
    
    void deactivateManagedInstances() {}
    
    CommonAPI::SomeIP::GetAttributeStubDispatcher<
        ::v0::commonapi::examples::Interface1Stub,
        CommonAPI::Version
    > getInterface1InterfaceVersionStubDispatcher;

    CommonAPI::SomeIP::GetAttributeStubDispatcher<
        ::v0::commonapi::examples::Interface1Stub,
        std::string,
        CommonAPI::SomeIP::StringDeployment
    > getAStringAttributeStubDispatcher;
    
    CommonAPI::SomeIP::SetObservableAttributeStubDispatcher<
        ::v0::commonapi::examples::Interface1Stub,
        std::string,
        CommonAPI::SomeIP::StringDeployment
    > setAStringAttributeStubDispatcher;
    
    CommonAPI::SomeIP::MethodWithReplyStubDispatcher<
        ::v0::commonapi::examples::Interface1Stub,
        std::tuple< uint32_t>,
        std::tuple< >,
        std::tuple< CommonAPI::SomeIP::IntegerDeployment<uint32_t>>,
        std::tuple< >
    > setUInt32StubDispatcher;
    
    CommonAPI::SomeIP::MethodWithReplyStubDispatcher<
        ::v0::commonapi::examples::Interface1Stub,
        std::tuple< >,
        std::tuple< uint32_t>,
        std::tuple< >,
        std::tuple< CommonAPI::SomeIP::IntegerDeployment<uint32_t>>
    > getUInt32StubDispatcher;
    
    Interface1SomeIPStubAdapterInternal(
        const CommonAPI::SomeIP::Address &_address,
        const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection,
        const std::shared_ptr<CommonAPI::StubBase> &_stub):
        CommonAPI::SomeIP::StubAdapter(_address, _connection),
        Interface1SomeIPStubAdapterHelper(
            _address,
            _connection,
            std::dynamic_pointer_cast< Interface1Stub>(_stub)),
        getInterface1InterfaceVersionStubDispatcher(&Interface1Stub::lockInterfaceVersionAttribute, &Interface1Stub::getInterfaceVersion, false, true),
        getAStringAttributeStubDispatcher(
            &::v0::commonapi::examples::Interface1Stub::lockAStringAttribute,
            &::v0::commonapi::examples::Interface1Stub::getAStringAttribute,
            false,
            _stub->hasElement(0)),
        setAStringAttributeStubDispatcher(
            &::v0::commonapi::examples::Interface1Stub::lockAStringAttribute,
            &::v0::commonapi::examples::Interface1Stub::getAStringAttribute,
            &Interface1StubRemoteEvent::onRemoteSetAStringAttribute,
            &Interface1StubRemoteEvent::onRemoteAStringAttributeChanged,
            &Interface1StubAdapter::fireAStringAttributeChanged,
            false,
            _stub->hasElement(0))
        ,
        setUInt32StubDispatcher(
            &Interface1Stub::setUInt32,
            false,
            _stub->hasElement(1),
            std::make_tuple(static_cast< CommonAPI::SomeIP::IntegerDeployment<uint32_t>* >(nullptr)),
            std::make_tuple())
        
        ,
        getUInt32StubDispatcher(
            &Interface1Stub::getUInt32,
            false,
            _stub->hasElement(2),
            std::make_tuple(),
            std::make_tuple(static_cast< CommonAPI::SomeIP::IntegerDeployment<uint32_t>* >(nullptr)))
        
    {
        Interface1SomeIPStubAdapterHelper::addStubDispatcher( { CommonAPI::SomeIP::method_id_t(0xbb8) }, &getAStringAttributeStubDispatcher );
        Interface1SomeIPStubAdapterHelper::addStubDispatcher( { CommonAPI::SomeIP::method_id_t(0xbb9) }, &setAStringAttributeStubDispatcher );
        Interface1SomeIPStubAdapterHelper::addStubDispatcher( { CommonAPI::SomeIP::method_id_t(0x7530) }, &setUInt32StubDispatcher );
        Interface1SomeIPStubAdapterHelper::addStubDispatcher( { CommonAPI::SomeIP::method_id_t(0x7531) }, &getUInt32StubDispatcher );
        std::shared_ptr<CommonAPI::SomeIP::ClientId> itsClient = std::make_shared<CommonAPI::SomeIP::ClientId>(0xFFFF, 0xFFFFFFFF, 0xFFFFFFFF);

        // Provided events/fields
        if (_stub->hasElement(0)) {
            std::set<CommonAPI::SomeIP::eventgroup_id_t> itsEventGroups;
            itsEventGroups.insert(CommonAPI::SomeIP::eventgroup_id_t(CommonAPI::SomeIP::eventgroup_id_t(0x80f2)));
            CommonAPI::SomeIP::StubAdapter::registerEvent(CommonAPI::SomeIP::event_id_t(0x80f2), itsEventGroups, CommonAPI::SomeIP::event_type_e::ET_FIELD, CommonAPI::SomeIP::reliability_type_e::RT_UNRELIABLE);
            fireAStringAttributeChanged(std::dynamic_pointer_cast< ::v0::commonapi::examples::Interface1Stub>(_stub)->getAStringAttribute(itsClient));
        }

    }

    // Register/Unregister event handlers for selective broadcasts
    void registerSelectiveEventHandlers();
    void unregisterSelectiveEventHandlers();

};

template <typename _Stub, typename... _Stubs>
void Interface1SomeIPStubAdapterInternal<_Stub, _Stubs...>::fireAStringAttributeChanged(const std::string &_value) {
    CommonAPI::Deployable< std::string, CommonAPI::SomeIP::StringDeployment> deployedValue(_value, static_cast< CommonAPI::SomeIP::StringDeployment* >(nullptr));
    CommonAPI::SomeIP::StubEventHelper<
        CommonAPI::SomeIP::SerializableArguments<
            CommonAPI::Deployable<
                std::string,
                CommonAPI::SomeIP::StringDeployment
            >
            >
    >::sendEvent(
        *this,
        CommonAPI::SomeIP::event_id_t(0x80f2),
        false,
        deployedValue
    );
}


template <typename _Stub, typename... _Stubs>
void Interface1SomeIPStubAdapterInternal<_Stub, _Stubs...>::registerSelectiveEventHandlers() {
}

template <typename _Stub, typename... _Stubs>
void Interface1SomeIPStubAdapterInternal<_Stub, _Stubs...>::unregisterSelectiveEventHandlers() {
}

template <typename _Stub = ::v0::commonapi::examples::Interface1Stub, typename... _Stubs>
class Interface1SomeIPStubAdapter
    : public Interface1SomeIPStubAdapterInternal<_Stub, _Stubs...> {
public:
    Interface1SomeIPStubAdapter(const CommonAPI::SomeIP::Address &_address,
                                            const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection,
                                            const std::shared_ptr<CommonAPI::StubBase> &_stub)
        : CommonAPI::SomeIP::StubAdapter(_address, _connection),
          Interface1SomeIPStubAdapterInternal<_Stub, _Stubs...>(_address, _connection, _stub) {
    }
};

} // namespace examples
} // namespace commonapi
} // namespace v0

#endif // V0_COMMONAPI_EXAMPLES_Interface1_SOMEIP_STUB_ADAPTER_HPP_
