#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Network/NetworkManager.h>
#include <Challenge/Network/NetworkSocket.h>

namespace challenge
{
	typedef std::vector<NetworkAddress> TClientList;

	class NetworkInterface : public INetworkInterface
	{
	public:
		NetworkInterface(std::string ip, int port);

		virtual std::string ReadData();
		virtual void WriteData(std::stringstream &dataStream);
		virtual void WriteData(std::stringstream &dataStream, NetworkAddress address);
		virtual NetworkAddress GetAddress() { return mAddress; }
		virtual void Close() { mSocket->Close(); }
		virtual void SetServer(NetworkAddress addr) { mServerAddr = addr; }
		virtual void AddClient(std::string ip, int port);
		virtual void SetIsServer(bool server) { mIsServer = server; }
		virtual bool IsServer() { return mIsServer; }

	protected:
		NetworkSocket *mSocket;
		NetworkAddress mAddress;
		TClientList mClients;
		NetworkAddress mServerAddr;
		bool mIsServer;
	};
};