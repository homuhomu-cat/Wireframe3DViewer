#pragma once
# include <Siv3D.hpp>

namespace TDLib
{
	template <typename T, template <typename, typename> class Container = Array>
	class Graph
	{
	private:
		Container<T, std::allocator<T>> m_node;
		Container<std::pair<T*, T*>, std::allocator<std::pair<T*, T*>>> m_edge;
	public:
		Graph() {}
	public:
		auto node_begin()
		{
			return m_node.begin();
		}
		auto node_end()
		{
			return m_node.end();
		}
		auto edge_begin()
		{
			return m_edge.begin();
		}
		auto edge_end()
		{
			return m_edge.end();
		}
	public:
		T* node_at(int32 n)
		{
			return &m_node.at(n);
		}
		T* find(T t)
		{
			for (auto itr = m_node.begin(); itr != m_node.end(); ++itr)
				if (*itr == t)
					return &*itr;
		}
		int32 find(T* t)
		{
			for (auto itr = m_node.begin(); itr != m_node.end(); ++itr)
				if (*itr == *t)
					return (int32)(itr - m_node.begin());
		}
	public:
		T* front()
		{
			return &m_node.front();
		}
		T* add(T t)
		{
			m_node.push_back(t);
			return &m_node.back();
		}
		T* push_back(T t)
		{
			return add(t);
		}
		void connect(T* f, T* s)
		{
			m_edge.push_back(std::pair<T*, T*>(f, s));
		}
	public:
		size_t node_size() 
		{
			return m_node.size();
		}
		size_t edge_size() 
		{
			return m_edge.size();
		}
	};
}
