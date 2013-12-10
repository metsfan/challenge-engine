#include <Challenge/Challenge.h>
#include "NetworkInterface.h"
using namespace challenge;

NetworkInterface::NetworkInterface(std::string ip, int port)
{
	mSocket = new NetworkSocket(ip, port);

	mAddress.ip = mSocket->GetIP();
	mAddress.port = mSocket->GetPort();

	mIsServer = true;
}

void NetworkInterface::WriteData(std::stringstream &dataStream, NetworkAddress address)
{
	mSocket->Send(dataStream, address.ip, address.port);
}

void NetworkInterface::WriteData(std::stringstream &dataStream)
{
	if(mIsServer) {
		TClientList::iterator it = mClients.begin();

		while(it != mClients.end()) {
			NetworkAddress address = (*it);
			mSocket->Send(dataStream, address.ip, address.port);
			++it;
		}
	} else {
		mSocket->Send(dataStream, mServerAddr.ip, mServerAddr.port);
	}
}


std::string NetworkInterface::ReadData()
{
	return mSocket->Receive();
}

void NetworkInterface::AddClient(std::string ip, int port)
{
	mClients.push_back(NetworkAddress(ip, port));
}