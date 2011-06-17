/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   Flactag is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/

#ifndef _MUSICBRAINZ4_TEXT_REPRESENTATION_H
#define _MUSICBRAINZ4_TEXT_REPRESENTATION_H

#include <iostream>
#include <string>

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
{
	class CTextRepresentation
	{
	public:
		CTextRepresentation(const XMLNode& Node=XMLNode::emptyNode());
		CTextRepresentation(const CTextRepresentation& Other);
		CTextRepresentation& operator =(const CTextRepresentation& Other);

		std::string Language() const;
		std::string Script() const;

	private:
		std::string m_Language;
		std::string m_Script;

	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CTextRepresentation& TextRepresentation);

#endif