#ifndef HASHMAP_H
#define HASHMAP_H

#include <utility>
#include <memory>
#include <cstdint>
#include <vector>
#include <string>

namespace ByteC
{

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
		Key key;
		Value value;
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
		typename Hash,
		typename Allocator = std::allocator<Bucket<Key, Value>>>
	class HashMap
	{
	private:
		using BucketArray = Bucket*;
		
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
		HashMap(size_t tableSize)
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
			size_t hashValue{ m_Hasher(index) % m_TableSize };
			size_t probeValue{ hashValue };
			//exchange while with for and rehash when for finishes
			while (true)
			{
				if (status[probeValue] == BucketStatus::EMPTY)
				{

				}
				else
				{
					//get new value from probe
				}
			}
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
			BucketArray newTable{ arrays.push_back(std::allocator_traits<Allocator>::allocate(m_Allocator, m_TableSize)) };
			
			//Carry all elemets with rehashing.

			clear();

			std::allocator_traits<Allocator>::deallocate(m_Allocator, removal, arraySize);

			buckets = newTable;
		}

	private:
		//craetes bucket at index and stores in it 
		void construct(size_t index, Value&& value)
		{
			//crate bucket and pass to construct

			std::allocator_traits<Allocator>::construct(allocator, buckets[index], std::move(value));
		}

		//deletes bucket at index
		void destroy(size_t index)
		{
			std::allocator_traits<Allocator>::destroy(allocator, buckets[index]);
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