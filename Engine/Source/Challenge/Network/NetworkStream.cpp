#include <Challenge/Challenge.h>
#include <Challenge/Network/NetworkStream.h>

namespace challenge
{
	NetworkStream::NetworkStream(const NetworkAddress *address, NetworkProto protocol)
	{
	}

	NetworkStream::~NetworkStream()
	{

	}

	void NetworkStream::Read(TByteArray &data, NetworkAddress *sender)
	{

	}

	void NetworkStream::Write(const TByteArray &data, NetworkAddress *address)
	{

	}

	bool NetworkStream::Open()
	{
		return true;
	}

	void NetworkStream::Close()
	{
	}
}