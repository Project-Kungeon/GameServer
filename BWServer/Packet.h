#include <google/protobuf/message.h>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>

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

	static bool Serialize(
		const asio::mutable_buffer& buffer,
		const short packetCode,
		const google::protobuf::Message& msg)
	{
		const size_t requiredSize = RequiredSize(msg);
		if (buffer.size() < requiredSize)
			return false;

		PacketHeader header;
		header.Length = static_cast<short>(msg.ByteSizeLong());
		header.Code = packetCode;

		memcpy(buffer.data(), &header, sizeof(PacketHeader));

		char* payloadPtr = static_cast<char*>(buffer.data()) + sizeof(PacketHeader);

		// buffer 에서 proto packet으로 변환
		if (!msg.SerializeToArray(payloadPtr,
			static_cast<int>(buffer.size()) - sizeof(PacketHeader)))
			return false;

		return true;
	}

	static bool ParseHeader(
		const asio::mutable_buffer& buffer,
		PacketHeader* header,
		int& offset
	)
	{
		// 읽고 있는 부분이 버퍼 바깥이라면
		if (buffer.size() <= offset)
			return false;

		// 남은 버퍼 데이터가 헤더 사이즈보다 작으면 못 읽음
		const size_t remainedSize = buffer.size() - offset;
		if (remainedSize < sizeof(PacketHeader))
			return false;

		const char* headerPtr = static_cast<char*>(buffer.data()) + offset;
		memcpy(header, headerPtr, sizeof(PacketHeader));
		offset += sizeof(PacketHeader);

		return true;
	}

};