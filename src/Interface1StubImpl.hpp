#ifndef INTERFACE1STUBIMPL_HPP
#define INTERFACE1STUBIMPL_HPP

#include "v0/commonapi/examples/Interface1StubDefault.hpp"

class Interface1StubImpl : public v0::commonapi::examples::Interface1StubDefault
{
public:
    Interface1StubImpl() = default;
    virtual ~Interface1StubImpl() = default;

    virtual void setUInt32(
        const std::shared_ptr<CommonAPI::ClientId> _client,
        uint32_t _value,
        setUInt32Reply_t _reply) override;
    virtual void getUInt32(const std::shared_ptr<CommonAPI::ClientId> _client, getUInt32Reply_t _reply) override;

private:
    uint32_t m_Uint32;
};

#endif // INTERFACE1STUBIMPL_HPP
