#include <Engine/Challenge.h>
#include "NetworkServer.h"
#include <Engine/Network/NetworkClient.h>
using namespace challenge;

NetworkServer::NetworkServer(std::string ip, int port) : 
	NetworkInterface(ip, port)
{
}

std::string NetworkServer::ReadData()
{
	return mSocket->Receive();
}

void NetworkServer::WriteData(std::stringstream &dataStream)
{
	TClientList::iterator it = mClients.begin();

	while(it != mClients.end()) {
		NetworkAddress address = (*it);
		mSocket->Send(dataStream, address.ip, address.port);
		++it;
	}
}

void NetworkServer::AddClient(std::string ip, int port)
{
	mClients.push_back(NetworkAddress(ip, port));
}