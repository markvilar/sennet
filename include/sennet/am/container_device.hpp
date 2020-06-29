#pragma once

#include <algorithm>				// copy, min
#include <iosfwd>				// streamsize

#include <boost/assert.hpp>			// BOOST_ASSERT
#include <boost/iostreams/categories.hpp>	// source_tag
#include <boost/iostreams/positioning.hpp>	// stream_offset

namespace am {

// This is a Boost.IoStreams SeekableDevice that can be used to create an
// (io)stream on top of a random access container (i.e. vector<>).
//
// A device provides access to one or two character sequences. It may provide
// access to an input sequence for reading and a output sequence for writing or
// both. 
//
// Boost documentation references:
// https://www.boost.org/doc/libs/1_72_0/libs/iostreams/doc/concepts/
// seekable_device.html
template<typename Container>
class container_device
{
private:
	// 
	typedef typename Container::size_type size_type;

	//
	typedef typename Container::difference_type difference_type;

	Container& m_container;

	// 
	boost::iostreams::stream_offset m_pos;

public:
	// The char type of the underlying container.
	typedef typename Container::value_type char_type;

	// Category tag identifying the device as a seekable device.
	typedef boost::iostreams::seekable_device_tag category;
	
	container_device(Container& c)
		: m_container(c),
		m_pos(0)
	{}

	// Read up to n characters from the underlying data source into the
	// buffer s, returning the number of characters read. Return -1 to
	// indicate EOF.
	std::streamsize read(char_type* s, std::streamsize n)
	{
		std::streamsize amt = 
			static_cast<std::streamsize>(m_container.size()) - m_pos;
		std::streamsize result = (std::min)(n, amt);
		BOOST_ASSERT(result > 0);
		if (result != 0)
		{
			std::copy(m_container.begin() + m_pos,
				m_container.begin() + m_pos + result,
				s);
			m_pos += result;
			return result;
		}
		else
		{
			return -1; // EOF
		}
	}

	// Write up to n characters to the underlying data sink into the 
	// buffer s, return the number of characters written.
	std::streamsize write(const char_type* s, std::streamsize n)
	{
		std::streamsize result = 0;
		if (static_cast<size_type>(m_pos) != m_container.size())
		{
			std::streamsize amt =
				static_cast<std::streamsize>(m_container.size())
				- m_pos;
			result = (std::min)(n, amt);
			std::copy(s, s + result, m_container.begin() + m_pos);
			m_pos += result;
		}

		if (result < n)
		{
			BOOST_ASSERT(
				n < (std::numeric_limits<difference_type>::max)()
				);
			m_container.insert(
				m_container.end(), 
				s, 
				s + static_cast<difference_type>(n));
			m_pos = static_cast<boost::iostreams::stream_offset>
				(m_container.size());
		}
		return n;
	}

	// Seek to position off and return the new stream position. The argument
	// 'way' indicates how off is interpreted:
	// 	- std::ios_base::beg - indicates an offset from the sequence
	// 		beginning.
	//	- std::ios_base::cur - indicates an offset from the current
	//		character position.
	// 	- std::ios_base::end - indicates an offset from the sequence
	// 		end.
	boost::iostreams::stream_offset seek(
		boost::iostreams::stream_offset off, std::ios_base::seekdir way)
	{
		// Determine new value of m_pos.
		boost::iostreams::stream_offset next(0);
		if (way == std::ios_base::beg)
		{
			next = off;
		}
		else if (way == std::ios_base::cur)
		{
			next = m_pos + off;
		}
		else if (way == std::ios_base::end)
		{
			next = static_cast<boost::iostreams::stream_offset>(
					m_container.size()) + off - 1u;
		}
		else
		{
			BOOST_ASSERT(false);
		}

		// Check for errors.
		BOOST_ASSERT(m_container.size() < static_cast<size_type>(
			(std::numeric_limits<boost::iostreams::stream_offset>::max
			)()));

		if (next < (static_cast<boost::iostreams::stream_offset>(0))
			|| next >= (static_cast<boost::iostreams::stream_offset>
			(m_container.size())))
			throw std::ios_base::failure("bad seek offset");

		m_pos = next;
		return m_pos;
	}

	Container& container() { return m_container; }

}; // class container_device

}; // namespace am
