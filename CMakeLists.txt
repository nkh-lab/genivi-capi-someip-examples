cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# project name e.g. for qt-creator
project(genivi-capi-someip-examples)

# nkh-lab/logger
add_subdirectory(external/logger)
list(APPEND USED_LIBS nkhlablogger)

# vsomeip3
find_package(vsomeip3 3.1.20 REQUIRED)

# CommonAPI
find_package(CommonAPI 3.2.0 REQUIRED)
include_directories(${COMMONAPI_INCLUDE_DIRS})

# SOME/IP
find_package(CommonAPI-SomeIP 3.2.0 REQUIRED)

option(COMMONAPI_INTERNAL_COMPILATION "Use internal SomeIP interface deployment or via shared lib" ON) #OFF by default

list(APPEND SERVICE_COMMONAPI_GEN_SRCS
    src-gen/commonapi/v0/commonapi/examples/Interface1.hpp
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
add_executable(Interface1-Service ${SERVICE_SRCS})
target_link_libraries(Interface1-Service ${USED_LIBS})

# Build Client
add_executable(Interface1-Client ${CLIENT_SRCS})
target_link_libraries(Interface1-Client ${USED_LIBS})

if(NOT COMMONAPI_INTERNAL_COMPILATION)
# Build SOME/IP library
add_library (Interface1-SomeIP SHARED ${SOMEIP_SRCS})
target_link_libraries(Interface1-SomeIP CommonAPI-SomeIP)
endif()
