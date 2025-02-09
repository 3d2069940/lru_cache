//----------------------------------------------------------------------------
#include <gtest/gtest.h>
//----------------------------------------------------------------------------
#include "lru_cache.hpp"
//----------------------------------------------------------------------------
TEST(LRUCacheTest, Initialization)
{
  {
    LRUCache::Cache<int, int> cache;
    ASSERT_EQ(0, cache.capacity());
    EXPECT_EQ(nullptr, cache.get(1));
    cache.put(1, 10);
    ASSERT_EQ(0, cache.capacity());
    EXPECT_EQ(nullptr, cache.get(1));
  }
  {
    LRUCache::Cache<int, int> cache(10);
    ASSERT_EQ(10, cache.capacity());
    for (int i = 1; i <= 10; ++i)
      EXPECT_EQ(nullptr, cache.get(i));
    ASSERT_EQ(10, cache.capacity());
    for (int i = 1; i <= 10; ++i)
      cache.put(i, i);
    ASSERT_EQ(10, cache.capacity());
    for (int i = 1; i <= 10; ++i)
      EXPECT_EQ(i, *cache.get(i));
    ASSERT_EQ(10, cache.capacity());
  }
}
//----------------------------------------------------------------------------
TEST(LRUCacheTest, Size)
{
  {
    LRUCache::Cache<int, int> cache;
    for (size_t i = 0; i < 1000; ++i)
    {
      cache.put(1, 1);
      EXPECT_EQ(0, cache.size());
    }
  }
  {
    LRUCache::Cache<int, int> cache(3);
    EXPECT_EQ(0, cache.size());
    cache.put(10, 10);
    EXPECT_EQ(1, cache.size());
    cache.put(20, 20);
    EXPECT_EQ(2, cache.size());
    cache.put(30, 30);
    EXPECT_EQ(3, cache.size());
  }
}
//----------------------------------------------------------------------------
TEST(LRUCacheTest, Put)
{
  int value = 10;
  {
    LRUCache::Cache<int, int> cache(1);
    cache.put(1, value);
    EXPECT_EQ(value, *cache.get(1));
  }
}
//----------------------------------------------------------------------------
TEST(LRUCacheTest, PutRValueRef)
{
  struct MyStruct
  {
    int         a_;
    char        b_;
    std::string c_;

    MyStruct() :
      a_(0),
      b_('0'),
      c_("0")
    {
    }
  };
  {
    LRUCache::Cache<int, MyStruct> cache(1);
    cache.put(1, MyStruct());
    auto * cacheEntry = cache.get(1);
    EXPECT_EQ(0, cacheEntry->a_);
    EXPECT_EQ('0', cacheEntry->b_);
    EXPECT_EQ("0", cacheEntry->c_);
  }
}
//----------------------------------------------------------------------------
TEST(LRUCacheTest, Emplace)
{
  struct MyStruct
  {
    int         a_;
    char        b_;
    std::string c_;

    MyStruct(int a, char b, std::string c):
      a_(a),
      b_(b),
      c_(c)
    {
    }
  };
  {
    LRUCache::Cache<int, MyStruct> cache(1);
    cache.emplace(1, 1, '1', "1");
    auto * cacheEntry = cache.get(1);
    ASSERT_NE(nullptr, cacheEntry);
    EXPECT_EQ(1, cacheEntry->a_);
    EXPECT_EQ('1', cacheEntry->b_);
    EXPECT_EQ("1", cacheEntry->c_);
  }
}
//----------------------------------------------------------------------------
TEST(LRUCacheTest, Remove)
{
  {
    int capactiy = 1;
    int key      = 10;
    int value    = 100;
    LRUCache::Cache<int, int> cache(capactiy);
    for (int i = 0; i < 1000; ++i)
      EXPECT_FALSE(cache.remove(i));
    cache.put(key, value);
    EXPECT_EQ(value, *cache.get(key));
    EXPECT_TRUE(cache.remove(key));
    EXPECT_EQ(nullptr, cache.get(key));
  }
}
//----------------------------------------------------------------------------
TEST(LRUCacheTest, Displacement)
{
  {
    LRUCache::Cache<int, int> cache(1);
    cache.put(1, 1);
    EXPECT_EQ(1, *cache.get(1));
    for (int i = 0; i <= 1000; ++i)
      cache.put(i, i);
    for (int i = 0; i < 1000; ++i)
      EXPECT_EQ(nullptr, cache.get(i));
    EXPECT_EQ(1000, *cache.get(1000));
  }
}
//----------------------------------------------------------------------------
TEST(LRUCacheTest, OverwriteExistingEntry) {
  LRUCache::Cache<int, int> cache(2);
  cache.put(1, 1);
  cache.put(2, 2);
  cache.put(1, 10); // Overwrite key 1
  EXPECT_EQ(10, *cache.get(1));
  EXPECT_EQ(2, *cache.get(2));
}
//----------------------------------------------------------------------------
TEST(LRUCacheTest, EvictionOrder) {
  LRUCache::Cache<int, int> cache(2);
  cache.put(1, 1);
  cache.put(2, 2);
  cache.put(3, 3);
  EXPECT_EQ(nullptr, cache.get(1));
  EXPECT_EQ(2, *cache.get(2));
  EXPECT_EQ(3, *cache.get(3));
}
//----------------------------------------------------------------------------
TEST(LRUCacheTest, MultipleInsertsAndAccesses) {
  LRUCache::Cache<int, int> cache(3);
  cache.put(1, 1);
  cache.put(2, 2);
  cache.put(3, 3);
  cache.get(1);
  cache.put(4, 4);
  EXPECT_EQ(nullptr, cache.get(2));
  EXPECT_EQ(1, *cache.get(1));
  EXPECT_EQ(3, *cache.get(3));
  EXPECT_EQ(4, *cache.get(4));
}
//----------------------------------------------------------------------------
TEST(LRUCacheTest, StressTest) {
  LRUCache::Cache<int, int> cache(100000);
  for (int i = 0; i < 200000; ++i)
    cache.put(i, i);
  for (int i = 0; i < 100000; ++i)
    EXPECT_EQ(nullptr, cache.get(i));
  for (int i = 100000; i < 200000; ++i)
    EXPECT_EQ(i, *cache.get(i));
}
//----------------------------------------------------------------------------