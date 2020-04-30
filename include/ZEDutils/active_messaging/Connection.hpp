#include <atomic>
#include <thread>

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/bind.hpp>
#include <boost/cstdint.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/ref.hpp>

namespace zed { namespace am {

class Runtime
{
};

class Connection
{
};

class Action 
{
	virtual ~action() {}
	
	virtual void operator()(Runtime&) = 0;

	virtual action* clone() const = 0;

	template<typename Archive>
	void serialize(Archive& ar, const unsigned int) {}
};

}};
