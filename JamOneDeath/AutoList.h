#pragma once

#include <vector>
#include <algorithm>

template<typename T>
class AutoList
{
public:
	AutoList()
	{
		m_references.push_back(static_cast<T*>(this));
	}
	virtual ~AutoList()
	{
		auto p = static_cast<T*>(this);
		auto iter = std::find(std::begin(m_references), std::end(m_references), p);
		if (iter != std::end(m_references)) m_references.erase(iter);
	}
	static int size()
	{
		return m_references.size();
	}
	static T* get(int index)
	{
		return m_references[index];
	}
private:
	static std::vector<T*> m_references;
};

template<typename T>
std::vector<T*> AutoList<T>::m_references;