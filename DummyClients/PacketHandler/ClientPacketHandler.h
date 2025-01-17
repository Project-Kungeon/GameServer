#pragma once
#include "pch.h"


// 전역 패킷 핸들러 선언
using PacketHandlerFunc = std::function<bool(SessionPtr&, std::shared_ptr<char[]>, PacketHeader&, int&)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(SessionPtr& session, std::shared_ptr<char[]> buffer, PacketHeader& header, int& offset);

class ClientPacketHandler
{
public:
    static void Init();

    static bool HandlePacket(SessionPtr& session, std::shared_ptr<char[]> ptr, size_t size)
    {
        int offset = 0;

        PacketHeader header;
        //asio::mutable_buffer buffer = asio::buffer(ptr, size);

        //PacketUtil::ParseHeader(buffer, &header, offset);
        return GPacketHandler[header.Code](session, ptr, header, offset);


    }

private:
    template<typename PacketType, typename ProcessFunc>
    static bool HandlePacket(ProcessFunc func, SessionPtr& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        PacketType pkt;
        if (!PacketUtil::Parse(pkt, buffer, header.Length, offset))
        {
            return false;
        }
        
        return func(session, pkt);
    }

private:
    template<typename PacketType, typename ProcessFunc>
    static bool HandlePacket(ProcessFunc func, SessionPtr& session, std::shared_ptr<char[]> ptr, PacketHeader& header, int& offset)
    {
        PacketType pkt;
        char* p = ptr.get();
        asio::mutable_buffer buffer = asio::buffer(p, header.Length);
        
        if (!PacketUtil::Parse(pkt, buffer, header.Length, offset))
        {
            return false;
        }

        return func(session, pkt);
    }

};