#include <string>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include <ZEDutils/serialization.hpp>

int main(int argc, char* argv[])
{
	sl::Mat mat1, mat2;
	std::ofstream ofs("matrices.bin", std::ios::out | std::ios::binary);

	// Use scope to ensure archive goes out of scope before stream
	{
		boost::archive::binary_oarchive oa(ofs);
		oa << mat1 << mat2;
	}
	ofs.close();
	return 0;
};
