#include <Challenge/Challenge.h>
#include <Challenge/Network/UDPSocket.h>

namespace challenge
{
	UDPSocket::UDPSocket(const NetworkAddress *address) :
		NetworkSocket(address)
	{
		this->InitializeSocket(SOCK_DGRAM, IPPROTO_UDP);

		if (address) {
			int result = bind(this->GetSocket(), (struct sockaddr *) &this->GetSockAddr(), sizeof(struct sockaddr_in));
			if (result == SOCKET_ERROR) {
				//TODO report errors here
				int error = WSAGetLastError();
				Logger::Log(LogDebug, "Network error initializing: %d", error);
			}
		}

		//u_long iMode = 1;
		//ioctlsocket(this->GetSocket(), FIONBIO, &iMode);
	}

	UDPSocket::~UDPSocket()
	{
	}

	int UDPSocket::Send(const TByteArray &data, const NetworkAddress *address)
	{
		//const sockaddr_in &addr = this->GetSockAddr();
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr(address->ip.c_str());
		addr.sin_port = htons(address->port);

		int status = sendto(this->GetSocket(), 
			(const char *) &data[0], 
			data.size(), 
			0, 
			(struct sockaddr *) &addr,
			sizeof(struct sockaddr_in));

		if (status == SOCKET_ERROR) {
			//TODO report errors here
			int error = WSAGetLastError();
			Logger::Log(LogDebug, "Network error sending: %d", error);
		}

		return status;
	}

	int UDPSocket::Receive(TByteArray &data, NetworkAddress *address)
	{
		struct sockaddr_in addr;
		int len = sizeof(struct sockaddr_in);

		int status = recvfrom(this->GetSocket(), (char *) &data[0], data.size(), 0, (struct sockaddr *)&addr, &len);

		if (status == SOCKET_ERROR) {
			//TODO report errors here
			int error = WSAGetLastError();
			Logger::Log(LogDebug, "Network error receiving: %d", error);
		}

		if (address) {
			address->ip = std::string(inet_ntoa(addr.sin_addr));
			address->port = ntohs(addr.sin_port);
		}

		return status;
	}
}