//----------------------------------------------------------------------------
#include <gtest/gtest.h>
//----------------------------------------------------------------------------
#include "circular_doubly_linked_list.hpp"
//----------------------------------------------------------------------------
TEST(CircularDoublyLinkedListTest, Initialization)
{
  {
    CircularDoublyLinkedList<int> list = {1};
    EXPECT_EQ(1, list.back());
    EXPECT_EQ(1, list.front());
  }
  {
    CircularDoublyLinkedList<int> list = {1, 2};
    EXPECT_EQ(1, list.front());
    EXPECT_EQ(2, list.back());
  }
  {
    CircularDoublyLinkedList<int> list = {1, 2, 3};
    EXPECT_EQ(1, list.front());
    EXPECT_EQ(3, list.back());
  }
}
//----------------------------------------------------------------------------