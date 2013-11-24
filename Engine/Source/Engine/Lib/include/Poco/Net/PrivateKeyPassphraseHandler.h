//
// PrivateKeyPassphraseHandler.h
//
// $Id: //poco/1.4/NetSSL_OpenSSL/include/Poco/Net/PrivateKeyPassphraseHandler.h#1 $
//
// Library: NetSSL_OpenSSL
// Package: SSLCore
// Module:  PrivateKeyPassphraseHandler
//
// Definition of the PrivateKeyPassphraseHandler class.
//
// Copyright (c) 2006-2009, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef NetSSL_PrivateKeyPassphraseHandler_INCLUDED
#define NetSSL_PrivateKeyPassphraseHandler_INCLUDED


#include "Poco/Net/NetSSL.h"


namespace Poco {
namespace Net {


class NetSSL_API PrivateKeyPassphraseHandler
	/// A passphrase handler is needed whenever the private key of a certificate is loaded and the certificate is protected
	/// by a passphrase. The PrivateKeyPassphraseHandler's task is to provide that passphrase.
	/// One can install one's own PrivateKeyPassphraseHandler by implementing this interface. Note that
	/// in the implementation file of the subclass the following code must be present (assuming you use the namespace My_API 
	/// and the name of your handler class is MyGuiHandler):
	///    
	///    #include "Poco/Net/PrivateKeyFactory.h"
	///    ...
	///    POCO_REGISTER_KEYFACTORY(My_API, MyGuiHandler)
	///
	/// One can either set the handler directly in the startup code of the main method of ones application by calling
	///
	///    SSLManager::instance().initialize(myguiHandler, myInvalidCertificateHandler, mySSLContext)
	///
	/// or in case one's application extends Poco::Util::Application one can use an XML configuration and put the following entry
	/// under the path openSSL.privateKeyPassphraseHandler:
	///    
	///    <privateKeyPassphraseHandler>
	///        <name>MyGuiHandler</name>
	///        <options>
	///            [...] // Put optional config params for the handler here
	///        </options>
	///    </privateKeyPassphraseHandler>
	///
	/// Note that the name of the passphrase handler must be same as the one provided to the POCO_REGISTER_KEYFACTORY macro.
{
public:
	PrivateKeyPassphraseHandler(bool onServerSide);
		/// Creates the PrivateKeyPassphraseHandler. Automatically registers at the SSLManager::PrivateKeyPassword event.

	virtual ~PrivateKeyPassphraseHandler();
		/// Destroys the PrivateKeyPassphraseHandler.

	virtual void onPrivateKeyRequested(const void* pSender, std::string& privateKey) = 0;
		/// Returns the requested private key in the parameter privateKey.

	bool serverSide() const;

private:
	bool _serverSide;
};


//
// inlines
//
inline bool PrivateKeyPassphraseHandler::serverSide() const
{
	return _serverSide;
}


} } // namespace Poco::Net


#endif // NetSSL_PrivateKeyPassphraseHandler_INCLUDED
