cmake_minimum_required(VERSION 3.10)

project(lru_cache)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

set(LRU_CACHE_SRC
  src/circular_doubly_linked_list.hpp
)

add_executable(tests
  tests/main.cpp
  tests/circular_doubly_linked_list_tests.cpp
  tests/lru_cache_tests.cpp
)

target_sources(tests PRIVATE ${LRU_CACHE_SRC})
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(tests PRIVATE -Wall -Wextra -g)
endif()
target_include_directories(tests PRIVATE src)
target_link_libraries(tests PRIVATE ${GTEST_LIBRARIES})