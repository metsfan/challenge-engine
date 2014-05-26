#include <Challenge/Challenge.h>
#include <Challenge/Network/NetworkStream.h>
#include <Challenge/Network/TCPSocket.h>
#include <Challenge/Network/UDPSocket.h>

namespace challenge
{
	NetworkStream::NetworkStream(const NetworkAddress *address, NetworkProto protocol) :
		mProto(protocol)
	{
		switch (protocol)
		{
		case NetworkProtoTCP:
			mSocket = new TCPSocket(address);
			break;

		case NetworkProtoUDP:
			mSocket = new UDPSocket(address);
			break;
		}
	}

	NetworkStream::~NetworkStream()
	{
		delete mSocket;
	}

	int NetworkStream::Read(TByteArray &data, NetworkAddress *sender)
	{
		return mSocket->Receive(data, sender);
	}

	int NetworkStream::Write(const TByteArray &data, const NetworkAddress *address)
	{
		return mSocket->Send(data, address);
	}

	int NetworkStream::Write(ISerializable *object, const NetworkAddress *address)
	{
		ByteArrayOutputStream stream;
		object->Serialize(stream);

		return this->Write(stream.GetData(), address);
	}

	int NetworkStream::Read(ISerializable *object, NetworkAddress *address)
	{
		TByteArray data;
		int n = this->Read(data, address);

		if (n > 0) {
			ByteArrayInputStream stream(data);
			object->Unserialize(stream);
		}
		
		return n;
	}

	int NetworkStream::Write(const ByteArrayOutputStream &stream, const NetworkAddress *address)
	{
		return this->Write(stream.GetData(), address);
	}

	int NetworkStream::Read(ByteArrayInputStream &stream, NetworkAddress *address)
	{
		TByteArray data;
		int n = this->Read(data, address);

		if (n > 0) {
			stream = ByteArrayInputStream(data);
		}
		
		return n;
	}

	bool NetworkStream::Open()
	{
		//return mSocket.Ready();
		return true;
	}

	void NetworkStream::Close()
	{
		mSocket->Close();
	}
}