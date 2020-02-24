cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# FLAGS:
# -std=c++11    - c++11 support
# -std=c++14
# -Wall         - all warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# project name e.g. for qt-creator
project(genivi-capi-someip-examples)

# CommonAPI
find_package (CommonAPI 3.1.12 REQUIRED)
include_directories(${COMMONAPI_INCLUDE_DIRS})

# SOME/IP
find_package (CommonAPI-SomeIP 3.1.12 REQUIRED)

include_directories(
    src-gen/commonapi
    src-gen/someip
)

# Build service
add_executable(Interface1-Service
    src/Interface1Service.cpp
    src/Interface1StubImpl.cpp
    src/Interface1StubImpl.hpp
    src-gen/commonapi/v0/commonapi/examples/Interface1StubDefault.cpp
    src-gen/commonapi/v0/commonapi/examples/Interface1StubDefault.hpp
    src-gen/commonapi/v0/commonapi/examples/Interface1Stub.hpp
    fidl/Interface1.fidl
    fidl/Interface1.fdepl
    scripts/RunInterface1Service.sh
    README.md)
target_link_libraries(Interface1-Service CommonAPI)

# Build Client
add_executable(Interface1-Client
    src/Interface1Client.cpp
    scripts/RunInterface1Client.sh)
target_link_libraries(Interface1-Client CommonAPI)

# Build SOME/IP library
add_library (Interface1-SomeIP SHARED
    src-gen/someip/v0/commonapi/examples/Interface1SomeIPDeployment.cpp
    src-gen/someip/v0/commonapi/examples/Interface1SomeIPDeployment.hpp
    src-gen/someip/v0/commonapi/examples/Interface1SomeIPProxy.cpp
    src-gen/someip/v0/commonapi/examples/Interface1SomeIPProxy.hpp
    src-gen/someip/v0/commonapi/examples/Interface1SomeIPStubAdapter.cpp
    src-gen/someip/v0/commonapi/examples/Interface1SomeIPStubAdapter.hpp
    config/commonapi.ini
    config/vsomeip.json
    )
target_link_libraries(Interface1-SomeIP CommonAPI-SomeIP)
