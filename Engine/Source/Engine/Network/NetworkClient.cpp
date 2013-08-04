#include <Engine/Challenge.h>
#include <Engine/Network/NetworkInterface.h>
#include "NetworkClient.h"
using namespace challenge;

NetworkClient::NetworkClient(std::string ip, int port) : 
	NetworkInterface(ip, port)
{
}

std::string NetworkClient::ReadData()
{
	return mSocket->Receive();
}

void NetworkClient::WriteData(std::stringstream dataStream)
{
	mSocket->Send(dataStream, mServerAddr.ip, mServerAddr.port);
}