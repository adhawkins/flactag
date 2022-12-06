/* --------------------------------------------------------------------------

	 flactag -- A tagger for single album FLAC files with embedded CUE sheets
							using data retrieved from the MusicBrainz service

	 Copyright (C) 2006-2022 Andrew Hawkins

	 This file is part of flactag.

	 This program is free software: you can redistribute it and/or modify
	 it under the terms of the GNU General Public License as published by
	 the Free Software Foundation, either version 3 of the License, or
	 (at your option) any later version.

	 Flactag is distributed in the hope that it will be useful,
	 but WITHOUT ANY WARRANTY; without even the implied warranty of
	 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	 Lesser General Public License for more details.

	 You should have received a copy of the GNU General Public
	 License along with this library; if not, write to the Free Software
	 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

		 $Id$

----------------------------------------------------------------------------*/

#include "CoverArt.h"

#include <sstream>

#include <Magick++.h>

#include "base64.h"
#include "ErrorLog.h"

CCoverArt::CCoverArt(const unsigned char *Data, size_t Length)
		: m_Data(0),
			m_Length(0),
			m_Width(0),
			m_Height(0)
{
	SetArt(Data, Length, true);
}

CCoverArt::CCoverArt(const std::vector<unsigned char> &Data)
		: m_Data(0),
			m_Length(0),
			m_Width(0),
			m_Height(0)
{
	SetArt(&Data[0], Data.size(), true);
}

CCoverArt::CCoverArt(const CCoverArt &Other)
		: m_Data(0),
			m_Length(0),
			m_Width(0),
			m_Height(0)
{
	if (this != &Other)
		*this = Other;
}

CCoverArt::~CCoverArt()
{
	Free();
}

void CCoverArt::Free()
{
	if (m_Data)
		delete[] m_Data;

	m_Data = 0;
	m_Length = 0;
	m_Width = 0;
	m_Height = 0;
	m_MimeType.clear();
}

CCoverArt &CCoverArt::operator=(const CCoverArt &Other)
{
	m_Width = Other.m_Width;
	m_Height = Other.m_Height;
	m_MimeType = Other.m_MimeType;
	SetArt(Other.m_Data, Other.m_Length, false, Other.m_MimeType);

	return *this;
}

bool CCoverArt::operator==(const CCoverArt &Other) const
{
	bool RetVal = false;

	if (m_Length == 0 && Other.m_Length == 0)
	{
		RetVal = true;
	}
	else if (m_Length == Other.m_Length && m_MimeType == Other.m_MimeType)
	{
		Magick::Blob ThisBlob(m_Data, m_Length);
		Magick::Image ThisImage(ThisBlob);

		Magick::Blob OtherBlob(Other.m_Data, Other.m_Length);
		Magick::Image OtherImage(OtherBlob);

		RetVal = ThisImage.compare(OtherImage);
	}

	return RetVal;
}

bool CCoverArt::operator!=(const CCoverArt &Other) const
{
	return !(*this == Other);
}

CCoverArt::operator std::string() const
{
	return rfc822_binary(m_Data, m_Length);
}

CCoverArt::operator bool() const
{
	return m_Length != 0;
}

void CCoverArt::Clear()
{
	Free();
}

void CCoverArt::SetArt(const unsigned char *Data, size_t Length, bool RetrieveDimensions, const std::string &MimeType)
{
	Free();

	if (Data && Length)
	{
		if (Length > 16 * 1024 * 1024)
		{
			Magick::Blob Blob(Data, Length);
			Magick::Image Image(Blob);

			Image.resize(Magick::Geometry(1920, 1080));

			Magick::Blob NewBlob;
			Image.write(&NewBlob);

			m_Data = new unsigned char[NewBlob.length()];
			m_Length = NewBlob.length();
			memcpy(m_Data, NewBlob.data(), NewBlob.length());
		}
		else
		{
			m_Data = new unsigned char[Length];
			m_Length = Length;
			memcpy(m_Data, Data, Length);
		}

		m_MimeType = MimeType;

		if (RetrieveDimensions)
			GetDimensions();
	}
}

unsigned char *CCoverArt::Data() const
{
	return m_Data;
}

size_t CCoverArt::Length() const
{
	return m_Length;
}

void CCoverArt::GetDimensions()
{
	if (!m_Width || !m_Height || m_MimeType.empty())
	{
		if (m_Length)
		{
			Magick::Blob Blob(m_Data, m_Length);
			Magick::Image Image;
			Image.ping(Blob); //'ping' just reads enough of the image to determine its metadata

			auto Magick = Image.magick();
			if (!Magick.empty())
			{
				try
				{
					Magick::CoderInfo CoderInfo(Magick);

					auto Size = Image.size();

					m_Width = Size.width();
					m_Height = Size.height();

					if (m_MimeType.empty())
						m_MimeType = CoderInfo.mimeType();
				}
				catch (const std::exception &e)
				{
					std::stringstream os;
					os << "ImageMagick exception: '" << e.what() << "' - '" << Magick << "'";
					CErrorLog::Log(os.str());
				}
			}
			else
			{
				std::stringstream os;
				auto Size = Image.size();
				os << "ImageMagick 'Magick' is empty - " << Size.width() << " x " << Size.height();
				CErrorLog::Log(os.str());
			}
		}
	}
}

int CCoverArt::Width() const
{
	return m_Width;
}

int CCoverArt::Height() const
{
	return m_Height;
}

std::string CCoverArt::MimeType() const
{
	return m_MimeType;
}
