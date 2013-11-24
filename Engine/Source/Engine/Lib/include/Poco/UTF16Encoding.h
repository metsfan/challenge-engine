//
// UTF16Encoding.h
//
// $Id: //poco/1.4/Foundation/include/Poco/UTF16Encoding.h#1 $
//
// Library: Foundation
// Package: Text
// Module:  UTF16Encoding
//
// Definition of the UTF16Encoding class.
//
// Copyright (c) 2004-2007, Applied Informatics Software Engineering GmbH.
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


#ifndef Foundation_UTF16Encoding_INCLUDED
#define Foundation_UTF16Encoding_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/TextEncoding.h"


namespace Poco {


class Foundation_API UTF16Encoding: public TextEncoding
	/// UTF-16 text encoding, as defined in RFC 2781.
	///
	/// When converting from UTF-16 to Unicode, surrogates are
	/// reported as they are - in other words, surrogate pairs
	/// are not combined into one Unicode character. 
	/// When converting from Unicode to UTF-16, however, characters
	/// outside the 16-bit range are converted into a low and
	/// high surrogate.
{
public:
	enum ByteOrderType
	{
		BIG_ENDIAN_BYTE_ORDER,
		LITTLE_ENDIAN_BYTE_ORDER,
		NATIVE_BYTE_ORDER
	};
	
	UTF16Encoding(ByteOrderType byteOrder = NATIVE_BYTE_ORDER);
		/// Creates and initializes the encoding for the given byte order.
		
	UTF16Encoding(int byteOrderMark);
		/// Creates and initializes the encoding for the byte-order
		/// indicated by the given byte-order mark, which is the Unicode
		/// character 0xFEFF.
		
	~UTF16Encoding();
	
	ByteOrderType getByteOrder() const;
		/// Returns the byte-order currently in use.
		
	void setByteOrder(ByteOrderType byteOrder);
		/// Sets the byte order.
		
	void setByteOrder(int byteOrderMark);
		/// Sets the byte order according to the given
		/// byte order mark, which is the Unicode
		/// character 0xFEFF.
	
	const char* canonicalName() const;
	bool isA(const std::string& encodingName) const;
	const CharacterMap& characterMap() const;
	int convert(const unsigned char* bytes) const;
	int convert(int ch, unsigned char* bytes, int length) const;
	int queryConvert(const unsigned char* bytes, int length) const;
	int sequenceLength(const unsigned char* bytes, int length) const;
	
private:
	bool _flipBytes;
	static const char* _names[];
	static const CharacterMap _charMap;
};


} // namespace Poco


#endif // Foundation_UTF16Encoding_INCLUDED
