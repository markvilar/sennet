#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <ZEDutils/active_messaging/Runtime.hpp>

namespace zed { namespace am {

class Action 
{
private:
	virtual ~Action() {}

	// Needed in order to use Boost.Serialization with Action class
	template<typename Archive>
	void serialize(Archive& ar, const unsigned int) {}

public:
		
	virtual void operator()(Runtime&) = 0;

	virtual Action* clone() const = 0;

};

}}; // Namespace zed::am
