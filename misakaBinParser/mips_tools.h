#pragma once

namespace MisakaTool{

	//helper struct to store state of the MIPS code translation
	struct MipsCpy{
		std::vector<char> *container = nullptr;
		std::vector<char> *container2 = nullptr;

		long lbu(long adr);

		void sb(long toStore, long location);

		void sw(long toStore, long location);
	};
};