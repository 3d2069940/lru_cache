//----------------------------------------------------------------------------
#include <benchmark/benchmark.h>
//----------------------------------------------------------------------------
#include "circular_doubly_linked_list.hpp"
//----------------------------------------------------------------------------
static void BM_PushBackPopBack(benchmark::State & state)
{
  CircularDoublyLinkedList<int> list;

  for (auto _ : state)
  {
    list.pushBack(1);
    list.popBack();
  }
}
//----------------------------------------------------------------------------
static void BM_PushFrontPopFront(benchmark::State & state)
{
  CircularDoublyLinkedList<int> list;

  for (auto _ : state)
  {
    list.pushFront(1);
    list.popFront();
  }
}
//----------------------------------------------------------------------------
static void BM_ToFrontWithTwoElems(benchmark::State & state)
{
  CircularDoublyLinkedList<int> list = {1, 2};

  for (auto _ : state)
  {
    auto it = list.begin();
    ++it;
    list.toFront(it);
  }
}
//----------------------------------------------------------------------------
static void BM_ToFrontWithThreeElems(benchmark::State & state)
{
  CircularDoublyLinkedList<int> list = {1, 2, 3};

  for (auto _ : state)
  {
    auto it = list.begin();
    ++it;
    list.toFront(it);
  }
}
//----------------------------------------------------------------------------
static void BM_ToBackWithTwoElems(benchmark::State & state)
{
  CircularDoublyLinkedList<int> list = {1, 2};

  for (auto _ : state)
  {
    auto it = list.begin();
    ++it;
    list.toBack(it);
  }
}
//----------------------------------------------------------------------------
static void BM_ToBackWithThreeElems(benchmark::State & state)
{
  CircularDoublyLinkedList<int> list = {1, 2, 3};

  for (auto _ : state)
  {
    auto it = list.begin();
    ++it;
    list.toBack(it);
  }
}
//----------------------------------------------------------------------------
BENCHMARK(BM_PushBackPopBack);
//----------------------------------------------------------------------------
BENCHMARK(BM_PushFrontPopFront);
//----------------------------------------------------------------------------
BENCHMARK(BM_ToFrontWithTwoElems);
//----------------------------------------------------------------------------
BENCHMARK(BM_ToFrontWithThreeElems);
//----------------------------------------------------------------------------
BENCHMARK(BM_ToBackWithTwoElems);
//----------------------------------------------------------------------------
BENCHMARK(BM_ToBackWithThreeElems);
//----------------------------------------------------------------------------