#ifndef ACTION_HPP
#define ACTION_HPP

namespace zed { namespace am {

class runtime; // Forward declaration.

// Virtual base class for actions.
class action 
{
private:

public:
	virtual ~action() {}
	
	virtual void operator()(runtime&) = 0;

	virtual action* clone() const = 0;

	// Member function needed in order to use Boost.Serialization.
	template<typename Archive>
	void serialize(Archive& ar, const unsigned int version) {}
}; // class action

} // namespace am
}; // namespace zed

#endif // ACTION_HPP
