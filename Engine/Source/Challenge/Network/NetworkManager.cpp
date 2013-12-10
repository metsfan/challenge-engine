#include <Challenge/Challenge.h>
#include <Challenge/Network/NetworkServer.h>
#include <Challenge/Network/NetworkClient.h>
#include <Challenge/Network/NetworkSocket.h>
#include <Challenge/Event/Types/NetworkEventData.h>
#include <Challenge/Event/Types/KeyboardEventData.h>
#include <Challenge/GameApplication.h>
#include <Challenge/Event/EventManager.h>
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

	std::thread *thread = new std::thread(NetworkManager::NetworkThreadCallback, this);

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