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

### VSOMEIP -> vsomeip.json
- Binds parameters from *.fdepl with VSOMEIP configuration.
- Sets routing. Would it be on Service side or by additional "vsomeipd" executable.

## Scripts -> ./scripts
Set predefined envairoment variables with values to coresponding configuration files
and describe place where SOME/IP libraries are placed which would be loaded in runtime.

## Run
```
cd ./scripts
./RunInterface1Service.sh
./RunInterface1Client.sh
```

### On AOSP
#### Service
VSOMEIP_APPLICATION_NAME=Interface1-Service \
VSOMEIP_CONFIGURATION=/etc/capi-someip/vsomeip.json \
COMMONAPI_CONFIG=/etc/capi-someip/commonapi.ini \
Interface1-Service

#### Client
VSOMEIP_APPLICATION_NAME=Interface1-Client \
VSOMEIP_CONFIGURATION=/etc/capi-someip/vsomeip.json \
COMMONAPI_CONFIG=/etc/capi-someip/commonapi.ini \
Interface1-Client
