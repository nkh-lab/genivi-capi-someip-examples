# Examples of CommonAPI usage via SOMEIP

## Codegeneration
### CommonAPI, fidl -> srcs
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

### SOMEIP, fdepl ->
Project: https://github.com/GENIVI/capicxx-someip-tools
```
cd ./tools/commonapi-someip-generator/x86_64
./commonapi-someip-generator-linux-x86_64 -d ../../../src-gen/someip ../../../fidl/Interface1.fdepl
```

## Runtime dependencies
### CommonAPI runtime library
Project: https://github.com/GENIVI/capicxx-core-runtime
Useful to enforce logging:
```
cmake -DMAX_LOG_LEVEL=VERBOSE -DUSE_CONSOLE=ON ..
```

### CommonAPI-SOMEIP and VSOMEIP runtime libraries
Project: https://github.com/GENIVI/capicxx-someip-runtime.git
which depends on VSOMEIP
Project: https://github.com/GENIVI/vsomeip.git

## Run
```
cd ./scripts
./RunInterface1Service.sh
./RunInterface1Client.sh
```
