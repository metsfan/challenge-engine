#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Network/NetworkManager.h>

namespace challenge
{
	class NetworkClient : public NetworkInterface
	{
	public:
		NetworkClient(std::string ip, int port, NetworkProto proto);

		virtual std::string ReadData();
		virtual void WriteData(std::stringstream dataStream);
		void SetServer(NetworkAddress addr) { mServerAddr = addr; }

	private:
		NetworkAddress mServerAddr;
	};
};