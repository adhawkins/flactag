#ifndef _COLLECTION_H
#define _COLLECTION_H

#include "xmlParser/xmlParser.h"

#include "GenericList.h"

namespace MusicBrainz4
{
	class CRelease;

	class CCollection
	{
	public:
		CCollection(const XMLNode& Node);
		CCollection(const CCollection& Other);
		CCollection& operator =(const CCollection& Other);
		~CCollection();

		std::string ID() const;
		std::string Name() const;
		std::string Editor() const;
		CGenericList<CRelease> *ReleaseList() const;

	private:
		void Cleanup();

		std::string m_ID;
		std::string m_Name;
		std::string m_Editor;
		CGenericList<CRelease> *m_ReleaseList;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CCollection& Collection);

#endif
