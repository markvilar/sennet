#pragma once

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

namespace sennet
{

class message
{
private:

public:
	message() = default;
	message(const message& other) = default;
	virtual ~message() = default;
	
	virtual message* clone() const
	{
		return new message();
	}

	virtual std::string to_string() const {};	

	template<typename Archive>
	void serialize(Archive& ar, const unsigned int version) {};

private:
	// TODO: Add sender address and port?
};

}
