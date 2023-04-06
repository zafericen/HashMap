#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <type_traits>
#include <utility>

namespace ByteC
{

	template<typename Key, typename Value>
	class LinkedList
	{
	private:
		template<typename Key, typename Value>
		struct Node
		{
			std::pair<Key, Value> m_pair;
			Node* m_next;
		};

		using NodePtr = Node<Key, Value>*;

		template<typename Key, typename Value>
		class Iterator
		{
		private:
			NodePtr m_ptr;

		public:
			Iterator(NodePtr* ptr)
				:m_ptr{ptr}
			{
			}

			std::pair<const Key, Value>& operator*()
			{
				return m_iterator->m_pair;
			}

			Iterator& operator++()
			{
				++m_ptr;
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
		LinkedList() = default;

		LinkedList(const LinkedList& linkedList) = delete;

		LinkedList(LinkedList&& linkedList):
			m_head{linkedList.m_head}
		{
			linkedList.m_head = nullptr;
		}

		~LinkedList()
		{
			clear();
		}

		void insert(Key&& key, Value&& value)
		{
			NodePtr newHead{ createNode(std::move(key), std::move(value)) };
			newHead->m_next = m_head;
			m_head = newHead;
		}

		void remove(const Key& key)
		{
			if (m_head->m_pair.first == key)
			{
				NodePtr newHead{ m_head->next };
				destroyNode(m_head);
				m_head = newHead;
			}
			else
			{
				NodePtr iterator{ m_head };
				while (iterator->m_next)
				{
					if (iterator->next->m_pair.first == key)
					{
						NodePtr removal{ iterator->m_next };
						iterator->m_next = removal->m_next;
						destroyNode(removal);
						return;
					}
				}
			}
		}

		Value& get(const Key& key)
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

			//assert here;
		}

		const Value& get(const Key& key) const
		{
			return get(key);
		}

		bool empty() const
		{
			return static_cast<bool>(m_head);
		}

		Iterator begin()
		{
			return Iterator<Key,Value>{ m_head };
		}

		Iterator end()
		{
			return Iterator<Key, Value>{ nullptr };
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

		void clear()
		{
			if (!empty())
			{
				NodePtr iterator{ m_head };
				while (iterator->m_next)
				{
					NodePtr next{ m_head->m_next };
					delete iterator;
					iterator = next;
				}
			}
		}
	};
}

#endif