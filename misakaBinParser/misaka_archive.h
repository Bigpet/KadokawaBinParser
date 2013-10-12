#pragma once

namespace MisakaTool{


	struct MisakaArchive{
		const int file_table_offset = 22;
		const int file_table_entry_width = 4;
		const int block_size = 2048;


		//reads the full file into a vector<char>
		static std::vector<char> readFullFile(std::string name);

		//returns an index of files. The index contains the sector numbers at which the files start
		static std::vector<short> getFiles(char *buffer);


		//decode the custom RLE CONTAINS ERRORS ATM
		static std::vector<char> decodeRLE(std::vector<char> buffer);

		//decode the custom RLE, one to one translation of the MIPS code
		static std::vector<char> decodeRLE2(std::vector<char> &buff);

		//extracts all files into the CWD 
		static void extractAllFiles(std::vector<short> &index, std::vector<char> &buffer, bool uncompress_images = true);

		//copy from source[startcpy] #amt elements into target[ins_pos]
		template <typename T>static void copy_data(std::vector<T> &target, std::vector<T> &source, int ins_pos, int startcpy, int amt){
			auto start = source.cbegin() + startcpy;
			auto end = source.cbegin() + startcpy + amt;
			target.insert(target.begin() + ins_pos, start, end);
		}
	};
};