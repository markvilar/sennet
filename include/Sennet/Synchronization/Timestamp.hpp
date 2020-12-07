#pragma once

#include <chrono>

namespace Sennet {

class Timestamp
{
public:
	Timestamp() = default;
	~Timestamp() = default;

	void SetMilliseconds(const uint64_t ms) { m_Milliseconds = ms; }
	uint64_t GetMilliseconds() const { return m_Milliseconds; }

	virtual void Grab() 
	{
		auto now = std::chrono::steady_clock::now();
		auto nowMs = std::chrono::time_point_cast
			<std::chrono::milliseconds>(now);
		auto epoch = nowMs.time_since_epoch();
		m_Milliseconds = std::chrono::duration_cast
			<std::chrono::milliseconds>(epoch).count();
	}

public:
	uint64_t m_Milliseconds = 0; // Time since epoch in milliseconds.
};

}
