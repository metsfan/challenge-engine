#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Network/Network.h>
#include <Challenge/Network/NetworkSocket.h>

namespace challenge
{
	class NetworkStream
	{
	public:
		NetworkStream(const NetworkAddress *address, NetworkProto protocol);
		~NetworkStream();

		void Read(TByteArray &data, NetworkAddress *sender = NULL);
		void Write(const TByteArray &data, NetworkAddress *address = NULL);
		
		bool Open();
		void Close();

	private:
		NetworkSocket *mSocket;
	};
};