//----------------------------------------------------------------------------
#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP
//----------------------------------------------------------------------------
#include <map>
//----------------------------------------------------------------------------
#include "circular_doubly_linked_list.hpp"
//----------------------------------------------------------------------------
template<class KeyT, class ValueT>
class LRUCache
{
//----------------------------------------------------------------------------
public:
  LRUCache();
  LRUCache(std::size_t capacity);
//----------------------------------------------------------------------------
  std::size_t capacity() const;
//----------------------------------------------------------------------------
  void put(const KeyT & key, const ValueT & value);
//----------------------------------------------------------------------------
  template<class ...Args>
  void emplace(const KeyT & key, Args && ...args) noexcept;
//----------------------------------------------------------------------------
        ValueT * get(const KeyT & key);
  const ValueT * get(const KeyT & key) const;
//----------------------------------------------------------------------------
private:
//----------------------------------------------------------------------------
  struct MapValue;
//----------------------------------------------------------------------------
  using ListT    = CircularDoublyLinkedList<KeyT>;
  using ListItT  = ListT::iterator;
  using ListNode = CircularDoublyLinkedListNode<KeyT>;
  using MapT     = std::map<KeyT, MapValue>;
//----------------------------------------------------------------------------
struct MapValue
{
//----------------------------------------------------------------------------
  ListItT it_;
  ValueT  value_;
//----------------------------------------------------------------------------
  MapValue(const ListItT & it, const ValueT & value);
  MapValue(ListItT && it, ValueT && value) noexcept;
//----------------------------------------------------------------------------
}; // struct MapValue
//----------------------------------------------------------------------------
  std::size_t capacity_;
  ListT       list_;
  MapT        map_;
//----------------------------------------------------------------------------
}; // class LRUCache
//----------------------------------------------------------------------------
template<class KeyT, class ValueT>
LRUCache<KeyT, ValueT>::MapValue::MapValue(const ListItT & it, const ValueT & value) :
  it_(it),
  value_(value)
{
}
//----------------------------------------------------------------------------
template<class KeyT, class ValueT>
LRUCache<KeyT, ValueT>::MapValue::MapValue(ListItT && it, ValueT && value) noexcept :
  it_(std::move(it)),
  value_(std::forward<ValueT>(value))
{
}
//----------------------------------------------------------------------------
template<class KeyT, class ValueT>
LRUCache<KeyT, ValueT>::LRUCache() :
  capacity_(0)
{
}
//----------------------------------------------------------------------------
template<class KeyT, class ValueT>
LRUCache<KeyT, ValueT>::LRUCache(std::size_t capacity) :
  capacity_(capacity)
{
}
//----------------------------------------------------------------------------
template<class KeyT, class ValueT>
std::size_t LRUCache<KeyT, ValueT>::capacity() const
{
  return capacity_;
}
//----------------------------------------------------------------------------
template<class KeyT, class ValueT>
void LRUCache<KeyT, ValueT>::put(const KeyT & key, const ValueT & value)
{
  if (capacity_ == 0)
    return;
  auto it = map_.find(key);
  if (it == map_.end())
  {
    list_.pushFront(key);
    map_.emplace_hint(it, key, MapValue(list_.begin(), value));
    if (list_.size() > capacity_)
    {
      map_.erase(list_.back());
      list_.popBack();
    }
    return;
  }
  it->second.value_ = value;
  list_.toFront(it->second.it_);
}
//----------------------------------------------------------------------------
template<class KeyT, class ValueT>
template<class ...Args>
void LRUCache<KeyT, ValueT>::emplace(const KeyT & key, Args && ...args) noexcept
{
  auto it = map_.find(key);
  if (it == map_.end())
  {
    list_.pushFront(key);
    map_.emplace_hint(it, key, MapValue(list_.begin(), ValueT(args...)));
    if (list_.size() > capacity_)
    {
      map_.erase(list_.back());
      list_.popBack();
    }
    return;
  }
  it->second.value_ = std::forward<ValueT>(ValueT(args...));
  list_.toFront(it->second.it_);
}
//----------------------------------------------------------------------------
template<class KeyT, class ValueT>
ValueT * LRUCache<KeyT, ValueT>::get(const KeyT & key)
{
  auto it = map_.find(key);
  if (it == map_.end())
    return nullptr;
  list_.toFront(it->second.it_);
  return &(it->second.value_);
}
//----------------------------------------------------------------------------
template<class KeyT, class ValueT>
const ValueT * LRUCache<KeyT, ValueT>::get(const KeyT & key) const
{
  auto it = map_.find(key);
  if (it == map_.end())
    return nullptr;
  list_.toFront(it->second.it_);
  return &(it->second.value_);
}
//----------------------------------------------------------------------------
#endif // LRU_CACHE_HPP
//----------------------------------------------------------------------------