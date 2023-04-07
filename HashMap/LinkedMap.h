#ifndef LINKEDMAP_H
#define LINKEDMAP_H

#include <type_traits>
#include <utility>
#include <cstdlib>

namespace ByteC
{

	template<typename Key, typename Value>
	class LinkedMap
	{
	private:
		template<typename Key, typename Value>
		struct Node
		{
			std::pair<const Key, Value> m_pair;
			Node* m_next;
		};

		using NodePtr = Node<Key, Value>*;

		template<typename Key, typename Value>
		class Iterator
		{
		private:
			NodePtr m_ptr;

		public:
			Iterator(NodePtr ptr)
				:m_ptr{ptr}
			{
			}

			std::pair<const Key, Value>& operator*()
			{
				return m_ptr->m_pair;
			}

			Iterator& operator++()
			{
				m_ptr = m_ptr->m_next;
				return *this;
			}

			bool operator==(const Iterator& iterator)
			{
				return m_ptr == iterator.m_ptr;
			}

			bool operator!=(const Iterator& iterator)
			{
				return m_ptr != iterator.m_ptr;
			}
		};

		NodePtr m_head{};

	public:
		LinkedMap() = default;

		LinkedMap(const LinkedMap& linkedList) = delete;

		LinkedMap(LinkedMap&& linkedList):
			m_head{linkedList.m_head}
		{
			linkedList.m_head = nullptr;
		}

		~LinkedMap()
		{
			clear();
		}

		void insert(const Key& key, const Value& value)
		{
			insert(Key{ key }, Value{ value });
		}

		void insert(Key&& key, Value&& value)
		{
			NodePtr newHead{ createNode(std::move(key), std::move(value)) };
			newHead->m_next = m_head;
			m_head = newHead;
		}

		void erase(const Key& key)
		{
			if (m_head->m_pair.first == key)
			{
				NodePtr newHead{ m_head->m_next };
				destroyNode(m_head);
				m_head = newHead;
			}
			else
			{
				NodePtr iterator{ m_head };
				while (iterator->m_next)
				{
					if (iterator->m_next->m_pair.first == key)
					{
						NodePtr removal{ iterator->m_next };
						iterator->m_next = removal->m_next;
						destroyNode(removal);
						return;
					}
				}
			}
		}

		Value& at(const Key& key)
		{
			NodePtr iterator{ m_head };
			while (iterator->m_next)
			{
				if (iterator->m_pair.first == key)
				{
					return iterator->m_pair.second;
				}
				iterator = iterator->m_next;
			}
		}

		const Value& at(const Key& key) const
		{
			return get(key);
		}

		Iterator<Key, Value> find(const Key& key)
		{
			NodePtr iterator{ m_head };
			while (iterator->m_next)
			{
				if (iterator->m_pair.first == key)
				{
					return Iterator<Key,Value>{iterator};
				}
				iterator = iterator->m_next;
			}
			return Iterator<Key, Value>{nullptr};
		}

		bool empty() const
		{
			return !static_cast<bool>(m_head);
		}

		Iterator<Key,Value> begin()
		{
			return Iterator<Key,Value>{ m_head };
		}

		Iterator<Key,Value> end()
		{
			return Iterator<Key, Value>{ nullptr };
		}

		void clear()
		{
			if (!empty())
			{
				NodePtr iterator{ m_head };
				while (iterator->m_next)
				{
					NodePtr next{ iterator->m_next };
					delete iterator;
					iterator = next;
				}
			}
			m_head = nullptr;
		}

	private:
		NodePtr createNode(Key&& key, Value&& value)
		{
			return new Node<Key, Value>{ std::pair<const Key,Value>{std::move(key),std::move(value)},nullptr };
		}

		void destroyNode(NodePtr nodePtr)
		{
			delete nodePtr;
		}
	};
}

#endif