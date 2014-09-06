#include "stdafx.h"

#include "half.h"

//takes a shtxps file and writes it into an uncompressed PNM file
void MisakaTool::writePNM(std::vector<char> buffer, std::string filename){
	std::ofstream outtest(filename, std::ofstream::out | std::ofstream::binary);

	short colors = reinterpret_cast<short &>(buffer[6]);
	short width = reinterpret_cast<short &>(buffer[10]);
	short height = reinterpret_cast<short &>(buffer[12]);
	short offset = 20 + 4 * colors;

	outtest.write("P6 ", 3);
	std::stringstream widhig;
	widhig << width << " " << height << " ";
	outtest.write(&widhig.str()[0], widhig.str().size());
	outtest.write("255 ", 4);


	for (int count = 0; count < width*height; count++){
		short color = reinterpret_cast<unsigned char &>(buffer[offset + count]);
		outtest.write(&(buffer[20 + color * 4]), 3);
	}
	outtest.flush();
	outtest.close();
}

//finds and prints out potential positions of normalized coordinate triplets
void MisakaTool::findNormals(std::vector<char> &buffer){
	const float epsilonf = 0.01f;
	float onef = 1.0f;

	uint16_t epsilon = half_from_float(reinterpret_cast<const uint32_t &>(epsilonf));
	uint16_t one = half_from_float(reinterpret_cast<uint32_t &>(onef));

	std::cout << "starting search for half-float triplets" << std::endl;

	int end = buffer.size() / 2;

	for (int j = 0; j <= 1; j++){
		uint16_t *buff = reinterpret_cast<uint16_t *>(&buffer[j]);
		uint16_t prev2 = 0;
		uint16_t prev = 0;
		uint16_t curr = 0;
		for (int i = 0; i < end; i++){
			prev2 = prev;
			prev = curr;
			curr = *(buff++);

			uint16_t norm = half_add(half_mul(prev2, prev2), half_mul(prev, prev));
			norm = half_add(norm, half_mul(curr, curr));

			uint16_t dist = half_sub(norm, one);
			uint32_t distf = half_to_float(dist);
			if (std::abs(reinterpret_cast<float &>(distf)) < epsilonf){
				std::cout << "possible candidate: " << i * 2 << " hex:" << std::hex << i * 2 << std::endl;
			}
		}

		std::cout << "shifting by one byte" << std::endl;
	}

	std::cout << "starting search for float triplets" << std::endl;
	double prev2d = 0.0;
	double prevd = 0.0;
	double currd = 0.0;

	for (int j = 0; j <= 3; j++){
		auto buff2 = reinterpret_cast<float *>(&buffer[j]);
		end = buffer.size() / 4;
		for (int i = 0; i < end; i++){
			prev2d = prevd;
			prevd = currd;
			currd = *(buff2++);

			double norm = prev2d*prev2d + prevd*prevd;
			norm = norm + currd*currd;

			double dist = norm - 1.0;
			if (std::abs(dist) < epsilonf){
				std::cout << "possible candidate: " << i * 4 << " hex:" << std::hex << i * 4 << std::endl;
			}
		}

		std::cout << "shift by one" << std::endl;
	}


	std::cout << "starting search for double triplets" << std::endl;

	for (int j = 0; j <= 7; j++){

		double *buff3 = reinterpret_cast<double *>(&buffer[j]);
		end = buffer.size() / 8;

		for (int i = 0; i < end; i++){
			prev2d = prevd;
			prevd = currd;
			currd = *(buff3++);

			double norm = prev2d*prev2d + prevd*prevd;
			norm = norm + currd*currd;

			double dist = norm - 1.0;
			if (std::abs(dist) < epsilonf){
				std::cout << "possible candidate: " << i * 8 << " hex:" << std::hex << i * 8 << std::endl;
			}
		}

		std::cout << "shift by one" << std::endl;
	}


}