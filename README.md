# Examples of CommonAPI usage via SOMEIP

## Codegeneration
Described below codegeneration tools are not the part of the given repository.
They are compiled and placed with whole theirs output stuff to:
./tools/commonapi-generator/x86_64
./tools/commonapi-someip-generator/x86_64
acordingly.

### CommonAPI, fidl -> src-gen/commonapi -> Service and Client executables
Project: https://github.com/GENIVI/capicxx-core-tools
```
cd ./tools/commonapi-generator/x86_64
./commonapi-generator-linux-x86_64 -sk -d ../../../src-gen/commonapi ../../../fidl/Interface1.fidl
```
```
cd ./src-gen/commonapi/v0/commonapi/examples
$ ls
Interface1.hpp
Interface1ProxyBase.hpp
Interface1Proxy.hpp
Interface1StubDefault.cpp (-sk)
Interface1StubDefault.hpp (-sk)
Interface1Stub.hppp
```

### SOMEIP, fdepl -> src-gen/someip -> SOME/IP library
Project: https://github.com/GENIVI/capicxx-someip-tools
```
cd ./tools/commonapi-someip-generator/x86_64
./commonapi-someip-generator-linux-x86_64 -d ../../../src-gen/someip ../../../fidl/Interface1.fdepl
```
```
cd ./src-gen/someip/v0/commonapi/examples
$ ls
Interface1SomeIPDeployment.cpp
Interface1SomeIPDeployment.hpp
Interface1SomeIPProxy.cpp
Interface1SomeIPProxy.hpp
Interface1SomeIPStubAdapter.cpp
Interface1SomeIPStubAdapter.hpp
```

## Runtime dependencies
### CommonAPI runtime library
Project: https://github.com/GENIVI/capicxx-core-runtime
Useful to enforce logging:
CMake:
```
cmake -DMAX_LOG_LEVEL=VERBOSE -DUSE_CONSOLE=ON ..
```
AOSP, Android.bp cflags:
"-DCOMMONAPI_LOGLEVEL=COMMONAPI_LOGLEVEL_VERBOSE",
"-DUSE_CONSOLE",

### CommonAPI-SOMEIP and VSOMEIP runtime libraries
Project: https://github.com/GENIVI/capicxx-someip-runtime.git
which depends on VSOMEIP
Project: https://github.com/GENIVI/vsomeip.git

To enforce logging use the same configuration like above for CommonAPI.

## Configuration files -> ./config
### CommonAPI -> commonapi.ini
Main point is describe the binding of the interfaces with SOME/IP libraries
which are loaded dinamicaly during runtime.

But if CMake -DCOMMONAPI_INTERNAL_COMPILATION=ON (-> #define COMMONAPI_INTERNAL_COMPILATION)
is defined all generated deplyoment SOMEIP stuff could be built in into Service and Client parts
and therefore commonapi.ini and runtime SOME/IP library are not needed.

### VSOMEIP -> vsomeip.json
- Binds parameters from *.fdepl with VSOMEIP configuration.
- Sets routing. Would it be on Service side or by additional "vsomeipd" executable.

## Scripts -> ./scripts
Set predefined envairoment variables with values to coresponding configuration files
and describe place where SOME/IP libraries are placed which would be loaded in runtime.

## Build
### On Ubuntu
By CMake:
```
cd ./build
cmake ..
make
```
or for defined COMMONAPI_INTERNAL_COMPILATION
```
cd ./build
cmake -DCOMMONAPI_INTERNAL_COMPILATION=ON ..
make
```

### On AOSP
Via mma or add to /device/linaro/hikey/hikey960/device-hikey960.mk
```sh
$(call inherit-product-if-exists, vendor/genivi-capi-someip-examples/aosp/config.mk)
```

## Run
### On Ubuntu
```
cd ./scripts
./RunInterface1Service.sh
./RunInterface1Client.sh
```
or for defined COMMONAPI_INTERNAL_COMPILATION
```
./RunInterface1Service_InternalCompilation.sh
./RunInterface1Client_InternalCompilation.sh
```

### On AOSP
#### Manualy under root:
Service:
```sh
VSOMEIP_APPLICATION_NAME=Interface1-Service \
VSOMEIP_CONFIGURATION=/vendor/etc/capi-someip/vsomeip.json \
COMMONAPI_CONFIG=/vendor/etc/capi-someip/commonapi.ini \
Interface1-Service
```
Client:
```sh
VSOMEIP_APPLICATION_NAME=Interface1-Client \
VSOMEIP_CONFIGURATION=/vendor/etc/capi-someip/vsomeip.json \
COMMONAPI_CONFIG=/vendor/etc/capi-someip/commonapi.ini \
Interface1-Client
```
#### Via init.rc
Please see ./aosp stuff.

**Atention!**: Base path should be changed in /external/vsomeip/implementation/configuration/include/internal_android.hpp from "/storage/" to:
```cpp
#define VSOMEIP_BASE_PATH                       "/data/vendor/vsomeip/"
```
In https://github.com/nkh-lab/vsomeip.git already changed.

## How sockets are used
```sh
hikey960:/ $ ss -x

Netid  State      Recv-Q Send-Q                  Local Address:Port     Peer Address:Port
u_str  ESTAB      0      0     /data/vendor/vsomeip/vsomeip-0 19685     * 0
u_str  ESTAB      0      0                                  * 19689     * 0
u_str  ESTAB      0      0  /data/vendor/vsomeip/vsomeip-5555 26232     * 0
u_str  ESTAB      0      0                                  * 26236     * 0
u_str  ESTAB      0      0  /data/vendor/vsomeip/vsomeip-4444 26237     * 0
```
