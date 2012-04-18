/* --------------------------------------------------------------------------

   flactag -- A tagger for single album FLAC files with embedded CUE sheets
   						using data retrieved from the MusicBrainz service

   Copyright (C) 2006-2012 Andrew Hawkins
   Copyright (C) 2011-2012 Daniel Pocock

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

#include "FlacInfo.h"

#include "TagName.h"

#include "ErrorLog.h"

#include <sstream>

CFlacInfo::CFlacInfo()
:	m_TagBlock(0),
	m_PictureBlock(0),
	m_CuesheetFound(false)
{
}

CFlacInfo::~CFlacInfo()
{
	if (m_TagBlock)
		delete m_TagBlock;

	if (m_PictureBlock)
		delete m_PictureBlock;
}

bool CFlacInfo::CuesheetFound() const
{
	return m_CuesheetFound;
}

void CFlacInfo::SetFileName(const std::string& FileName)
{
	m_Tags.clear();
	m_Cuesheet.Clear();
	m_CoverArt.Clear();

	m_FileName=FileName;

	if (m_TagBlock)
		delete m_TagBlock;

	m_TagBlock=0;

	if (m_PictureBlock)
		delete m_PictureBlock;

	m_PictureBlock=0;

	m_CuesheetFound=false;
}

bool CFlacInfo::Read()
{
	bool RetVal=false;

	m_Tags.clear();
	m_Cuesheet.Clear();
	m_CoverArt.Clear();

	if (m_TagBlock)
		delete m_TagBlock;

	m_TagBlock=0;

	if (m_PictureBlock)
		delete m_PictureBlock;

	m_PictureBlock=0;

	m_CuesheetFound=false;

	if (!m_FileName.empty())
	{
		if (m_Chain.read(m_FileName.c_str()))
		{
			if (m_Chain.is_valid())
			{
				FLAC::Metadata::Iterator Iterator;

				Iterator.init(m_Chain);

				if (Iterator.is_valid())
				{
					do
					{
						switch (Iterator.get_block_type())
						{
							case FLAC__METADATA_TYPE_STREAMINFO:
								break;

							case FLAC__METADATA_TYPE_PADDING:
								break;

							case FLAC__METADATA_TYPE_APPLICATION:
								break;

							case FLAC__METADATA_TYPE_SEEKTABLE:
								break;

							case FLAC__METADATA_TYPE_VORBIS_COMMENT:
								m_TagBlock=(FLAC::Metadata::VorbisComment *)Iterator.get_block();

								if (m_TagBlock->is_valid())
								{
									for (unsigned count=0;count<m_TagBlock->get_num_comments();count++)
									{
										FLAC::Metadata::VorbisComment::Entry Entry=m_TagBlock->get_comment(count);

										std::string Name(Entry.get_field_name(),Entry.get_field_name_length());
										std::string Value(Entry.get_field_value(),Entry.get_field_value_length());

										m_Tags[CTagName(Name)]=CUTF8Tag(Value);
									}
								}

								break;

							case FLAC__METADATA_TYPE_CUESHEET:
							{
								m_CuesheetFound=true;

								FLAC::Metadata::CueSheet *Cuesheet=(FLAC::Metadata::CueSheet *)Iterator.get_block();
								for (unsigned count=0;count<Cuesheet->get_num_tracks();count++)
								{
									FLAC::Metadata::CueSheet::Track Track=Cuesheet->get_track(count);

									if (Track.get_number()==170)
										m_Cuesheet.SetLeadout(CalculateOffset(Track));
									else
										m_Cuesheet.AddTrack(CCuesheetTrack(Track.get_number(),CalculateOffset(Track)));
								}

								delete Cuesheet;

								break;
							}

							case FLAC__METADATA_TYPE_UNDEFINED:
								break;

#ifdef FLAC_API_VERSION_CURRENT
							case FLAC__METADATA_TYPE_PICTURE:
								m_PictureBlock=(FLAC::Metadata::Picture *)Iterator.get_block();
								if (m_PictureBlock->is_valid())
									m_CoverArt.SetArt(m_PictureBlock->get_data(),m_PictureBlock->get_data_length(),true);
								break;
#endif

						}
					} while (Iterator.next());
				}
			}
		}
	}

	if(m_CuesheetFound)
		UpdateCuesheet();

	return RetVal;
}

bool CFlacInfo::UpdateCuesheet()
{
	std::map<int, std::string> Titles;
	std::map<int, std::string> Artists;
	std::map<int, int> trackMappings;
	tTagMap::iterator iterator;
	std::map<int, int>::iterator it2;

	for(iterator=m_Tags.begin(); iterator!=m_Tags.end(); iterator++)
	{
		const CTagName& tagName = iterator->first;
		const CUTF8Tag& tagValue = iterator->second;

		if(tagName == CTagName("ALBUM"))
			m_Cuesheet.setTitle(tagValue.UTF8Value());
		else if(tagName == CTagName("ARTIST"))
			m_Cuesheet.setPerformer(tagValue.UTF8Value());

		if(tagName.Number() > -1)
		{
			if(tagName.Name() == "TRACKNUMBER")
				trackMappings[tagName.Number()] = atoi(tagValue.DisplayValue().c_str());
			else if(tagName.Name() == "ARTIST")
				Artists[tagName.Number()] = tagValue.DisplayValue();
			else if(tagName.Name() == "TITLE")
				Titles[tagName.Number()] = tagValue.DisplayValue();
		}
	}

	for(it2=trackMappings.begin(); it2!=trackMappings.end(); it2++)
	{
		int trackNum = it2->second;
		m_Cuesheet.setTrackPerformer(trackNum, Artists[it2->first]);
		m_Cuesheet.setTrackTitle(trackNum, Titles[it2->first]);
	}
	return true;
}

tTagMap CFlacInfo::Tags() const
{
	return m_Tags;
}

CCoverArt CFlacInfo::CoverArt() const
{
	return m_CoverArt;
}

CCuesheet CFlacInfo::Cuesheet() const
{
	return m_Cuesheet;
}

std::string CFlacInfo::WriteError() const
{
	return m_WriteError;
}

int CFlacInfo::CalculateOffset(const FLAC::Metadata::CueSheet::Track& Track) const
{
	FLAC__uint64 Offset=Track.get_offset();
	FLAC__uint64 MaxIndexOffset=0;

	for (unsigned count=0;count<Track.get_num_indices();count++)
	{
		FLAC__StreamMetadata_CueSheet_Index Index=Track.get_index(count);

		if (Index.number==1)
			MaxIndexOffset=Index.offset;
	}

	Offset+=MaxIndexOffset;
	Offset/=588;
	Offset+=150;

	return Offset;
}

bool CFlacInfo::WriteInfo(const CWriteInfo& WriteInfo)
{
	bool RetVal=true;

	if (m_TagBlock)
	{
		while (m_TagBlock->get_num_comments())
			m_TagBlock->delete_comment(0);

		tTagMap Tags=WriteInfo.Tags();
		tTagMapConstIterator ThisTag=Tags.begin();

		while (Tags.end()!=ThisTag)
		{
			CTagName Name=(*ThisTag).first;
			CUTF8Tag Value=(*ThisTag).second;

			if (!Value.empty())
			{
				FLAC::Metadata::VorbisComment::Entry NewEntry;

				if (!NewEntry.set_field_name(Name.String().c_str()))
				{
					std::stringstream os;
					os << "Error setting field name: '" << Name.String() << "'";
					CErrorLog::Log(os.str());
				}

				if (!NewEntry.set_field_value(Value.UTF8Value().c_str(),Value.UTF8Value().length()))
				{
					std::stringstream os;
					os << "Error setting field value: '" << Value.DisplayValue() << "' for '" << Name.String() << "'";
					CErrorLog::Log(os.str());
				}

				if (!m_TagBlock->insert_comment(m_TagBlock->get_num_comments(),NewEntry))
				{
					std::stringstream os;
					os << "Error inserting comment: '" << Value.DisplayValue() << "' for '" << Name.String() << "'";
					CErrorLog::Log(os.str());
				}
			}

			++ThisTag;
		}

#ifdef FLAC_API_VERSION_CURRENT
		if (WriteInfo.CoverArt())
		{
			if (m_PictureBlock)
				SetPictureBlock(WriteInfo.CoverArt());
			else
			{
				FLAC::Metadata::Iterator Iterator;

				Iterator.init(m_Chain);

				if (Iterator.is_valid())
				{
					//Move to the end
					while (Iterator.next())
						;

					m_PictureBlock = new FLAC::Metadata::Picture;
					SetPictureBlock(WriteInfo.CoverArt());

					RetVal=Iterator.insert_block_after(m_PictureBlock);
				}
			}
		}
		else
		{
			if (m_PictureBlock)
			{
				FLAC::Metadata::Iterator Iterator;

				Iterator.init(m_Chain);

				if (Iterator.is_valid())
				{
					bool Found=false;

					do
					{
						switch (Iterator.get_block_type())
						{
							case FLAC__METADATA_TYPE_PICTURE:
							{
								Found=true;
								RetVal=Iterator.delete_block(true);
								break;
							}

							default:
								break;
						}
					} while (!Found && Iterator.next());
				}
			}
		}

#endif
		if (RetVal)
		{
			RetVal=m_Chain.write();

			if (!RetVal)
			{
				FLAC::Metadata::Chain::Status Status=m_Chain.status();
				m_WriteError=Status.as_cstring();
			}
		}
	}
	else
	{
		m_WriteError.assign("no tag block exists in the FLAC file, create one with metaflac --set-tag=ARTIST=unset <filename.flac>");
		RetVal=false;
	}

	return RetVal;
}

void CFlacInfo::SetTag(const CTagName& Name, const std::string& Value)
{
	bool Found=false;

	for (unsigned count=0;count<m_TagBlock->get_num_comments();count++)
	{
		FLAC::Metadata::VorbisComment::Entry Entry=m_TagBlock->get_comment(count);
		std::string ThisField=Entry.get_field_name();

		if (ThisField==Name.String())
			Found=true;

		if (Found)
		{
			Entry.set_field_name(Name.String().c_str());
			Entry.set_field_value(Value.c_str(),Value.length());
			m_TagBlock->set_comment(count,Entry);
		}
	}

	if (!Found)
	{
		FLAC::Metadata::VorbisComment::Entry NewEntry;

		NewEntry.set_field_name(Name.String().c_str());
		NewEntry.set_field_value(Value.c_str(),Value.length());

		m_TagBlock->insert_comment(m_TagBlock->get_num_comments(),NewEntry);
	}
}

void CFlacInfo::SetPictureBlock(const CCoverArt& CoverArt)
{
	if (m_PictureBlock)
	{
		m_PictureBlock->set_type(FLAC__STREAM_METADATA_PICTURE_TYPE_FRONT_COVER);
		unsigned char *TmpData=new unsigned char[CoverArt.Length()];
		memcpy(TmpData,CoverArt.Data(),CoverArt.Length());
		m_PictureBlock->set_data(TmpData,CoverArt.Length());
		m_PictureBlock->set_width(CoverArt.Width());
		m_PictureBlock->set_height(CoverArt.Height());
		m_PictureBlock->set_mime_type("image/jpeg");
	}
}
