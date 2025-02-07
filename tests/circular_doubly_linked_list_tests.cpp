//----------------------------------------------------------------------------
#include <gtest/gtest.h>
//----------------------------------------------------------------------------
#include "circular_doubly_linked_list.hpp"
//----------------------------------------------------------------------------
TEST(CircularDoublyLinkedListTest, Initialization)
{
  {
    CircularDoublyLinkedList<int> list;
    EXPECT_EQ(0, list.size());
    EXPECT_TRUE(list.empty());
  }
  {
    CircularDoublyLinkedList<int> list = {1};
    ASSERT_EQ(1, list.size());
    EXPECT_EQ(1, list.back());
    EXPECT_EQ(1, list.front());
  }
  {
    CircularDoublyLinkedList<int> list = {1, 2};
    ASSERT_EQ(2, list.size());
    EXPECT_EQ(1, list.front());
    EXPECT_EQ(2, list.back());
  }
  {
    CircularDoublyLinkedList<int> list = {1, 2, 3};
    ASSERT_EQ(3, list.size());
    EXPECT_EQ(1, list.front());
    EXPECT_EQ(3, list.back());
  }
}
//----------------------------------------------------------------------------
TEST(CircularDoublyLinkedListTest, Iterators)
{
  {
    CircularDoublyLinkedList<int> list = {1};
    auto it = list.begin();
    std::size_t times = 0;
    for ( ; it != list.end(); ++it)
      ++times;
    EXPECT_EQ(1, times);
  }
  {
    CircularDoublyLinkedList<int> list = {1, 2, 3};
    auto it = list.begin();
    auto end = list.end();
    EXPECT_FALSE(it == end);
    EXPECT_EQ(1, it->value_);
    ++it;
    --it;
    EXPECT_FALSE(it == end);
    ++it;
    EXPECT_EQ(2, it->value_);
    ++it;
    EXPECT_EQ(3, it->value_);
    ++it;
    EXPECT_TRUE(it == end);
    EXPECT_EQ(1, it->value_);
  }
}
//----------------------------------------------------------------------------
TEST(CircularDoublyLinkedListTest, PushBack)
{
  {
    CircularDoublyLinkedList<int> list;
    ASSERT_TRUE(list.empty());

    list.pushBack(1);
    ASSERT_EQ(1, list.size());
    EXPECT_EQ(1, list.front());
    EXPECT_EQ(1, list.back());

    list.pushBack(2);
    ASSERT_EQ(2, list.size());
    EXPECT_EQ(1, list.front());
    EXPECT_EQ(2, list.back());
  }
  {
    CircularDoublyLinkedList<int> list;

    for (int i = 0; i < 1000; ++i)
      list.pushBack(i);

    EXPECT_EQ(1000, list.size());
    EXPECT_EQ(0, list.front());
    EXPECT_EQ(999, list.back());
  }
}
//----------------------------------------------------------------------------
TEST(CircularDoublyLinkedListTest, PopBack)
{
  {
    CircularDoublyLinkedList<int> list;

    list.pushBack(1);
    list.popBack();
    ASSERT_EQ(0, list.size());
  }
  {
    CircularDoublyLinkedList<int> list;

    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    list.popBack();
    ASSERT_EQ(2, list.size());
    EXPECT_EQ(1, list.front());
    EXPECT_EQ(2, list.back());
  }
  {
    CircularDoublyLinkedList<int> list;

    for (int i = 0; i < 1000; ++i)
      list.pushBack(i);
    while (list.empty() == false)
      list.popBack();
  }
}
//----------------------------------------------------------------------------
TEST(CircularDoublyLinkedListTest, PushFront)
{
  {
    CircularDoublyLinkedList<int> list;

    list.pushFront(1);
    ASSERT_EQ(1, list.size());
    EXPECT_EQ(1, list.front());
    list.pushFront(2);
    ASSERT_EQ(2, list.size());
    EXPECT_EQ(2, list.front());
    list.pushFront(3);
    ASSERT_EQ(3, list.size());
    EXPECT_EQ(3, list.front());
  }
  {
    CircularDoublyLinkedList<int> list;

    for (std::size_t i = 0; i < 1000; ++i)
    {
      list.pushFront(i);
      EXPECT_EQ(i, list.front());
    }
  }
}
//----------------------------------------------------------------------------
TEST(CircularDoublyLinkedListTest, PopFront)
{
  {
    CircularDoublyLinkedList<int> list;

    list.pushFront(1);
    list.popFront();
    ASSERT_EQ(0, list.size());
  }
  {
    CircularDoublyLinkedList<int> list;

    list.pushFront(1);
    list.pushFront(2);
    list.pushFront(3);
    ASSERT_EQ(3, list.size());
    list.popFront();
    ASSERT_EQ(2, list.size());
    EXPECT_EQ(2, list.front());
    EXPECT_EQ(1, list.back());
    list.popFront();
    ASSERT_EQ(1, list.size());
    EXPECT_EQ(1, list.front());
    EXPECT_EQ(1, list.back());
  }
  {
    CircularDoublyLinkedList<int> list;

    for (std::size_t i = 0; i < 10; ++i)
      list.pushFront(i);
    while (list.empty() == false)
      list.popFront();
  }
}
//----------------------------------------------------------------------------
TEST(CircularDoublyLinkedListTest, ToFront)
{
  {
    CircularDoublyLinkedList<int> list;

    list.pushFront(10);
    EXPECT_EQ(10, list.front());

    auto it = list.begin();
    list.toFront(it);

    EXPECT_EQ(10, list.front());
  }
  {
    CircularDoublyLinkedList<int> list;

    list.pushFront(20);
    list.pushFront(10);
    EXPECT_EQ(10, list.front());
    EXPECT_EQ(20, list.back());
    auto it = list.begin();
    ++it;
    list.toFront(it);
    EXPECT_EQ(20, list.front());
    EXPECT_EQ(10, list.back());
  }
  {
    CircularDoublyLinkedList<int> list;

    list.pushFront(30);
    list.pushFront(20);
    list.pushFront(10);
    EXPECT_EQ(10, list.front());
    EXPECT_EQ(30, list.back());
    auto it = list.begin();
    ++it;
    list.toFront(it);
    EXPECT_EQ(20, list.front());
    EXPECT_EQ(30, list.back());
  }
}
//----------------------------------------------------------------------------
TEST(CircularDoublyLinkedListTest, ToBack)
{
  {
    CircularDoublyLinkedList<int> list;

    list.pushFront(10);
    EXPECT_EQ(10, list.front());

    auto it = list.begin();
    list.toBack(it);

    EXPECT_EQ(10, list.front());
  }
  {
    CircularDoublyLinkedList<int> list;

    list.pushFront(20);
    list.pushFront(10);
    EXPECT_EQ(10, list.front());
    EXPECT_EQ(20, list.back());

    auto it = list.begin();
    list.toBack(it);

    EXPECT_EQ(20, list.front());
    EXPECT_EQ(10, list.back());
  }
  {
    CircularDoublyLinkedList<int> list;

    list.pushFront(30);
    list.pushFront(20);
    list.pushFront(10);
    EXPECT_EQ(10, list.front());
    EXPECT_EQ(30, list.back());
    auto it = list.begin();
    ++it;
    list.toBack(it);
    EXPECT_EQ(10, list.front());
    EXPECT_EQ(20, list.back());
  }
}
//----------------------------------------------------------------------------