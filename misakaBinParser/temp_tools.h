#pragma once

#include "stdafx.h"

namespace MisakaTool{
//takes a shtxps file and writes it into an uncompressed PNM file
	void writePNM(std::vector<char> buffer, std::string filename);

	//finds and prints out potential positions of normalized coordinate triplets
	void findNormals(std::vector<char> &buffer);
};