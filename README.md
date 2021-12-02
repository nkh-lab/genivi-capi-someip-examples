# genivi-capi-someip-examples

Examples of GENIVI CommonAPI usage via SOMEIP. 
They cover Linux (tested on Ubuntu) and Android AOSP and NDK cases.

For Android NDK please refer next Android Studio project: https://github.com/nkh-lab/ndk-capi-hello-world

## Dependencies
**Used codegeneartion tool projects:**
1. https://github.com/GENIVI/capicxx-core-tools 3.2.0.1
2. https://github.com/GENIVI/capicxx-someip-tools 3.2.0.1

**Runtime libraries:**
1. https://github.com/GENIVI/vsomeip 3.1.20
2. https://github.com/GENIVI/capicxx-core-runtime 3.2.0
3. https://github.com/GENIVI/capicxx-someip-runtime.git 3.2.0

## Codegeneration
Described below codegeneration tools are not the part of the given repository.
It means that they are compiled and placed manualy with whole theirs output stuff to:
```
./tools/commonapi-generator/x86_64
./tools/commonapi-someip-generator/x86_64
```
acordingly.

### CommonAPI, fidl -> src-gen/commonapi -> Service and Client executables
Project: https://github.com/GENIVI/capicxx-core-tools
How to build generator:
```
cd ./capicxx-core-tools/org.genivi.commonapi.releng
mvn -Dtarget.id=org.genivi.commonapi.core.target clean verify
```
Copy generator output stuff:
```
cd org.genivi.commonapi.core.cli.product/target/products
unzip commonapi_core_generator.zip -d ~/My/Projects/genivi-capi-someip-examples/tools/commonapi-generator/x86_64
```
Codegeneration:
```
cd ./tools/commonapi-generator/x86_64
./commonapi-core-generator-linux-x86_64 -sk -d ../../../src-gen/commonapi ../../../fidl/Interface1.fidl
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
How to build generator:
```
cd ./capicxx-someip-tools/org.genivi.commonapi.someip.releng
mvn clean verify -DCOREPATH=../../capicxx-core-tools -Dtarget.id=org.genivi.commonapi.someip.target
```
Copy generator output stuff:
```
cd org.genivi.commonapi.someip.cli.product/target/products
unzip commonapi_someip_generator.zip -d ~/My/Projects/genivi-capi-someip-examples/tools/commonapi-someip-generator/x86_64
```
Codegeneration:
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
### vSOMEIP runtime library
Project: https://github.com/GENIVI/vsomeip
How to build and install:
```
cd build
cmake -D CMAKE_INSTALL_PREFIX=/usr/local ..
make
sudo make install
```

### CommonAPI runtime library
Project: https://github.com/GENIVI/capicxx-core-runtime
How to build and install:
```
cd build
cmake -D CMAKE_INSTALL_PREFIX=/usr/local ..
make
sudo make install
```
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

How to build and install:
```
cd build
cmake -D USE_INSTALLED_COMMONAPI=ON -D CMAKE_INSTALL_PREFIX=/usr/local ..
make
sudo make install
```
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
or for switch off COMMONAPI_INTERNAL_COMPILATION, it is ON by default
```
cd ./build
cmake -DCOMMONAPI_INTERNAL_COMPILATION=OFF ..
make
```

### On AOSP
Prerequisite:
```
ln -s ./aosp/runtime_lib.bp Android.bp
```
or for defined COMMONAPI_INTERNAL_COMPILATION
```
ln -s ./aosp/internal_cmp.bp Android.bp
```

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
Example for runtime SOMEIP interface library, COMMONAPI_INTERNAL_COMPILATION not defined
Service:
```sh
VSOMEIP_APPLICATION_NAME=Interface1-Service \
VSOMEIP_CONFIGURATION=/vendor/etc/genivi-capi-someip-examples/vsomeip.json \
COMMONAPI_CONFIG=/vendor/etc/genivi-capi-someip-examples/commonapi.ini \
Interface1-Service
```
Client:
```sh
VSOMEIP_APPLICATION_NAME=Interface1-Client \
VSOMEIP_CONFIGURATION=/vendor/etc/genivi-capi-someip-examples/vsomeip.json \
COMMONAPI_CONFIG=/vendor/etc/genivi-capi-someip-examples/commonapi.ini \
Interface1-Client
```
or for defined COMMONAPI_INTERNAL_COMPILATION
```sh
VSOMEIP_APPLICATION_NAME=Interface1-Service \
VSOMEIP_CONFIGURATION=/vendor/etc/genivi-capi-someip-examples/vsomeip.json \
Interface1-Service
```
Client:
```sh
VSOMEIP_APPLICATION_NAME=Interface1-Client \
VSOMEIP_CONFIGURATION=/vendor/etc/genivi-capi-someip-examples/vsomeip.json \
Interface1-Client
```
#### Via init.rc
Please see [aosp](aosp) stuff.

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
