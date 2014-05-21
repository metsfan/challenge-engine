#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Network/NetworkSocket.h>

namespace challenge
{
	class TCPSocket : public NetworkSocket
	{
	public:
		TCPSocket(const NetworkAddress *address = NULL);
		~TCPSocket();

		int Send(const TByteArray &data, const NetworkAddress *address = NULL);
		int Receive(TByteArray &data, NetworkAddress *address = NULL);
	};
};