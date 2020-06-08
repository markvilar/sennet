#include <iostream>
#include <tuple>

#include <boost/asio.hpp>

#include <glad/glad.h>

#include <zedutils/am/actions.hpp>
#include <zedutils/am/core.hpp>
#include <zedutils/log.hpp>

int main()
{
	am::log::init("Logger 1");
	AM_WARN("Initialized log 1!");
	int a = 5;
	AM_INFO("Hello! Var={0}", a);
	return 0;
}
