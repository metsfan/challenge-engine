#include <Challenge/Challenge.h>
#include <Challenge/Network/TCPSocket.h>

namespace challenge
{
	TCPSocket::TCPSocket(const NetworkAddress *address) :
		NetworkSocket(address)
	{
		this->InitializeSocket(SOCK_STREAM, IPPROTO_TCP);
	}

	TCPSocket::~TCPSocket()
	{
	}

	int TCPSocket::Send(const TByteArray &data, const NetworkAddress *address)
	{
		return 0;
	}

	int TCPSocket::Receive(TByteArray &data, NetworkAddress *address)
	{
		return 0;
	}
}