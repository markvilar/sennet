#pragma once

namespace Sennet
{

template<typename K, typename T>
class TSMap
{
	// Thread-safe implementation of unordered map. Does not support
	// multiple external writes, which might be implemented in the future by
	// means of shared mutexes.
public:
	TSMap() = default;
	virtual ~TSMap()
	{
		std::scoped_lock lock(m_Mutex);
		clear();
	}

	TSMap(const TSMap&) = delete;
	
	bool empty() const
	{
		std::scoped_lock lock(m_Mutex);
		return m_Map.empty();
	}

	uint64_t size() const
	{
		std::scoped_lock lock(m_Mutex);
		return m_Map.size();
	}

	uint64_t max_size() const
	{
		std::scoped_lock lock(m_Mutex);
		return m_Map.max_size();
	}

	typename std::unordered_map<K, T>::iterator begin()
	{
		std::scoped_lock lock(m_Mutex);
		return m_Map.begin();
	}

	typename std::unordered_map<K, T>::iterator end()
	{
		std::scoped_lock lock(m_Mutex);
		return m_Map.end();
	}

	typename std::unordered_map<K, T>::const_iterator begin() const
	{
		std::scoped_lock lock(m_Mutex);
		return m_Map.cbegin();
	}

	typename std::unordered_map<K, T>::const_iterator end() const
	{
		std::scoped_lock lock(m_Mutex);
		return m_Map.cend();
	}

	T& operator[](const K& k)
	{
		std::scoped_lock lock(m_Mutex);
		return m_Map[k];
	}

	T& at(const K& k)
	{
		std::scoped_lock lock(m_Mutex);
		return m_Map.at(k);
	}

	typename std::unordered_map<K, T>::iterator find(const K& k)
	{
		std::scoped_lock lock(m_Mutex);
		return m_Map.find(k);
	}

	typename std::unordered_map<K, T>::const_iterator find(const K& k) const
	{
		std::scoped_lock lock(m_Mutex);
		return m_Map.find(k);
	}

	uint64_t count(const K& k) const
	{
		std::scoped_lock lock(m_Mutex);
		return m_Map.count();
	}

	std::pair<typename std::unordered_map<K, T>::iterator, bool> emplace()
	{
		std::scoped_lock lock(m_Mutex);
		return m_Map.emplace();
	}

	std::pair<typename std::unordered_map<K, T>::iterator, bool> 
		insert(const K& k)
	{
		std::scoped_lock lock(m_Mutex);
		return m_Map.insert(k);
	}

	typename std::unordered_map<K, T>::iterator 
		erase(typename std::unordered_map<K, T>::const_iterator position)
	{
		std::scoped_lock lock(m_Mutex);
		return m_Map.erase(position);
	}

	uint64_t erase(const K& k)
	{
		std::scoped_lock lock(m_Mutex);
		return m_Map.erase(k);
	}

	typename std::unordered_map<K, T>::iterator 
		erase(typename std::unordered_map<K, T>::const_iterator first,
		typename std::unordered_map<K, T>::const_iterator last)
	{
		std::scoped_lock lock(m_Mutex);
		return m_Map.erase(first, last);
	}
		
	void clear()
	{
		std::scoped_lock lock(m_Mutex);
		m_Map.clear();
	}

	void swap(typename std::unordered_map<K, T>& other)
	{
		std::scoped_lock lock(m_Mutex);
		m_Map.swap(other);
	}

private:
	std::unordered_map<K, T> m_Map;
	std::mutex m_Mutex;
};

}
