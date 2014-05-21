#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Network/Network.h>

namespace challenge
{
	class NetworkSocket
	{
	public:
		NetworkSocket(const NetworkAddress *address);
		~NetworkSocket();

		virtual int Send(const TByteArray &data, const NetworkAddress *address = NULL) = 0;
		virtual int Receive(TByteArray &data, NetworkAddress *address = NULL) = 0;
		void Close();

	protected:
		const NetworkAddress& GetAddress() { return mAddress; }
		const sockaddr_in& GetSockAddr() { return mAddr; }
		uint32_t GetSocket() { return mSocket; }

		void InitializeSocket(int type, int protocol);

	private:
		NetworkAddress mAddress;
		uint32_t mSocket;
		sockaddr_in mAddr;
		int mAddrSize;
	};
};