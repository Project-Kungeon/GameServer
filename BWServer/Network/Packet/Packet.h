#pragma once

#include <google/protobuf/message.h>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>

#include "spdlog/spdlog.h" 
#include "spdlog/sinks/basic_file_sink.h" 
#include "spdlog/sinks/rotating_file_sink.h" 
#include "spdlog/sinks/daily_file_sink.h" 

using namespace std;
using namespace boost;

struct PacketHeader
{
	short Length;
	short Code;
};

class PacketUtil
{
public:
	static size_t RequiredSize(const google::protobuf::Message& msg)
	{
		return sizeof(PacketHeader) + msg.ByteSizeLong();
	}

	static bool Serialize(const asio::mutable_buffer& buffer, const short packetCode, const google::protobuf::Message& msg)
	{
		const size_t requiredSize = RequiredSize(msg);
		if (buffer.size() < requiredSize)
			return false;

		PacketHeader header;
		header.Length = static_cast<short>(msg.ByteSizeLong());
		header.Code = packetCode;

		memcpy(buffer.data(), &header, sizeof(PacketHeader));

		// buffer.data() : 헤더의 시작점
		// buffer.data()) + sizeof(PacketHeader) : 헤더의 끝점 = payload 시작점
		char* payloadPtr = static_cast<char*>(buffer.data()) + sizeof(PacketHeader);
		if (!msg.SerializeToArray(payloadPtr, static_cast<int>(buffer.size()) - sizeof(PacketHeader)))
			return false;

		return true;
	}

	static bool ParseHeader(const asio::mutable_buffer& buffer, PacketHeader* header, int& offset)
	{
		// 읽고 있는 부분이 버퍼 바깥으로 나갈 경우
		if (buffer.size() <= offset)
			return false;

		// 남은 버퍼 데이터가 헤더 사이즈보다 작을 경우
		const size_t remainedSize = buffer.size() - offset;
		if (remainedSize < sizeof(PacketHeader))
			return false;

		const char* headerPtr = static_cast<char*>(buffer.data()) + offset;
		memcpy(header, headerPtr, sizeof(PacketHeader));
		offset += sizeof(PacketHeader);

		return true;
	}

	// payloadSize : 헤더를 제외한 사이즈
	// offset : 헤더 이후부터 시작되는 payload 시작점
	static bool Parse(google::protobuf::Message& msg, const asio::mutable_buffer& buffer, const int payloadSize, int& offset)
	{
		if (buffer.size() < sizeof(PacketHeader))
			return false;

		const char* payloadPtr = static_cast<char*>(buffer.data()) + offset;
		const size_t remainedSize = buffer.size() - offset;
		const bool parseResult = msg.ParseFromArray(payloadPtr, payloadSize);
		if (parseResult)
		{
			offset += static_cast<int>(msg.ByteSizeLong());
			return true;
		}
		else
		{
			spdlog::error("Failed to parse packet");
			return false;
		}
	}

	static std::shared_ptr<char[]> MakeSendBuffer(google::protobuf::Message& msg, const short packetCode)
	{
		const size_t requiredSize = PacketUtil::RequiredSize(msg);

		std::shared_ptr<char[]> rawBuffer = std::make_shared<char[]>(requiredSize);
		auto sendBuffer = asio::buffer(rawBuffer.get(), requiredSize);
		PacketUtil::Serialize(sendBuffer, packetCode, msg);

		return rawBuffer;
	}
};