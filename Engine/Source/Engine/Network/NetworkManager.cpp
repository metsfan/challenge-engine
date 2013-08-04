#include <Engine/Challenge.h>
#include <boost/thread/thread.hpp>
#include <Engine/Network/NetworkServer.h>
#include <Engine/Network/NetworkClient.h>
#include <Engine/Network/NetworkSocket.h>
#include <Engine/Event/Types/NetworkEventData.h>
#include <Engine/Event/Types/KeyboardEventData.h>
#include <Engine/GameApplication.h>
#include <Engine/Event/EventManager.h>
#include "NetworkManager.h"
using namespace challenge;

NetworkManager::NetworkManager()
{
	mInterface = NULL;
	mIsServer = false;
}

bool NetworkManager::Initialize()
{
	NetworkAddress localAddr = NetworkSocket::GetLocalAddress();
	mInterface = new NetworkInterface(localAddr.ip, localAddr.port);
	if(!mInterface) {
		return false;
	}
	mIsServer = true;

	boost::thread *thread = new boost::thread(NetworkManager::NetworkThreadCallback, this);

	return true;
}

void NetworkManager::SendData(std::stringstream &stream)
{
	mInterface->WriteData(stream);
}

void NetworkManager::NetworkThreadCallback(NetworkManager *netManager)
{
	
	while(true) {
		std::string receivedData = netManager->GetNetworkInterface()->ReadData();

		EventManager *eventManager = GameApplication::GetInstance()->GetEventManager();
		if(eventManager) {
			NetworkReceivedEventData *eventData = new NetworkReceivedEventData(0);
			eventData->packetData = receivedData;
			eventManager->QueueEvent(eventData);
		}
	}
}

void NetworkManager::SwitchToServer()
{
	if(!mInterface->IsServer()) {
		NetworkAddress localAddr = NetworkSocket::GetLocalAddress();
		mInterface->SetIsServer(true);
	}
}

void NetworkManager::SwitchToClient(NetworkAddress serverAddr)
{
	if(mInterface->IsServer()) {
		mInterface->SetIsServer(false);
		mInterface->SetServer(serverAddr);
	}
}

/* Server-only methods */

void NetworkManager::AddClient(NetworkAddress address)
{
	if(mInterface->IsServer()) {
		mInterface->AddClient(address.ip, address.port);
	}
}

/* Client-only methods */
void NetworkManager::SetServer(NetworkAddress address)
{
	if(!mInterface->IsServer()) {
		mInterface->SetServer(address);
	}
}