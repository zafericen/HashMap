#ifndef HASHMAP_H
#define HASHMAP_H

#include <utility>
#include <memory>
#include <cstdint>
#include <iostream>

#include "LinkedMap.h"
#include "Algorithm.h"

namespace ByteC
{

	inline constexpr double MAX_LOAD{1};

	template<
		typename Key,
		typename Value,
		typename Hash = Hash<Key>>
	class HashMap
	{
	private:
		template<typename Key, typename Value>
		struct Bucket
		{
			LinkedMap<Key, Value> m_map;
		};

		using BucketArray = Bucket<Key,Value>*;
		
		Hash m_hasher;
		size_t m_tableSize{ 4 };
		size_t m_size{};
		BucketArray m_buckets;

	public:
		HashMap()
			:m_buckets{new Bucket<Key,Value>[m_tableSize]}
		{
		}

		~HashMap()
		{
			delete[] m_buckets;
		}

		void insert(const Key& key, const Value& value)
		{
			insert(Key{ key }, Value{ value });
		}

		void insert(Key&& key, Value&& value)
		{
			size_t hashValue{ m_hasher(key) % m_tableSize };

			m_buckets[hashValue].m_map.insert(std::move(key), std::move(value));

			++m_size;

			checkLoad();
		}

		void erase(const Key& key)
		{
			size_t hashValue{ m_hasher(key) % m_tableSize };

			m_buckets[hashValue].m_map.erase(key);

			--m_size;
		}

		Value& at(const Key& key)
		{
			size_t hashValue{ m_hasher(key) % m_tableSize };

			m_buckets[hashValue].m_map.at(key);
		}

		const Value& at(const Key& key) const
		{
			size_t hashValue{ m_hasher(key) % m_tableSize };

			m_buckets[hashValue].m_map.at(key);
		}

		void find(const Key& index)
		{
		}

		bool contains(const Key& key) const
		{
			size_t hashValue{ m_hasher(key) % m_tableSize };

			return *m_buckets[hashValue].m_map.find(key) == nullptr;
		}

		void begin()
		{
		}

		void end()
		{
		}

		size_t size() const
		{
			return m_size;
		}

		void rehash(size_t newTableSize)
		{
			BucketArray oldTable{ m_buckets };
			m_buckets = new Bucket<Key,Value>[newTableSize];

			size_t oldTableSize{ m_tableSize };
			m_tableSize = newTableSize;

			m_size = 0;
			
			for (size_t i{}; i < oldTableSize; ++i)
			{
				for (auto& pair : oldTable[i].m_map)
				{
					insert(std::move(pair.first), std::move(pair.second));
				}
			}

			delete[] oldTable;
		}

		void printt()
		{
			for (size_t i{}; i < m_tableSize; ++i)
			{
				for (auto& pair : m_buckets[i].m_map)
				{
					std::cout << pair.first << " ";
				}
				std::cout << std::endl;
			}
			std::cout << "------------" << std::endl;
		}

	private:
		void checkLoad()
		{
			if (m_size > MAX_LOAD * static_cast<double>(m_tableSize))
			{
				rehash(m_tableSize * 2);
			}
		}

	};

	
}

#endif