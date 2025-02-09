# LRU Cache

## Description

LRU Cache is a Least Recently Used (LRU) cache implementation designed to optimize data retrieval by storing frequently accessed items. [Wikipedia](https://en.wikipedia.org/wiki/Cache_replacement_policies#Least_Recently_Used_(LRU))

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [License](#license)

## Installation

To install the LRU Cache, follow these steps:

1. Clone the repo:

    ```sh
    git clone https://github.com/3d2069940/lru_cache.git && cd lru_cache
    ```

2. And just copy `lru_cache.hpp` from `lru_cache/src` right into your project!

3. Optional step. If you want to build tests and benchmark install the following dependencies:

    - CMake: [Github](https://github.com/Kitware/CMake) | [Website](https://cmake.org/)

    - Compiler with C++11 support or higher: [GCC](https://gcc.gnu.org/releases.html), [Clang](https://releases.llvm.org/download.html)

    - [GTest](https://github.com/google/googletest) and [Google Benchmark](https://github.com/google/benchmark) can be installed as an option

4. Optional step. Now run these commands in the `lru_cache` directory:

    ```sh
    cmake -B build -DCMAKE_BUILD_TYPE=Release .
    ```

    ```sh
    cmake --build build -j
    ```
5. Optional step. It's compiled. Simply run:

    ```sh
    ./build/tests && ./build/benchmark_exec
    ```

## Usage

```c++
#include <iostream>
#include "lru_cache.hpp"

int main()
{
  LRUCache::Cache<int, std::string> cache;

  cache.put(1, "string");

  auto * cacheEntry = cache.get(1);

  if (cacheEntry != nullptr)
    std::cout << *cacheEntry << std::endl; // prints "string"
}
```

## Examples

You can find example usage scenarios in the `examples` directory. These examples demonstrate how to implement the LRU Cache in different contexts

## License

This project is licensed under the MIT License. See the [LICENSE](https://github.com/3d2069940/lru_cache/blob/master/LICENSE) file for details.

