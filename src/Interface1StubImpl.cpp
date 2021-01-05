#include "Interface1StubImpl.hpp"

void Interface1StubImpl::setUInt32(
    const std::shared_ptr<CommonAPI::ClientId> _client,
    uint32_t _value,
    setUInt32Reply_t _reply)
{
    (void)_client;
    m_Uint32 = _value;
    _reply();
}

void Interface1StubImpl::getUInt32(const std::shared_ptr<CommonAPI::ClientId> _client, getUInt32Reply_t _reply)
{
    (void)_client;
    _reply(m_Uint32);
}
