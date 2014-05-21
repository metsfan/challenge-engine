#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Event/EventManager.h>

namespace challenge
{
	static const std::string kNegotiationServer = "192.168.1.12:7001";

	struct NetworkAddress {
		std::string ip;
		int port;

		NetworkAddress() {};
		NetworkAddress(std::string ip, int port) : ip(ip), port(port) {};
	};

	enum NetworkProto
	{
		NetworkProtoUDP,
		NetworkProtoTCP
	};

	class INetworkObject
	{
	public:
		virtual void Serialize(std::stringstream &stream) = 0;
		virtual void Unserialize(std::stringstream &stream) = 0;
	};
};