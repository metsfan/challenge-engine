#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Network/NetworkManager.h>
#include <Challenge/Network/NetworkInterface.h>

namespace challenge
{
	typedef std::vector<NetworkAddress> TClientList;

	class NetworkServer : public NetworkInterface
	{
	public:
		NetworkServer(std::string ip, int port, NetworkProto proto);

		virtual std::string ReadData();
		virtual void WriteData(std::stringstream &dataStream);

		void AddClient(std::string ip, int port);

	private:
		TClientList mClients;
	};
};