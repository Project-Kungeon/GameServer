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

		// buffer ���� proto packet���� ��ȯ
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
		// �а� �ִ� �κ��� ���� �ٱ��̶��
		if (buffer.size() <= offset)
			return false;

		// ���� ���� �����Ͱ� ��� ������� ������ �� ����
		const size_t remainedSize = buffer.size() - offset;
		if (remainedSize < sizeof(PacketHeader))
			return false;

		const char* headerPtr = static_cast<char*>(buffer.data()) + offset;
		memcpy(header, headerPtr, sizeof(PacketHeader));
		offset += sizeof(PacketHeader);

		return true;
	}

};