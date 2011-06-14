#ifndef _MUSICBRAINZ4_ANNOTATION_H
#define _MUSICBRAINZ4_ANNOTATION_H

#include <string>
#include <iostream>

#include "xmlParser.h"

namespace MusicBrainz4
{
	class CAnnotation
	{
	public:
		CAnnotation(const XMLNode& Node);
		CAnnotation(const CAnnotation& Other);
		CAnnotation& operator =(const CAnnotation& Other);

		std::string Type() const;
		std::string Entity() const;
		std::string Name() const;
		std::string Text() const;

	private:
		std::string m_Type;
		std::string m_Entity;
		std::string m_Name;
		std::string m_Text;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CAnnotation& Annotation);

#endif
