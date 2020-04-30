#include <sl/Camera.hpp>

#include <boost/serialization/split_free.hpp>
#include <boost/serialization/vector.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::sl::Mat)

namespace boost { namespace serialization {

	// Serialization support for sl::Mat
	template<class Archive, typename N>
	void save(Archive& ar, const ::sl::Mat& m, const unsigned int version)
	{
		(void)version;
		size_t width = m.getWidth();
		size_t height = m.getHeight();
		size_t elem_size = m.getStep();
		auto type = m.getDataType();

		ar & width;
		ar & height;
		ar & elem_size;
		ar & type;

		const size_t data_size = width * height * elem_size;
		ar & boost::serialization::make_array(m.getPtr<N>(), data_size);
	}

	// Serialization support for sl::Mat
	template<class Archive, typename N>
	void load(Archive& ar, ::sl::Mat& m, const unsigned int version)
	{
		(void)version;
		size_t width, height, elem_size;
		sl::MAT_TYPE type;

		ar & width;
		ar & height;
		ar & elem_size;
		ar & type;
		
		m.alloc(width, height, type);

		const size_t data_size = width * height * elem_size;
		ar & boost::serialization::make_array(m.getPtr<N>(), data_size);
	}

}};
