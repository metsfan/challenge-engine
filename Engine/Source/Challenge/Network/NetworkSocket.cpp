#include <Challenge/Challenge.h>
#include <iphlpapi.h>
#include <stdlib.h>
//#include <curl/curl.h>
#include "NetworkSocket.h"
using namespace challenge;

#pragma comment(lib, "IPHLPAPI.lib")

NetworkSocket::NetworkSocket(std::string ip, int port)
{
	mSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	Initialize(ip, port);
}

NetworkSocket::~NetworkSocket()
{
}

void NetworkSocket::Initialize(std::string ip, int port)
{
	mAddr.sin_family = AF_INET;
	mAddr.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
	mAddr.sin_port = htons(port);
	mAddrSize = sizeof(mAddr);

	int result = bind(mSocket, (sockaddr *)&mAddr, mAddrSize);
	if (result != 0) {
		//TODO report errors here
		int error = WSAGetLastError();
		if(error == WSAEADDRINUSE) {
			port += 1;
			return Initialize(ip, port);
		}
	} else {
		mIP = ip;
		mPort = port;

		
	}
}

bool NetworkSocket::Send(std::stringstream &data, std::string ip, int port)
{
	//std::string packet;
	std::string packet = data.str();
	
	struct sockaddr_in to;
	to.sin_family = AF_INET;
	to.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
	to.sin_port = htons(port);

	int result = sendto(mSocket, packet.c_str(), packet.length(), 0, (sockaddr *)&to, sizeof(to));
	
	if(result == SOCKET_ERROR) {
		int error = WSAGetLastError();

		return false;
	}

	return true;
}

std::string NetworkSocket::Receive()
{
	std::string incoming;
	sockaddr_in from = mAddr;
	int fromSize = mAddrSize;

	char buf[1024];
	int result = recvfrom(mSocket, buf, 1024, 0, (sockaddr *)&from, &fromSize);

	if(result != SOCKET_ERROR) {
		incoming = std::string(buf, result);
	} else {
		int error = WSAGetLastError();
		printf("stop");
	}

	return incoming;
}

void NetworkSocket::Close()
{
	shutdown(mSocket, SD_BOTH);
}

NetworkAddress NetworkSocket::GetLocalAddress()
{
	NetworkAddress out;

	// Get the local host information
	hostent *localHost = gethostbyname("");
	out.ip = inet_ntoa (*(struct in_addr *)*localHost->h_addr_list);
	//out.ip = "74.72.235.243";
	out.port = 6001;

	//CURL *ch = curl_easy_init();
    
    return out;
}