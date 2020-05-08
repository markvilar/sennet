#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/zlib.hpp>

#include <zedutils/io.hpp>
#include <zedutils/serialization.hpp>

// Example illustrating one way of saving and loading data using a boost
// archive.

void save()
{
	namespace io = boost::iostreams;

	auto m = sl::Mat(100, 150, sl::MAT_TYPE::U8_C4);
	m.setTo(sl::uchar4(1, 2, 3, 4));
	m.setValue(50, 50, sl::uchar4(5, 5, 5, 5));

	std::ofstream ofs("matrix.bin", std::ios::out | std::ios::binary);

	// Use scope to ensure archive goes out of scope before stream.
	{
		io::filtering_streambuf<io::output> out;
		//out.push(io::zlib_compressor(io::zlib::best_speed));
		out.push(ofs);
		
		boost::archive::binary_oarchive oa(out);
		
		// Send matrix to archive.
		oa << m;
		std::cout << "Saved matrix to archive!\n" << m << "\n";

		// Get values from matrix
		sl::uchar4 vs;
		m.getValue(50, 50, &vs);
		std::cout << vs << "\n";
		m.getValue(0, 0, &vs);
		std::cout << vs << "\n";
	}
	
	ofs.close();
}

void load()
{
	namespace io = boost::iostreams;

	sl::Mat m;

	std::ifstream ifs("matrix.bin", std::ios::out | std::ios::binary);

	// Use scope to ensrue archive goes out of scope before stream.
	{
		io::filtering_streambuf<io::input> in;
		//in.push(io::zlib_decompressor());
		in.push(ifs);

		boost::archive::binary_iarchive ia(in);

		// Load matrix from archive.
		ia >> m;
		std::cout << "Loaded matrix from archive!\n" << m << "\n";
		sl::uchar4 vs;

		// Get values from matrix
		m.getValue(50, 50, &vs);
		std::cout << vs << "\n";
		m.getValue(0, 0, &vs);
		std::cout << vs << "\n";
	}
	
	ifs.close();
}

int main(int argc, char* argv[])
{
	save();
	load();
	return 0;
};
