#pragma once

namespace sennet
{

class message
{
private:

public:
	virtual ~message() = default;
	
	virtual message* clone() const = 0;

	template<typename Archive>
	void serialize(Archive& ar, const unsigned int version) {};
};

}
