#!/bin/bash

export VSOMEIP_APPLICATION_NAME=Interface1-Service
export VSOMEIP_CONFIGURATION=../config/vsomeip.json
export COMMONAPI_CONFIG=../config/commonapi.ini
export LD_LIBRARY_PATH=../build:/usr/local/lib:$LD_LIBRARY_PATH
../build/Interface1-Service
