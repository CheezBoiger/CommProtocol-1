/*
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
#include <CHeader.h>

using namespace Comnet;
CHeader::CHeader()
{
	header = new header_t();
}

CHeader::~CHeader()
{
	if (header != NULL)
	{
		delete header;
		header = NULL;
	}
}

void CHeader::setDestID(Byte destID){ header->destID = destID; }
uint8_t CHeader::getDestID(){ return header->destID; }

void CHeader::setSourceID(Byte sourceID){ header->sourceID = sourceID; }
uint8_t CHeader::getSourceID(){ return header->sourceID; }

void CHeader::setMessageLength(UInt16 mesageLength){ header->messageLength = mesageLength; }
uint16_t CHeader::getMessageLength(){ return header->messageLength; }

void CHeader::setMessageID(UInt16 messageID){ header->messageID = messageID; }
uint16_t CHeader::getMessageID(){ return header->messageID; }

void CHeader::setIV(cli::array<Byte>^ IV)
{
	for (int x = 0; x < KEY_LENGTH; x++)
	{
		header->IV[x] = IV[x];
	}
}

cli::array<Byte>^ CHeader::getIV()
{
	cli::array<Byte>^IV = gcnew cli::array<Byte>(KEY_LENGTH);
	for (int x = 0; x < KEY_LENGTH; x++)
	{
		IV[x] = header->IV[x];
	}
	return IV;
}