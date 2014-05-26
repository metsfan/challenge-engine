#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Network/Network.h>
#include <Challenge/Network/NetworkSocket.h>
#include <Challenge/Util/Serializable.h>

namespace challenge
{
	class NetworkStream
	{
	public:
		NetworkStream(const NetworkAddress *address, NetworkProto protocol);
		~NetworkStream();

		int Write(ISerializable *object, const NetworkAddress *address = NULL);
		int Write(const TByteArray &data, const NetworkAddress *address = NULL);
		int Write(const ByteArrayOutputStream &stream, const NetworkAddress *address = NULL);

		int Read(ISerializable *object, NetworkAddress *address = NULL);
		int Read(TByteArray &data, NetworkAddress *sender = NULL);
		int Read(ByteArrayInputStream &stream, NetworkAddress *address = NULL);
		
		bool Open();
		void Close();

	private:
		NetworkSocket *mSocket;
		NetworkProto mProto;
	};
};