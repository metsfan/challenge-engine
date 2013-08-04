#pragma once

#include <Engine/Challenge.h>
#include <Engine/Network/NetworkManager.h>
#include <Engine/Network/NetworkInterface.h>

namespace challenge
{
	typedef std::vector<NetworkAddress> TClientList;

	class NetworkServer : public NetworkInterface
	{
	public:
		NetworkServer(std::string ip, int port);

		virtual std::string ReadData();
		virtual void WriteData(std::stringstream &dataStream);

		void AddClient(std::string ip, int port);

	private:
		TClientList mClients;
	};
};