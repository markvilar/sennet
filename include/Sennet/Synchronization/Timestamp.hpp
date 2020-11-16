#pragma once

#include <chrono>

namespace Sennet {

class Timestamp
{
public:
	Timestamp(const char* name)
		: m_Name(name)
	{
		auto now = std::chrono::steady_clock::now();
		auto nowMs = std::chrono::time_point_cast
			<std::chrono::milliseconds>(now);
		auto epoch = nowMs.time_since_epoch();
		m_Milliseconds = std::chrono::duration_cast
			<std::chrono::milliseconds>(epoch).count();
	}

	const char* GetName() const { return m_Name; }
	uint64_t GetMilliseconds() const { return m_Milliseconds; }

	~Timestamp() = default;
private:
	const char* m_Name;
	uint64_t m_Milliseconds = 0; // Time since epoch in milliseconds.
};

}
