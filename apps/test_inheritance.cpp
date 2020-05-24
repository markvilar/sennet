#include <iostream>
#include <memory>

// Forward declaration.
class Base_class;
class Derived_class;

class Base_action
{
private:

public:
	virtual ~Base_action() {};
	virtual void interact(Base_class& c) = 0;
	virtual void interact(Derived_class& c) = 0;
};

class Derived_action : public Base_action
{
private:

public:
	Derived_action() {};

	~Derived_action() {};

	void interact(Base_class& c)
	{
		std::cout << "Executing derived action with base class.\n";
	}
	void interact(Derived_class& c)
	{
		std::cout << "Executing derived action with derived class.\n";
	}
};

class Base_class
{
protected:

public:
	Base_class() {};

	~Base_class() {};

	virtual void execute_action(Base_action& a)
	{
		a.interact(*this);
	}
};

class Derived_class : public Base_class
{
private:
	
public:
	Derived_class() : Base_class() {};

	~Derived_class() {};
		
	void execute_action(Base_action& a)
	{
		a.interact(*this);
	}
};

int main()
{
	Derived_action action;
	Base_class base;
	Derived_class derived;

	base.execute_action(action);
	derived.execute_action(action);
	return 0;
}
