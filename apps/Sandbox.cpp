#include <functional>
#include <iostream>

void print()
{
	std::cout << "print!\n";
}

void print_number(int n)
{
	std::cout << n << "\n";
}

int main(int argc, char* argv[])
{
	// Create functor without any arguments, where we bind in a function
	// with arguments.
	int number = 32;
	auto f = std::function<void()>(std::bind(&print_number, number));

	// This is how you call it!
	f();
}
