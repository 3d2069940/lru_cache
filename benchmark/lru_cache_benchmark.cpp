//----------------------------------------------------------------------------
#include <random>
//----------------------------------------------------------------------------
#include <benchmark/benchmark.h>
//----------------------------------------------------------------------------
#include "lru_cache.hpp"
//----------------------------------------------------------------------------
static void BM_CachePut(benchmark::State & state) 
{
  LRUCache::Cache<int, int> cache(10000);

  for (auto _ : state)
    cache.put(1, 1);
}
//----------------------------------------------------------------------------
static void BM_CacheRandomPut(benchmark::State & state)
{
  LRUCache::Cache<int, int> cache(10000);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib(1, 10000);

  for (int i = 0; i < 10000; ++i)
    cache.put(i, 1);

  for (auto _ : state)
  {
    int i;
    benchmark::DoNotOptimize(i = distrib(gen));
    cache.put(i, 1);
  }
}
//----------------------------------------------------------------------------
static void BM_CacheGet(benchmark::State & state) 
{
  LRUCache::Cache<int, int> cache(10000);

  for (int i = 0; i < 10000; ++i)
    cache.put(i, i);

  for (auto _ : state)
    cache.get(1);
}
//----------------------------------------------------------------------------
static void BM_CacheRandomGet(benchmark::State & state)
{
  LRUCache::Cache<int, int> cache(10000);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib(0, 10000);

  for (int i = 0; i < 10000; ++i)
    cache.put(i, 1);

  for (auto _ : state)
  {
    int i;
    benchmark::DoNotOptimize(i = distrib(gen));
    cache.get(i);
  }
}
//----------------------------------------------------------------------------
static void BM_CacheRemove(benchmark::State & state) 
{
  LRUCache::Cache<int, int> cache(10000);

  for (int i = 0; i < 10000; ++i)
    cache.put(i, 1);

  for (auto _ : state)
    cache.remove(42);
}
//----------------------------------------------------------------------------
static void BM_CacheRandomRemove(benchmark::State & state)
{
  LRUCache::Cache<int, int> cache(10000);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib(0, 10000);

  for (int i = 0; i < 10000; ++i)
    cache.put(i, 1);

  for (auto _ : state)
  {
    int i;
    benchmark::DoNotOptimize(i = distrib(gen));
    cache.remove(i);
  }
}
//----------------------------------------------------------------------------
BENCHMARK(BM_CachePut);
BENCHMARK(BM_CacheRandomPut);
BENCHMARK(BM_CacheGet);
BENCHMARK(BM_CacheRandomGet);
BENCHMARK(BM_CacheRemove);
BENCHMARK(BM_CacheRandomRemove);
//----------------------------------------------------------------------------