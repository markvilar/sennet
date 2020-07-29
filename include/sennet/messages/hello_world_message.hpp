#pragma once
#include <sennet/messages/message.hpp>

namespace sennet
{

class hello_world_message : public message
{
private:

public:
	hello_world_message() = default;

	virtual std::string to_string() const override
	{
		return "hello_world";
	}
	
	virtual message* clone() const override
	{
		return new hello_world_message(*this);
	}

	template<typename Archive>
	void serialize(Archive& ar, const unsigned int version) 
	{
		ar & boost::serialization::base_object<message>(*this);
	}

private:
	
};

}


