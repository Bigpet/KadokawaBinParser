//misakaBinParser.pp : Defines the entry point for the console application.
//

#include "stdafx.h"




int _tmain(int argc, _TCHAR* argv[])
{
	auto buffer = MisakaTool::MisakaArchive::readFullFile("GRP.BIN");


	std::vector<short> index;

	index = MisakaTool::MisakaArchive::getFiles(&buffer[0]);

	std::cout << "HDR_LEN " << index.size() << std::endl;

	std::vector<unsigned short> files= { 
		 0x3DD5
		,0x3DDA
		,0x3DDD
		,0x3DE1
		,0x3DE5
		,0x3DE7
		,0x4D77
		,0x3DEB
		,0x3DEE
		,0x56CC
		,0x561E
		,0x6047
		,0x601C
		,0x6047
		,0x604E
	};

	//MisakaTool::MisakaArchive::extractAllFiles(index,buffer);

	//auto pscfile = MisakaTool::MisakaArchive::readFullFile::readFullFile("22046.PSC");
	//MisakaTool::findNormals(pscfile);

	int pause;
	//std::cin >> pause;


	return 0;
}



