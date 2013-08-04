#pragma once

#include <Engine/Challenge.h>
#include <Engine/Event/EventData.h>

namespace challenge
{
	static const std::string kNetworkReceivedEventType = "network_received";
	static const std::string kNetworkSentEventType = "network_sent";

	class NetworkEventData : public EventData
	{
	public:
		std::string packetData;

		NetworkEventData(int timestamp) : EventData(timestamp) {}
		virtual std::string GetEventType() = 0;
	};

	class NetworkReceivedEventData : public NetworkEventData
	{
	public:
		NetworkReceivedEventData(int timestamp) : NetworkEventData(timestamp) {}
		virtual std::string GetEventType() { return kNetworkReceivedEventType; }
	};

	class NetworkSentEventData : public NetworkEventData
	{
	public:

		NetworkSentEventData(int timestamp) : NetworkEventData(timestamp) {}
		virtual std::string GetEventType() { return kNetworkSentEventType; }
	};
};