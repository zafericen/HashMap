#ifndef HASHMAP_H
#define HASHMAP_H

#include <utility>
#include <memory>
#include <cstdint>
#include <vector>

namespace ByteC
{

	template<typename Key, typename Item>
	struct Bucket
	{
		Key key;
		Item item;
	};

	template<
		typename Key,
		typename Item,
		typename Hash,
		typename Allocator = std::allocator<Bucket<Key,Item>>>
	class HashMap
	{
	private:
		using BucketArray = Bucket*;
		
		Allocator allocator;
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
		}

		void erase(const Key& index)
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

		size_t size() const
		{
			return size;
		}

		void rehash(size_t newTableSize)
		{
			BucketArray newTable{ arrays.push_back(std::allocator_traits<Allocator>::allocate(allocator, tableSize)) };
			std::allocator_traits<Allocator>::deallocate(allocator, removal, arraySize);
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
	};

	
}

#endif