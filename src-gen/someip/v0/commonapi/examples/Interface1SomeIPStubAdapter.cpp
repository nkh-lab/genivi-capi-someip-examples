/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.someip 3.1.12.v202002201657.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#include <v0/commonapi/examples/Interface1SomeIPStubAdapter.hpp>
#include <v0/commonapi/examples/Interface1.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/SomeIP/AddressTranslator.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v0 {
namespace commonapi {
namespace examples {

std::shared_ptr<CommonAPI::SomeIP::StubAdapter> createInterface1SomeIPStubAdapter(
                   const CommonAPI::SomeIP::Address &_address,
                   const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection,
                   const std::shared_ptr<CommonAPI::StubBase> &_stub) {
    return std::make_shared< Interface1SomeIPStubAdapter<::v0::commonapi::examples::Interface1Stub>>(_address, _connection, _stub);
}

void initializeInterface1SomeIPStubAdapter() {
    CommonAPI::SomeIP::AddressTranslator::get()->insert(
        "local:commonapi.examples.Interface1:v0_1:commonapi.examples.Interface1",
         0x1234, 0x5678, 0, 1);
    CommonAPI::SomeIP::Factory::get()->registerStubAdapterCreateMethod(
        Interface1::getInterface(),
        &createInterface1SomeIPStubAdapter);
}

INITIALIZER(registerInterface1SomeIPStubAdapter) {
    CommonAPI::SomeIP::Factory::get()->registerInterface(initializeInterface1SomeIPStubAdapter);
}
} // namespace examples
} // namespace commonapi
} // namespace v0
