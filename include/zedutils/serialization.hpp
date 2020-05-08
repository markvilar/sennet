#include <sl/Camera.hpp>

#include <boost/serialization/split_free.hpp>
#include <boost/serialization/array.hpp>

// Allows for 'save' and 'load' templates rather than 'serialize'
// for non-intrusive serialization. SPLIT = load/save, FREE = non-intrusive
BOOST_SERIALIZATION_SPLIT_FREE(sl::Mat)

namespace boost { namespace serialization {

	// Serialization support for sl::Mat
	template<class Archive>
	void save(Archive& ar, const sl::Mat& m, const unsigned int version)
	{
		(void)version;
		size_t width = m.getWidth();
		size_t height = m.getHeight();
		size_t pixel_bytes = m.getPixelBytes();
		auto type = m.getDataType();

		ar & width;
		ar & height;
		ar & pixel_bytes;
		ar & type;

		const size_t data_size = width * height * pixel_bytes;

		ar & boost::serialization::make_array(m.getPtr<sl::uchar1>(),
			data_size);
	}

	// Serialization support for sl::Mat
	template<class Archive>
	void load(Archive& ar, sl::Mat& m, const unsigned int version)
	{
		(void)version;
		size_t width, height, pixel_bytes;
		sl::MAT_TYPE type;

		ar & width;
		ar & height;
		ar & pixel_bytes;
		ar & type;
		
		m.alloc(width, height, type);

		const size_t data_size = width * height * pixel_bytes;

		ar & boost::serialization::make_array(m.getPtr<sl::uchar1>(), 
			data_size);
	}
} // namespace serialization
}; // namespace boost


namespace zed {
	
	// Returns the data of a sl::Mat as a std::vector
	std::vector<unsigned char> mat2vec(sl::Mat& m)
	{
		auto ptr = m.getPtr<sl::uchar1>();
		size_t size = m.getWidth() * m.getHeight() 
			* m.getPixelBytes();
		auto v = std::vector<unsigned char>(ptr, ptr + size);
		return v;
	}

	sl::Mat vec2mat(size_t width, size_t height, size_t pixel_bytes,
		 sl::MAT_TYPE type, std::vector<unsigned char> data)
	{
		sl::Mat m;
		// TODO: Implement!
		return m;
	}

}; // namespace zed
