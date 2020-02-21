#ifndef INTERFACE1STUBIMPL_HPP
#define INTERFACE1STUBIMPL_HPP

#include "v0/commonapi/examples/Interface1StubDefault.hpp"

class Interface1StubImpl : public v0::commonapi::examples::Interface1StubDefault
{
public:
    Interface1StubImpl() = default;
    virtual ~Interface1StubImpl() = default;

};

#endif // INTERFACE1STUBIMPL_HPP
