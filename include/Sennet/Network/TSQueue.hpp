#pragma once

namespace Sennet
{

template <typename T>
class TSQueue
{
public:
	TSQueue() = default;
	virtual ~TSQueue()
	{
		std::scoped_lock lock(m_Mutex);
		clear();
	}

	TSQueue(const TSQueue<T>&) = delete;

	const T& front()
	{
		std::scoped_lock lock(m_Mutex);
		return m_Deque.front();
	}

	const T& back()
	{
		std::scoped_lock lock(m_Mutex);
		return m_Deque.back();
	}

	void push_front(const T& t)
	{
		std::scoped_lock scopedLock(m_Mutex);
		m_Deque.emplace_front(std::move(t));
		
		std::unique_lock uniqueLock(m_MutexBlocking);
		m_BlockingCondition.notify_one();
	}

	void push_back(const T& t)
	{
		std::scoped_lock scopedLock(m_Mutex);
		m_Deque.emplace_back(std::move(t));

		std::unique_lock uniqueLock(m_MutexBlocking);
		m_BlockingCondition.notify_one();
	}

	bool empty()
	{
		std::scoped_lock scopedLock(m_Mutex);
		return m_Deque.empty();
	}

	uint64_t count()
	{
		std::scoped_lock scopedLock(m_Mutex);
		return m_Deque.count();
	}

	void clear()
	{
		std::scoped_lock scopedLock(m_Mutex);
		m_Deque.clear();
	}

	T pop_front()
	{
		std::scoped_lock scopedLock(m_Mutex);
		auto t = std::move(m_Deque.front());
		m_Deque.pop_front();
		return t;
	}

	T pop_back()
	{	
		std::scoped_lock scopedLock(m_Mutex);
		auto t = std::move(m_Deque.back());
		m_Deque.pop_back();
		return t;
	}

	void wait()
	{
		while (empty())
		{
			std::unique_lock<std::mutex> uniqueLock(
				m_MutexBlocking);
			m_BlockingCondition.wait(uniqueLock);
		}
	}

	typename std::deque<T>::iterator begin()
	{
		std::scoped_lock lock(m_Mutex);
		return m_Deque.begin();
	}

	typename std::deque<T>::iterator end()
	{
		std::scoped_lock lock(m_Mutex);
		return m_Deque.end();
	}

	typename std::deque<T>::const_iterator begin() const
	{
		std::scoped_lock lock(m_Mutex);
		return m_Deque.cbegin();
	}

	typename std::deque<T>::const_iterator end() const
	{
		std::scoped_lock lock(m_Mutex);
		return m_Deque.cend();
	}

protected:
	std::mutex m_Mutex;
	std::deque<T> m_Deque;

	std::mutex m_MutexBlocking;
	std::condition_variable m_BlockingCondition;
};

}
