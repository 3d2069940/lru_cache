//----------------------------------------------------------------------------
#include <gtest/gtest.h>
//----------------------------------------------------------------------------
#include "lru_cache.hpp"
//----------------------------------------------------------------------------
TEST(LRUCacheTest, Initialization)
{
  {
    LRUCache<int, int> cache;
    ASSERT_EQ(0, cache.capacity());
    EXPECT_EQ(nullptr, cache.get(1));
    cache.put(1, 10);
    ASSERT_EQ(0, cache.capacity());
    EXPECT_EQ(nullptr, cache.get(1));
  }
  {
    LRUCache<int, int> cache (10);
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
TEST(LRUCacheTest, Emplace)
{
  struct MyStruct
  {
    int         a_;
    char        b_;
    std::string c_;
  };
  {
    LRUCache<int, MyStruct> cache(1);
    cache.emplace(1, 1, '1', "1");
    MyStruct * ptr = cache.get(1);
    ASSERT_NE(nullptr, ptr);
    EXPECT_EQ(1, ptr->a_);
    EXPECT_EQ('1', ptr->b_);
    EXPECT_EQ("1", ptr->c_);
  }
}
//----------------------------------------------------------------------------
TEST(LRUCacheTest, Displacement)
{
  {
    LRUCache<int, int> cache(1);
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