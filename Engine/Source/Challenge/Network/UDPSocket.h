#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Network/NetworkSocket.h>

namespace challenge
{
	class UDPSocket : public NetworkSocket
	{
	public:
		UDPSocket(const NetworkAddress *address = NULL);
		~UDPSocket();

		int Send(const TByteArray &data, const NetworkAddress *address = NULL);
		int Receive(TByteArray &data, NetworkAddress *address = NULL);
	};
};