#ifndef HASHMAP_H
#define HASHMAP_H

#include <utility>
#include <memory>
#include <cstdint>
#include <vector>
#include <string>


namespace ByteC
{
	inline constexpr size_t MAX_PROB_ITERATION{ 100 };

	template<typename T>
	struct Hash
	{
		
		constexpr size_t operator()(const T& arg) const
		{
			size_t hash{ static_cast<size_t>(reinterpret_cast<std::uintptr_t>(&arg)) };
			hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
			hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
			hash = ((hash >> 16) ^ hash);
			return hash;

		}
	};

	template<>
	struct Hash<uint32_t>
	{
		constexpr uint32_t operator()(uint32_t arg) const
		{
			return arg;
		}
	};

	template<>
	struct Hash<size_t>
	{
		constexpr size_t operator()(size_t arg) const
		{
			return arg;
		}
	};

	template<>
	struct Hash<std::string>
	{
		constexpr uint32_t operator()(const std::string& s) const
		{
			return operator()(s.c_str());
		}

		constexpr uint32_t operator()(const char* s) const
		{
			uint32_t hash{};

			for (uint32_t index{}; s[index]; ++index)
			{
				hash += (index + 1) * s[index];
			}

			return hash;
		}
	};

	template<typename Key, typename Value>
	struct Bucket
	{
		using Pair = std::pair<Key,Value>;
		Pair m_Pair;

	
	};

	struct Probe
	{
		size_t operator()(size_t index, size_t degree) const
		{
			return index + degree * degree;
		}
	};

	template<
		typename Key,
		typename Value,
		typename Hash = Hash<Key>,
		typename Allocator = std::allocator<Bucket<Key, Value>>>
	class HashMap
	{
	private:
		using Pair = std::pair<Key,Value>;
		using BucketArray = Bucket<Key,Value>*;
		
		enum class BucketStatus : uint8_t
		{
			EMPTY,
			DELETED,
			FULL
		};
		
		using StatusVector = std::vector<BucketStatus>;

		
		Allocator m_Allocator;
		Probe m_Probe;
		Hash m_Hasher;
		BucketArray m_Buckets;
		StatusVector m_Status;
		size_t m_Size;
		size_t m_TableSize;

	public:
		//alocate table at size 8
		HashMap(size_t tableSize = 8)
			:m_TableSize{ tableSize } 
		{

		}
		
		//call clear
		virtual ~HashMap() = default;

		void insert(const Key& key, const Value& value)
		{
			insert(Key{ key }, Value{ value });
		}

		//add key-value pairs to apopriate bucket
		void insert(Key&& key, Value&& value)
		{
			size_t hashValue{ m_Hasher(key) % m_TableSize };
			size_t probeValue{ hashValue % m_TableSize };
			
			//exchange while with for and rehash when for finishes 
			for(size_t i =1;i <=MAX_PROB_ITERATION ;i++){
				if (m_Status[probeValue] == BucketStatus::EMPTY)
				{
					m_Status[probeValue] = BucketStatus::FULL;
					construct(probeValue, std::move(key), std::move(value));
					break;
				}
				probeValue = m_Probe(hashValue,i)%m_TableSize;
			}

			rehash(m_TableSize*2);
			
			insert(std::move(key), std::move(value));
			
		}

		//delete key-value pair from table(call destroy) and set status to deleted
		void erase(const Key& key)
		{
		}

		//returns iterator that points to the key-value pair if it exist if not return end
		void find(const Key& key)
		{
		}

		
		bool contains(const Key& key) const
		{
		}


		void begin()
		{
		}

		void end()
		{
		}

		//create new table and rehash all elements to the new table and delete the old table
		void rehash(size_t newTableSize)
		{
			BucketArray tempArray{ m_Buckets };
			
			m_Buckets = std::allocator_traits<Allocator>::allocate(m_Allocator, m_TableSize);
			StatusVector tempStatus = std::move(m_Status);
			
			for (size_t i =0;i< m_TableSize;i++)
			{
				if (tempStatus[i] == BucketStatus::FULL)
				{
					insert(std::move(tempArray[i].pair.first), std::move(tempArray[i].pair.second));
					std::allocator_traits<Allocator>::destroy(m_Allocator, tempArray[i]);
				}
			}
			m_TableSize = newTableSize;
			//Carry all elemets with rehashing.
			std::allocator_traits<Allocator>::deallocate(m_Allocator, tempArray, m_TableSize);
		}

	private:
		//craetes bucket at index and stores in it 
		void construct(size_t index, Key&& key, Value&& value)
		{
			//crate bucket and pass to construct
			std::allocator_traits<Allocator>::construct(m_Allocator, m_Buckets[index], Bucket<Key, Value>{ Pair{ std::move(key),std::move(value) } });
		}

		//deletes bucket at index
		void destroy(size_t index)
		{
			std::allocator_traits<Allocator>::destroy(m_Allocator, m_Buckets[index]);
		}
		
		//checks load and rehashes it if needed
		void checkLoad()
		{
		}

		//deletes buckets and creats new with default size
		void clear()
		{
		}

	};


}

#endif