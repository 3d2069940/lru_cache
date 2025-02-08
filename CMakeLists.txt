cmake_minimum_required(VERSION 3.10)

project(lru_cache)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

set(LRU_CACHE_SRC
  src/circular_doubly_linked_list.hpp
)

add_executable(tests
  tests/main.cpp
  tests/circular_doubly_linked_list_tests.cpp
  tests/lru_cache_tests.cpp
)
target_sources(tests PRIVATE ${LRU_CACHE_SRC})
target_include_directories(tests PRIVATE src)
target_link_libraries(tests PRIVATE ${GTEST_LIBRARIES})

add_executable(benchmark_exec
  benchmark/main.cpp
  benchmark/circular_doubly_linked_list_benchmark.cpp
)
target_sources(benchmark_exec PRIVATE ${LRU_CACHE_SRC})
target_include_directories(benchmark_exec PRIVATE src)
target_link_libraries(benchmark_exec benchmark::benchmark)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(tests PRIVATE -Wall -Wextra -g)
  target_compile_options(benchmark_exec PRIVATE -Wall -Wextra -g)
endif()