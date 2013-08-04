#pragma once

#include <Engine/Challenge.h>
#include <Engine/Network/NetworkManager.h>

namespace challenge
{
	class NetworkSocket
	{
	public:
		NetworkSocket(std::string ip, int port);
		~NetworkSocket();

		bool Send(std::stringstream &data, std::string ip, int port);
		std::string Receive();
		void Close();
		int GetPort() { return mPort; }
		std::string GetIP() { return mIP; }

		static NetworkAddress GetLocalAddress();

	private:
		std::string mIP;
		int mPort;
		SOCKET mSocket;
		sockaddr_in mAddr;
		int mAddrSize;

		void Initialize(std::string ip, int port);
	};
};