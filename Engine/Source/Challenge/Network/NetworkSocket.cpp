#include <Challenge/Challenge.h>
#include <iphlpapi.h>
#include <stdlib.h>
//#include <curl/curl.h>
#include "NetworkSocket.h"

#pragma comment(lib, "IPHLPAPI.lib")

namespace challenge
{
	NetworkSocket::NetworkSocket(const NetworkAddress *address)
	{
		if (address) {
			uint64_t ip;
			if (address->ip.length() > 0) {
				ip = inet_addr(address->ip.c_str());
			}
			else {
				ip = INADDR_ANY;
			}

			mAddr.sin_family = AF_INET;
			mAddr.sin_addr.s_addr = ip;
			mAddr.sin_port = htons(address->port);
		}
		
	}

	NetworkSocket::~NetworkSocket()
	{
	}

	void NetworkSocket::Close()
	{
		shutdown(mSocket, SD_BOTH);
	}

	void NetworkSocket::InitializeSocket(int type, int protocol)
	{
		mSocket = socket(AF_INET, type, protocol);
	}
}