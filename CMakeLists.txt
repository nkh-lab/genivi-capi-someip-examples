cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# project name e.g. for qt-creator
project(genivi-capi-someip-examples)

set (COMMONAPI_INTERNAL_COMPILATION ON)

include_directories(include)

# Workaround to fix dynamic_cast in libvsomeip3.so (vsomeip_v3::application_impl::init())
# Possible root cause: the same type info in libvsomeip3.so and libvsomeip3-cfg.so
# Fix: swap type info positions in linker by changing libraries loading order
#(lldb) image lookup -r -v -s "typeinfo.*vsomeip_v3::configuration_plugin"
#2 symbols match the regular expression 'typeinfo.*vsomeip_v3::configuration_plugin' in /home/nikolay/Projects/Android/AS/app/build/intermediates/cmake/debug/obj/x86/libvsomeip3.so:
#        Address: libvsomeip3.so[0x00c96678] (libvsomeip3.so..data.rel.ro + 33064)
#        Summary: libvsomeip3.so`typeinfo for vsomeip_v3::configuration_plugin
#         Module: file = "/home/nikolay/Projects/Android/AS/app/build/intermediates/cmake/debug/obj/x86/libvsomeip3.so", arch = "i386"
#         Symbol: id = {0x00082da2}, range = [0xcaa16678-0xcaa16680), name="typeinfo for vsomeip_v3::configuration_plugin", mangled="_ZTIN10vsomeip_v320configuration_pluginE"
# ...
#8 symbols match the regular expression 'typeinfo.*vsomeip_v3::configuration_plugin' in /home/nikolay/Projects/Android/AS/app/build/intermediates/cmake/debug/obj/x86/libvsomeip3-cfg.so:
#        Address: libvsomeip3-cfg.so[0x002188fc] (libvsomeip3-cfg.so..data.rel.ro + 4132)
#        Summary: libvsomeip3-cfg.so`typeinfo for vsomeip_v3::configuration_plugin
#         Module: file = "/home/nikolay/Projects/Android/AS/app/build/intermediates/cmake/debug/obj/x86/libvsomeip3-cfg.so", arch = "i386"
#         Symbol: id = {0x0000b2c6}, range = [0xcacb58fc-0xcacb5904), name="typeinfo for vsomeip_v3::configuration_plugin", mangled="_ZTIN10vsomeip_v320configuration_pluginE"
#...
list(APPEND USED_LIBS vsomeip3-cfg vsomeip3-sd)

# nkh-lab/logger
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../logger/include)
list(APPEND USED_LIBS nkhlablogger)

# CommonAPI
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../capicxx-core-runtime/include)

# SOME/IP
#find_package(CommonAPI-SomeIP 3.1.12 REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../capicxx-someip-runtime/include)

option(COMMONAPI_INTERNAL_COMPILATION "Use internal SomeIP interface deployment or via shared lib" ON) #OFF by default

list(APPEND SERVICE_COMMONAPI_GEN_SRCS
    src-gen/commonapi/v0/commonapi/examples/Interface1.hpp
    src-gen/commonapi/v0/commonapi/examples/Interface1StubDefault.cpp
    src-gen/commonapi/v0/commonapi/examples/Interface1StubDefault.hpp
    src-gen/commonapi/v0/commonapi/examples/Interface1Stub.hpp
    )

list(APPEND CLIENT_COMMONAPI_GEN_SRCS
    src-gen/commonapi/v0/commonapi/examples/Interface1.hpp
    src-gen/commonapi/v0/commonapi/examples/Interface1ProxyBase.hpp
    src-gen/commonapi/v0/commonapi/examples/Interface1Proxy.hpp
    )

list(APPEND COMMON_SOMEIP_GEN_SRCS
    src-gen/someip/v0/commonapi/examples/Interface1SomeIPDeployment.cpp
    src-gen/someip/v0/commonapi/examples/Interface1SomeIPDeployment.hpp
    )

list(APPEND SERVICE_SOMEIP_GEN_SRCS
    src-gen/someip/v0/commonapi/examples/Interface1SomeIPStubAdapter.cpp
    src-gen/someip/v0/commonapi/examples/Interface1SomeIPStubAdapter.hpp
    )

list(APPEND CLIENT_SOMEIP_GEN_SRCS
    src-gen/someip/v0/commonapi/examples/Interface1SomeIPProxy.cpp
    src-gen/someip/v0/commonapi/examples/Interface1SomeIPProxy.hpp
    )

list(APPEND EXTRA_FILES # to see in progect tree
    fidl/Interface1.fidl
    fidl/Interface1.fdepl
    scripts/RunInterface1Service.sh
    scripts/RunInterface1Client.sh
    scripts/RunInterface1Service_InternalCompilation.sh
    scripts/RunInterface1Client_InternalCompilation.sh
    config/commonapi.ini
    config/vsomeip.json
    README.md
    )

list(APPEND SERVICE_SRCS
    src/Interface1Service.cpp
    src/Interface1StubImpl.cpp
    src/Interface1StubImpl.hpp
    ${SERVICE_COMMONAPI_GEN_SRCS}
    ${EXTRA_FILES}
    )

list(APPEND CLIENT_SRCS
    src/Interface1Client.cpp
    ${CLIENT_COMMONAPI_GEN_SRCS}
    )

list(APPEND SOMEIP_SRCS
    ${COMMON_SOMEIP_GEN_SRCS}
    ${SERVICE_SOMEIP_GEN_SRCS}
    ${CLIENT_SOMEIP_GEN_SRCS}
    )

list(APPEND USED_LIBS CommonAPI)

include_directories(
    src-gen/commonapi
    src-gen/someip
)

if(COMMONAPI_INTERNAL_COMPILATION)

    list(APPEND MY_CXX_FLAGS -DCOMMONAPI_INTERNAL_COMPILATION)

    list(APPEND USED_LIBS CommonAPI-SomeIP)

    list(APPEND SERVICE_SRCS
        ${COMMON_SOMEIP_GEN_SRCS}
        ${SERVICE_SOMEIP_GEN_SRCS}
        )

    list(APPEND CLIENT_SRCS
        ${COMMON_SOMEIP_GEN_SRCS}
        ${CLIENT_SOMEIP_GEN_SRCS}
        )
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall ${MY_CXX_FLAGS}")

# Build Service
add_library(Interface1-Service SHARED ${SERVICE_SRCS})
target_link_libraries(Interface1-Service ${USED_LIBS})

# Build Client
add_library(Interface1-Client SHARED ${CLIENT_SRCS})
target_link_libraries(Interface1-Client ${USED_LIBS})

if(NOT COMMONAPI_INTERNAL_COMPILATION)
# Build SOME/IP library
add_library (Interface1-SomeIP SHARED ${SOMEIP_SRCS})
target_link_libraries(Interface1-SomeIP CommonAPI-SomeIP)
endif()
