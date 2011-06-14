#include "GenericList.h"

#include <string>

#include "Alias.h"

int main(int argc, const char *argv[])
{
	argc=argc;
	argv=argv;

	MusicBrainz4::CGenericList<MusicBrainz4::CAlias> List;

	std::cout << List;

	return 0;
}