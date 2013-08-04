#pragma once

#include <Engine/Challenge.h>
#include <Engine/Event/EventManager.h>

namespace challenge
{
	static const std::string kNegotiationServer = "192.168.1.12:7001";

	struct NetworkAddress {
		std::string ip;
		int port;

		NetworkAddress() {};
		NetworkAddress(std::string ip, int port) : ip(ip), port(port) {};
	};

	class INetworkInterface
	{
	public:
		virtual std::string ReadData() = 0;
		virtual void WriteData(std::stringstream &dataStream) = 0;
		virtual void WriteData(std::stringstream &dataStream, NetworkAddress address) = 0;
		virtual NetworkAddress GetAddress() = 0;
		virtual void Close() = 0;
		virtual void SetServer(NetworkAddress addr) = 0;
		virtual void AddClient(std::string ip, int port) = 0;
		virtual void SetIsServer(bool server) = 0;
		virtual bool IsServer() = 0;
	};

	class INetworkObject
	{
	public:
		virtual void Serialize(std::stringstream &stream) = 0;
		virtual void Unserialize(std::stringstream &stream) = 0;
	};

	typedef std::vector<std::iostream> TPacketList;

	class NetworkManager
	{
	public:
		NetworkManager();
		bool Initialize();

		void SendData(std::stringstream &stream);
		bool IsServer() { return mInterface->IsServer(); }
		void SwitchToServer();
		void SwitchToClient(NetworkAddress serverAddr);

		/* Server-Only methods */
		void AddClient(NetworkAddress address);

		/* Client-only methods */
		void SetServer(NetworkAddress address);

		INetworkInterface *GetNetworkInterface() { return mInterface; }
		NetworkAddress GetAddress() { 
			NetworkAddress addr;
			addr.ip = mLocalIP;
			addr.port = mLocalPort;
			return addr;
		}

	private:
		bool mIsServer;
		INetworkInterface *mInterface;
		std::string mLocalIP;
		int mLocalPort;
		TPacketList mOutgoingQueue;

		static void NetworkThreadCallback(NetworkManager *netManager);
	};
};