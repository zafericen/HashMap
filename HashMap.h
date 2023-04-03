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
			size_t hash{ &arg };
			hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
			hash = (hash >> 16) ^ hash) * 0x45d9f3b;
			hash = (hash >> 16) ^ hash;
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

	template<typename Key, typename Item>
	struct Bucket
	{
		Key key;
		Item item;
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
		typename Item,
		typename Hash,
		typename Allocator = std::allocator<Bucket<Key, Item>>>
	class HashMap
	{
	private:
		using BucketArray = Bucket*;
		using StatusVector = std::vector<BucketStatus>;

		enum class BucketStatus : uint8_t
		{
			EMPTY,
			DELETED,
			FULL
		};

		Allocator allocator;
		Probe probe;
		Hash hasher;
		BucketArray buckets;
		StatusVector status;
		size_t size;
		size_t tableSize;

	public:
		HashMap() = default;

		~HashMap() = default;

		void insert(const Key& key, const Item& item)
		{
			insert(key, Item{ item });
		}

		void insert(Key&& key, Item&& item)
		{
			size_t hashValue{ hasher(index) % tableSize };
			size_t probeValue{ hashValue };
			while (true)
			{
				if (status[probeValue] == BucketStatus::EMPTY)
				{

				}
			}
		}

		void erase(size_t index)
		{
		}

		void find()
		{
		}

		bool contains() const
		{
		}

		void begin()
		{
		}

		void end()
		{
		}

		void rehash(size_t newTableSize)
		{
			BucketArray newTable{ arrays.push_back(std::allocator_traits<Allocator>::allocate(allocator, tableSize)) };
			
			//Carry all elemets with rehashing.

			clear();

			std::allocator_traits<Allocator>::deallocate(allocator, removal, arraySize);

			buckets = newTable;
		}

	private:
		void construct(size_t index, Item&& value)
		{
			std::allocator_traits<Allocator>::construct(allocator, buckets[index], std::move(item));
		}

		void destroy(size_t index)
		{
			std::allocator_traits<Allocator>::destroy(allocator, buckets[index]);
		}

		void checkLoad()
		{
		}

		void clear()
		{
		}
	};


}

#endif