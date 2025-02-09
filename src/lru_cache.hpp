//----------------------------------------------------------------------------
#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP
//----------------------------------------------------------------------------
#include <map>
#include <list>
#include <utility>
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
namespace LRUCache
{
//----------------------------------------------------------------------------
namespace Internal
{
//----------------------------------------------------------------------------
template<class _ListT, class _ValueT>
struct MapValue
{
//----------------------------------------------------------------------------
  using IteratorT = typename _ListT::iterator;
//----------------------------------------------------------------------------
  IteratorT it_;
  _ValueT   value_;
//----------------------------------------------------------------------------
  MapValue(const IteratorT & it, const _ValueT & value);
  MapValue(IteratorT && it, _ValueT && value) noexcept;
//----------------------------------------------------------------------------
}; // struct MapValue
//----------------------------------------------------------------------------
template<class _KeyT, class _Alloc = std::allocator<_KeyT>>
using ListT = std::list<_KeyT, _Alloc>;
//----------------------------------------------------------------------------
template<class _KeyT, class _ValueT, class _ListT>
using MapT = std::map<_KeyT, MapValue<ListT<_KeyT>, _ValueT>>;
//----------------------------------------------------------------------------
} // namespace Internal
//----------------------------------------------------------------------------
/**
 * @brief LRU cache implementation.
 *
 * This class provides a cache that stores key-value pairs with a specified
 * capacity. When the cache exceeds its capacity, the least recently used items
 * are evicted to make room for new entries. The cache uses a list to maintain
 * the order of items and a map for fast key-value lookups.
 *
 * @tparam _KeyT The type of keys used in the cache.
 * @tparam _ValueT The type of values associated with the keys in the cache.
 * @tparam _ListT The type of the list used to maintain the order of items.
 *                 Defaults to `::LRUCache::Internal::ListT<_KeyT>`.
 * @tparam _MapT The type of the map used for fast key-value lookups.
 *                Defaults to `::LRUCache::Internal::MapT<_KeyT, _ValueT, _ListT>`.
 */
template<class _KeyT, class _ValueT, class _ListT = ::LRUCache::Internal::ListT<_KeyT>, class _MapT = ::LRUCache::Internal::MapT<_KeyT, _ValueT, _ListT>>
class Cache
{
//----------------------------------------------------------------------------
  using SizeType      = typename _ListT::size_type; ///< Type representing the size of the cache.
  using ListIteratorT = typename _ListT::iterator;  ///< Iterator type for the list.
  using MapValueT     = Internal::MapValue<_ListT, _ValueT>; ///< Type representing the value stored in the map, which includes the list iterator and the associated value.
//----------------------------------------------------------------------------
public:
  /**
   * @brief Default constructor for the Cache class.
   *
   * Initializes an empty cache with the default capacity.
   */
  Cache();
    /**
   * @brief Constructs a Cache with a specified capacity.
   *
   * @param capacity The maximum number of items that the cache can hold.
   */
  Cache(SizeType capacity);
  /**
   * @brief Retrieves the current capacity of the cache.
   *
   * @return The maximum number of items that the cache can hold.
   */
  SizeType capacity() const;
  /**
   * @brief Retrieves the current number of items in the cache.
   *
   * @return The number of items currently stored in the cache.
   */
  SizeType size() const;
  /**
   * @brief Inserts or updates a value in the cache associated with the specified key.
   *
   * This function adds a new key-value pair to the cache. If the key already exists,
   * the associated value is updated. If the cache exceeds its capacity after the
   * insertion, the least recently used item is evicted.
   *
   * @param key The key associated with the value to be inserted or updated.
   * @param value The value to be associated with the specified key.
   */
  void put(const _KeyT & key, const _ValueT & value);
    /**
   * @brief Inserts or updates a value in the cache associated with the specified key.
   *
   * This overload accepts an rvalue reference for the value, allowing for efficient
   * moves of temporary objects into the cache.
   *
   * @param key The key associated with the value to be inserted or updated.
   * @param value The value to be associated with the specified key.
   */
  void put(const _KeyT & key, _ValueT && value);
  /**
   * @brief Constructs and inserts a value in the cache associated with the specified key.
   *
   * This function constructs a new value in place using the provided arguments and
   * associates it with the specified key. If the key already exists, the associated
   * value is updated. If the cache exceeds its capacity after the insertion, the
   * least recently used item is evicted.
   *
   * @param key The key associated with the value to be constructed and inserted or updated.
   * @param args The arguments used to construct the value. These can be of any type
   *             that is compatible with the constructor of `_ValueT`.
   */
  template<class ...Args>
  void emplace(const _KeyT & key, Args && ...args) noexcept;
  /**
   * @brief Removes the value associated with the specified key from the cache.
   *
   * This function removes the key-value pair from the cache if it exists.
   *
   * @param key The key associated with the value to be removed.
   * @return True if the key was found and removed, false otherwise.
   */
  bool remove(const _KeyT & key);
  /**
   * @brief Clears all items from the cache.
   *
   * This function removes all key-value pairs from the cache, effectively resetting it.
   */
  inline void clear();
  /**
   * @brief Retrieves a pointer to the value associated with the specified key.
   *
   * This function searches for the specified key in the cache. If the key is found,
   * the associated value is marked as recently used. The function returns a pointer
   * to the value.
   *
   * @param key The key associated with the value to be retrieved.
   * @return A pointer to the value associated with the specified key, or nullptr
   *         if the key is not found in the cache.
   */
  _ValueT * get(const _KeyT & key);
  /**
   * @brief Retrieves a pointer to the value associated with the specified key.
   *
   * This const-qualified version of the function can be called on const instances
   * of the Cache. It behaves the same as the non-const version.
   *
   * @param key The key associated with the value to be retrieved.
   * @return A pointer to the value associated with the specified key, or nullptr
   *         if the key is not found in the cache.
   */
  const _ValueT * get(const _KeyT & key) const;
  /**
   * @brief Checks if the cache contains a value associated with the specified key.
   *
   * @param key The key to check for existence in the cache.
   * @return True if the key exists in the cache, false otherwise.
   * @note Does not update position of the associated value
   */
  bool contains(const _KeyT & key) const;
//----------------------------------------------------------------------------
private:
//----------------------------------------------------------------------------
  SizeType capacity_; ///< The maximum number of items that the cache can hold.
  _ListT   list_; ///< The list used to maintain the order of items.
  _MapT    map_; ///< The map used for fast key-value lookups.
//----------------------------------------------------------------------------
}; // class Cache
//----------------------------------------------------------------------------
} // namespace LRUCache
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
namespace LRUCache
{
//----------------------------------------------------------------------------
namespace Internal
{
//----------------------------------------------------------------------------
template<class _ListT, class _ValueT>
MapValue<_ListT, _ValueT>::MapValue(const IteratorT & it, const _ValueT & value) :
  it_(it),
  value_(value)
{
}
//----------------------------------------------------------------------------
template<class _ListT, class _ValueT>
MapValue<_ListT, _ValueT>::MapValue(IteratorT && it, _ValueT && value) noexcept :
  it_(std::forward<IteratorT>(it)),
  value_(std::forward<_ValueT>(value))
{
}
//----------------------------------------------------------------------------
} // namespace Internal
//----------------------------------------------------------------------------
template<class _KeyT, class _ValueT, class _ListT, class _MapT>
Cache<_KeyT, _ValueT, _ListT, _MapT>::Cache() :
  capacity_(0)
{
}
//----------------------------------------------------------------------------
template<class _KeyT, class _ValueT, class _ListT, class _MapT>
Cache<_KeyT, _ValueT, _ListT, _MapT>::Cache(SizeType capacity) :
  capacity_(capacity)
{
}
//----------------------------------------------------------------------------
template<class _KeyT, class _ValueT, class _ListT, class _MapT>
typename Cache<_KeyT, _ValueT, _ListT, _MapT>::SizeType Cache<_KeyT, _ValueT, _ListT, _MapT>::capacity() const
{
  return capacity_;
}
//----------------------------------------------------------------------------
template<class _KeyT, class _ValueT, class _ListT, class _MapT>
typename Cache<_KeyT, _ValueT, _ListT, _MapT>::SizeType Cache<_KeyT, _ValueT, _ListT, _MapT>::size() const
{
  return list_.size();
}
//----------------------------------------------------------------------------
template<class _KeyT, class _ValueT, class _ListT, class _MapT>
void Cache<_KeyT, _ValueT, _ListT, _MapT>::put(const _KeyT & key, const _ValueT & value)
{
  auto it = map_.find(key);
  if (it == map_.end())
  {
    list_.push_front(key);
    map_.emplace_hint(it, key, MapValueT(list_.begin(), value));
    if (list_.size() > capacity_)
    {
      map_.erase(list_.back());
      list_.pop_back();
    }
    return;
  }
  auto & mapEntryData = it->second;
  mapEntryData.value_ = value;
  list_.splice(list_.begin(), list_, mapEntryData.it_);
}
//----------------------------------------------------------------------------
template<class _KeyT, class _ValueT, class _ListT, class _MapT>
void Cache<_KeyT, _ValueT, _ListT, _MapT>::put(const _KeyT & key, _ValueT && value)
{
  auto it = map_.find(key);
  if (it == map_.end())
  {
    list_.push_front(key);
    map_.emplace_hint(it, key, MapValueT(list_.begin(), std::forward<_ValueT>(value)));
    if (list_.size() > capacity_)
    {
      map_.erase(list_.back());
      list_.pop_back();
    }
    return;
  }
  auto & mapEntryData = it->second;
  mapEntryData.value_ = std::forward<_ValueT>(value);
  list_.splice(list_.begin(), list_, mapEntryData.it_);
}
//----------------------------------------------------------------------------
template<class _KeyT, class _ValueT, class _ListT, class _MapT>
template<class ...Args>
void Cache<_KeyT, _ValueT, _ListT, _MapT>::emplace(const _KeyT & key, Args && ...args) noexcept
{
  auto it = map_.find(key);
  if (it == map_.end())
  {
    list_.push_front(key);
    map_.emplace_hint(it, key, MapValueT(list_.begin(), _ValueT(args...)));
    if (list_.size() > capacity_)
    {
      map_.erase(list_.back());
      list_.pop_back();
    }
    return;
  }
  auto & mapEntryData = it->second;
  mapEntryData.value_ = std::forward<_ValueT>(_ValueT(args...));
  list_.splice(list_.begin(), list_, mapEntryData.it_);
}
//----------------------------------------------------------------------------
template<class _KeyT, class _ValueT, class _ListT, class _MapT>
bool Cache<_KeyT, _ValueT, _ListT, _MapT>::remove(const _KeyT & key)
{
  auto it = map_.find(key);
  if (it == map_.end())
    return false;
  auto & mapEntryData = it->second;
  list_.erase(mapEntryData.it_);
  map_.erase(it);
  return true;
}
//----------------------------------------------------------------------------
template<class _KeyT, class _ValueT, class _ListT, class _MapT>
void Cache<_KeyT, _ValueT, _ListT, _MapT>::clear()
{
  list_.clear();
  map_.clear();
}
//----------------------------------------------------------------------------
template<class _KeyT, class _ValueT, class _ListT, class _MapT>
_ValueT * Cache<_KeyT, _ValueT, _ListT, _MapT>::get(const _KeyT & key)
{
  auto it = map_.find(key);
  if (it == map_.end())
    return nullptr;
  auto & mapEntryData = it->second;
  list_.splice(list_.begin(), list_, mapEntryData.it_);
  return &(mapEntryData.value_);
}
//----------------------------------------------------------------------------
template<class _KeyT, class _ValueT, class _ListT, class _MapT>
const _ValueT * Cache<_KeyT, _ValueT, _ListT, _MapT>::get(const _KeyT & key) const
{
  auto it = map_.find(key);
  if (it == map_.end())
    return nullptr;
  auto & mapEntryData = it->second;
  list_.splice(list_.begin(), mapEntryData.it_);
  return &(mapEntryData.value_);
}
//----------------------------------------------------------------------------
template<class _KeyT, class _ValueT, class _ListT, class _MapT>
bool Cache<_KeyT, _ValueT, _ListT, _MapT>::contains(const _KeyT & key) const
{
  return map_.find(key) == map_.end();
}
//----------------------------------------------------------------------------
} // namespace LRUCache
//----------------------------------------------------------------------------
#endif // LRU_CACHE_HPP
//----------------------------------------------------------------------------