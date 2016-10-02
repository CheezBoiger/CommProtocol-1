/*
Serial configurations.

Copyright (C) 2016  Michael Wallace, Mario Garcia.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <CommProto/serialization/objectstream.h>
#include <CommProto/debug/comms_debug.h>

#include <string.h>

using namespace comnet::serialization;

ObjectStream::ObjectStream():currentPostion(HEADER_SIZE)
{
	streamBuffer = new uint8_t[MAX_BUFFER_SIZE];
}

ObjectStream::~ObjectStream()
{
	delete[] streamBuffer;
	streamBuffer = NULL;
}


void ObjectStream::setBuffer(const char* buffer, int len)
{
	for (currentPostion = 0; currentPostion < len; currentPostion++)
	{
		streamBuffer[currentPostion] = buffer[currentPostion];
	}
}

void ObjectStream::serializeHeader(header_t header)
{
	//not sure if more is needed kind of a waste of space
	headerPacket.destID = header.destID;
	header.serialize(streamBuffer, 0);
}

header_t ObjectStream::deserializeHeader()
{
	header_t header;
	header.deserialize(streamBuffer, 0);	
	return header;
}

/*******************************************************/
/*******************************************************/
/*******************************************************/
/********************* INPUT ***************************/
/*******************************************************/
/*******************************************************/
/*******************************************************/

ObjectStream& ObjectStream::operator<<(string_t& data)
{
	uint8_t strLen = 0;
	str_length(data, strLen);
	// + 1 for null termination + 1 for storing length of string as byte
	if (currentPostion + strLen + 2 < MAX_PACKET_SIZE)
	{
	        //COMMS_DEBUG("STRING BEFORE: %d\n", currentPostion);
		currentPostion += packString(data, strLen, streamBuffer + currentPostion);
		//COMMS_DEBUG("STRING AFTER: %d\n", currentPostion);
	}
	else
	{
		printErrorOverFlow();
	}
	return *this;
}


ObjectStream& ObjectStream::operator<<(std::wstring& data)
{

	//needs string leng
	uint32_t strLen = data.length();
	// + 2 for null termination + 1 for storing length of string as byte
	if (currentPostion + strLen + 2 < MAX_PACKET_SIZE)
	{
	        COMMS_DEBUG("SIZE BEFORE: %d\n", currentPostion);
		currentPostion += packWideString(data,strLen, streamBuffer + currentPostion);
		COMMS_DEBUG("SIZE AFTER: %d\n", currentPostion);
	}
	else
	{
		printErrorOverFlow();
	}
	return *this;
}


ObjectStream& ObjectStream::operator<<(std::string& data) 
{
  uint32_t strLen = data.size();
  if (currentPostion + strLen + 2 < MAX_PACKET_SIZE) {
    currentPostion += packString((string_t)data.c_str(), strLen, streamBuffer + currentPostion);
  } else {
    printErrorOverFlow();
  }

  return *this;
}


ObjectStream& ObjectStream::operator<<(uint8_t& data)
{
	if (currentPostion + sizeof(uint8_t) < MAX_PACKET_SIZE)
	{
		currentPostion += packByte(data, streamBuffer + currentPostion);
	}
	else
	{
		printErrorOverFlow();
	}
	return *this;
}


ObjectStream& ObjectStream::operator<<(int8_t& data)
{
	if (currentPostion + sizeof(int8_t) < MAX_PACKET_SIZE)
	{
		currentPostion += packByte(data, streamBuffer + currentPostion);
	}
	else
	{
		printErrorOverFlow();
	}
	return *this;
}


ObjectStream& ObjectStream::operator<<(uint16_t& data)
{
	if (currentPostion + sizeof(uint16_t) < MAX_PACKET_SIZE)
	{
		currentPostion += packUint16(data, streamBuffer + currentPostion);
	}
	else
	{
		printErrorOverFlow();
	}
	return *this;
}

ObjectStream& ObjectStream::operator<<(int16_t& data)
{
	if (currentPostion + sizeof(int16_t) < MAX_PACKET_SIZE)
	{
		currentPostion += packInt16(data, streamBuffer + currentPostion);
	}
	else
	{
		printErrorOverFlow();
	}
	return *this;
}

ObjectStream& ObjectStream::operator<<(int32_t& data)
{
	if (currentPostion + sizeof(int32_t) < MAX_PACKET_SIZE)
	{
		currentPostion += packInt32(data, streamBuffer + currentPostion);
	}
	else
	{
		printErrorOverFlow();
	}
	return *this;
}


ObjectStream& ObjectStream::operator<<(uint32_t& data)
{
	if (currentPostion + sizeof(uint32_t) < MAX_PACKET_SIZE)
	{
		currentPostion += packUint32(data, streamBuffer + currentPostion);
	}
	else
	{
		printErrorOverFlow();
	}
	return *this;
}
ObjectStream& ObjectStream::operator<<(int64_t& data)
{
	if (currentPostion + sizeof(int64_t) < MAX_PACKET_SIZE)
	{
		currentPostion += packInt64(data, streamBuffer + currentPostion);
	}
	else
	{
		printErrorOverFlow();
	}
	return *this;
}
ObjectStream& ObjectStream::operator<<(uint64_t& data)
{
	if (currentPostion + sizeof(uint64_t) < MAX_PACKET_SIZE)
	{
		currentPostion += packUint64(data, streamBuffer + currentPostion);
	}
	else
	{
		printErrorOverFlow();
	}
	return *this;
}
ObjectStream& ObjectStream::operator<<(real32_t& data)
{
	if (currentPostion + sizeof(real32_t) < MAX_PACKET_SIZE)
	{
		currentPostion += packReal32(data, streamBuffer + currentPostion);
	}
	else
	{
		printErrorOverFlow();
	}
	return *this;
}

ObjectStream& ObjectStream::operator<<(real64_t& data)
{
	if (currentPostion + sizeof(real64_t) < MAX_PACKET_SIZE)
	{
		currentPostion += packReal64(data, streamBuffer + currentPostion);
	}
	else
	{
		printErrorOverFlow();
	}
	return *this;
}


/*******************************************************/
/*******************************************************/
/*******************************************************/
/********************* OUTPUT **************************/
/*******************************************************/
/*******************************************************/
/*******************************************************/

ObjectStream& ObjectStream::operator>>(string_t& data)
{
	uint8_t strLen = 0;
	strLen = unpackByte(streamBuffer + currentPostion - 1);
	// + 1 for null termination + 1 for storing length of string as byte
	currentPostion -= (strLen + 2);

	strLen = unpackString(data,strLen,streamBuffer + currentPostion);



	return *this;
}

ObjectStream& ObjectStream::operator>>(std::wstring& data)
{
	uint32_t strLen = unpackByte(streamBuffer + currentPostion - 1);
	data.resize(strLen + 1);

	// + 2 for null termination + 1 for storing length of string as byte
	currentPostion -= (strLen + 2);
	strLen = unpackWideString(data, strLen,streamBuffer + currentPostion);

	return *this;
}

ObjectStream& ObjectStream::operator>>(std::string& data) 
{
  uint32_t strLen = unpackByte(streamBuffer + currentPostion - 1);
  data.resize(strLen + 1);
  currentPostion -= (strLen + 2);
  string_t temp = (string_t) malloc(data.size());
  strLen = unpackString(temp, strLen, streamBuffer + currentPostion);
  data = temp;
  free_pointer(temp);
  return *this;
}

ObjectStream& ObjectStream::operator>>(uint8_t& data)
{
	if ((currentPostion -= sizeof(uint8_t)) >= HEADER_SIZE)
	{
		data = unpackByte(streamBuffer + currentPostion);
	}
	else
	{
		currentPostion += sizeof(uint8_t);
		printErrorUnderFlow();
	}
	return *this;
}

ObjectStream& ObjectStream::operator>>(int8_t& data)
{
	if ((currentPostion -= sizeof(int8_t)) >= HEADER_SIZE)
	{
		data = unpackByte(streamBuffer + currentPostion);
	}
	else
	{
		currentPostion += sizeof(int8_t);
		printErrorUnderFlow();
	}
	return *this;
}

ObjectStream& ObjectStream::operator>>(uint16_t& data)
{
	if ((currentPostion -= sizeof(uint16_t)) >= HEADER_SIZE)
	{
		data = unpackUint16(streamBuffer + currentPostion);
	}
	else
	{
		currentPostion += sizeof(uint16_t);
		printErrorUnderFlow();
	}
	return *this;
}

ObjectStream& ObjectStream::operator>>(int16_t& data)
{
	if ((currentPostion -= sizeof(int16_t)) >= HEADER_SIZE)
	{
		data = unpackInt16(streamBuffer + currentPostion);
	}
	else
	{
		currentPostion += sizeof(int16_t);
		printErrorUnderFlow();
	}
	return *this;
}

ObjectStream& ObjectStream::operator>>(uint32_t& data)
{
	if ((currentPostion -= sizeof(uint32_t)) >= HEADER_SIZE)
	{
		data = unpackUint32(streamBuffer + currentPostion);
	}
	else
	{
		currentPostion += sizeof(uint32_t);
		printErrorUnderFlow();
	}
	return *this;
}

ObjectStream& ObjectStream::operator>>(int32_t& data)
{
	if ((currentPostion -= sizeof(int32_t)) >= HEADER_SIZE)
	{
		data = unpackInt32(streamBuffer + currentPostion);
	}
	else
	{
		currentPostion += sizeof(int32_t);
		printErrorUnderFlow();
	}
	return *this;
}

ObjectStream& ObjectStream::operator>>(uint64_t& data)
{
	if ((currentPostion -= sizeof(uint64_t)) >= HEADER_SIZE)
	{
		data = unpackUint64(streamBuffer + currentPostion);
	}
	else
	{
		currentPostion += sizeof(uint64_t);
		printErrorUnderFlow();
	}
	return *this;
}

ObjectStream& ObjectStream::operator>>(int64_t& data)
{
	if ((currentPostion -= sizeof(int64_t)) >= HEADER_SIZE)
	{
		data = unpackInt64(streamBuffer + currentPostion);
	}
	else
	{
		currentPostion += sizeof(int64_t);
		printErrorUnderFlow();
	}
	return *this;
}

ObjectStream& ObjectStream::operator>>(real32_t& data)
{
	if ((currentPostion -= sizeof(real32_t)) >= HEADER_SIZE)
	{
		data = unpackReal32(streamBuffer + currentPostion);
	}
	else
	{
		currentPostion += sizeof(real32_t);
		printErrorUnderFlow();
	}
	return *this;
}

ObjectStream& ObjectStream::operator>>(real64_t& data)
{
	if ((currentPostion -= sizeof(real64_t)) >= HEADER_SIZE)
	{
		data = unpackReal64(streamBuffer + currentPostion);
	}
	else
	{
		currentPostion += sizeof(real64_t);
		printErrorUnderFlow();
	}
	return *this;
}