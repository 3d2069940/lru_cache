//----------------------------------------------------------------------------
#ifndef CIRCULAR_DOUBLY_LINKED_LIST_HPP
#define CIRCULAR_DOUBLY_LINKED_LIST_HPP
//----------------------------------------------------------------------------
#include <cassert>
#include <iostream>
#include <memory_resource>
//----------------------------------------------------------------------------
template<class ValueT>
struct CircularDoublyLinkedListNode
{
//----------------------------------------------------------------------------
  ValueT                         value_;
  CircularDoublyLinkedListNode * prev_;
  CircularDoublyLinkedListNode * next_;
//----------------------------------------------------------------------------
  CircularDoublyLinkedListNode();
  CircularDoublyLinkedListNode(const ValueT & value);
//----------------------------------------------------------------------------
}; // struct Node
//----------------------------------------------------------------------------
template<class ValueT>
CircularDoublyLinkedListNode<ValueT>::CircularDoublyLinkedListNode() :
  prev_(this),
  next_(this)
{
}
//----------------------------------------------------------------------------
template<class ValueT>
CircularDoublyLinkedListNode<ValueT>::CircularDoublyLinkedListNode(const ValueT & value) :
  value_(value),
  prev_(this),
  next_(this)
{
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc = std::pmr::polymorphic_allocator<CircularDoublyLinkedListNode<ValueT>>>
class CircularDoublyLinkedList
{
//----------------------------------------------------------------------------
public:
//----------------------------------------------------------------------------
  using NodeT = CircularDoublyLinkedListNode<ValueT>;
//----------------------------------------------------------------------------
class iterator
{
//----------------------------------------------------------------------------
public:
//----------------------------------------------------------------------------
  iterator();
  iterator(NodeT * node, std::size_t & size);
  iterator(NodeT * node, std::size_t pos, std::size_t & size);
  iterator(const iterator & rhs);
//----------------------------------------------------------------------------
  iterator & operator =(const iterator & rhs);
//----------------------------------------------------------------------------
  iterator & operator ++();
  iterator & operator --();
//----------------------------------------------------------------------------
        ValueT & operator *();
  const ValueT & operator *() const;
//----------------------------------------------------------------------------
        NodeT * operator ->();
  const NodeT * operator ->() const;  
//----------------------------------------------------------------------------
  bool operator ==(const iterator & rhs) const;
  bool operator !=(const iterator & rhs) const;
//----------------------------------------------------------------------------
private:
  NodeT       * node_;
  std::size_t   pos_;
  bool          dir_;
  std::size_t * size_;
//----------------------------------------------------------------------------
};  // class iterator
//----------------------------------------------------------------------------
  CircularDoublyLinkedList(const Alloc & alloc = Alloc());
  CircularDoublyLinkedList(std::initializer_list<ValueT> init, const Alloc & alloc = Alloc());
  ~CircularDoublyLinkedList();
//----------------------------------------------------------------------------
  CircularDoublyLinkedList & operator =(const CircularDoublyLinkedList & rhs);
//----------------------------------------------------------------------------
  std::size_t size() const;
//----------------------------------------------------------------------------
  bool empty() const;
//----------------------------------------------------------------------------
  void pushFront(const ValueT & val);
  void pushFront(ValueT && val);
//----------------------------------------------------------------------------
  void popFront();
//----------------------------------------------------------------------------
  void pushBack(const ValueT & val);
  void pushBack(ValueT && val);
//----------------------------------------------------------------------------
  void popBack();
//----------------------------------------------------------------------------
  void toFront(iterator it);
  void toBack(iterator it);
//----------------------------------------------------------------------------
  void clear();
//----------------------------------------------------------------------------
  void erase(iterator it);
  void erase(iterator from, const iterator to);
//----------------------------------------------------------------------------
        ValueT & front();
  const ValueT & front() const;
//----------------------------------------------------------------------------
        ValueT & back();
  const ValueT & back() const;
//----------------------------------------------------------------------------
  iterator begin();
  iterator end();
//----------------------------------------------------------------------------
  void print() const;
  void printR() const;
//----------------------------------------------------------------------------
private:
  Alloc       alloc_;
  NodeT     * node_;
  std::size_t size_;
//----------------------------------------------------------------------------
}; // class CircularDoublyLinkedList
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
CircularDoublyLinkedList<ValueT, Alloc>::iterator::iterator() :
  node_(nullptr),
  pos_(0),
  dir_(false),
  size_(nullptr)
{
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
CircularDoublyLinkedList<ValueT, Alloc>::iterator::iterator(NodeT * node, std::size_t & size) :
  node_(node),
  pos_(0),
  dir_(false),
  size_(&size)
{
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
CircularDoublyLinkedList<ValueT, Alloc>::iterator::iterator(NodeT * node, std::size_t pos, std::size_t & size) :
  node_(node),
  pos_(pos),
  dir_(false),
  size_(&size)
{
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
CircularDoublyLinkedList<ValueT, Alloc>::iterator::iterator(const iterator & rhs) :
  node_(rhs.node_),
  pos_(rhs.pos_),
  dir_(rhs.dir_),
  size_(rhs.size_)
{
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
CircularDoublyLinkedList<ValueT, Alloc>::iterator & CircularDoublyLinkedList<ValueT, Alloc>::iterator::operator =(const iterator & rhs)
{
  if (*this != rhs)
  {
    node_ = rhs.node_;
    pos_  = rhs.pos_;
    dir_  = rhs.dir_;
  }
  return *this;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
CircularDoublyLinkedList<ValueT, Alloc>::iterator & CircularDoublyLinkedList<ValueT, Alloc>::iterator::operator++()
{
  node_ = node_->next_;
  if (pos_ == 0)
    dir_ = true; // true = forward
  pos_ += (dir_ ? 1 : -1);
  // NOTE: to handle overflow and underflow
  pos_  = std::min(pos_, std::max((*size_) - 1, (std::size_t)1));
  return *this;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
CircularDoublyLinkedList<ValueT, Alloc>::iterator & CircularDoublyLinkedList<ValueT, Alloc>::iterator::operator--()
{
  node_ = node_->prev_;
  if (pos_ == 0)
    dir_ = false; // false = backward
  pos_ += (dir_ ? -1 : 1);
  // NOTE: to handle overflow and underflow
  pos_ = std::min(pos_, std::max((*size_) - 1, (std::size_t)1));
  return *this;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
ValueT & CircularDoublyLinkedList<ValueT, Alloc>::iterator::operator *()
{
  return node_->value_;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
const ValueT & CircularDoublyLinkedList<ValueT, Alloc>::iterator::operator *() const
{
  return node_->value_;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
CircularDoublyLinkedList<ValueT, Alloc>::NodeT * CircularDoublyLinkedList<ValueT, Alloc>::iterator::operator ->()
{
  return node_;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
const CircularDoublyLinkedList<ValueT, Alloc>::NodeT * CircularDoublyLinkedList<ValueT, Alloc>::iterator::operator ->() const
{
  return node_;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
bool CircularDoublyLinkedList<ValueT, Alloc>::iterator::operator ==(const iterator & rhs) const
{
  return node_ == rhs.node_ && 
         pos_  == rhs.pos_  &&
         size_ == rhs.size_;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
bool CircularDoublyLinkedList<ValueT, Alloc>::iterator::operator !=(const iterator & rhs) const
{
  return !((*this) == rhs);
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
CircularDoublyLinkedList<ValueT, Alloc>::CircularDoublyLinkedList(const Alloc & alloc) :
  alloc_(alloc),
  node_(nullptr),
  size_(0)
{
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
CircularDoublyLinkedList<ValueT, Alloc>::CircularDoublyLinkedList(std::initializer_list<ValueT> init, const Alloc & alloc) :
  alloc_(alloc),
  node_(nullptr),
  size_(init.size())
{
  NodeT * first = nullptr;
  NodeT * last  = nullptr;
  auto it = init.end();
  for (std::size_t i = 0; i < init.size(); ++i)
  {
    std::advance(it, -1);
    if (first == nullptr)
    {
      node_ = alloc_.template new_object<NodeT>(*it);
      first = node_->prev_;
      last  = node_->next_;
      continue;
    }
    node_        = alloc_.template new_object<NodeT>(*it);
    first->prev_ = node_;
    last->next_  = node_;
    node_->next_ = first;
    node_->prev_ = last;
    first = node_;
  }
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
CircularDoublyLinkedList<ValueT, Alloc>::~CircularDoublyLinkedList()
{
  clear();
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
CircularDoublyLinkedList<ValueT, Alloc> & CircularDoublyLinkedList<ValueT, Alloc>::operator =(const CircularDoublyLinkedList<ValueT, Alloc> & rhs)
{
  if (*this == rhs)
    return *this;
  clear();
  for (const auto & value : rhs)
    pushBack(value);
  return *this;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
std::size_t CircularDoublyLinkedList<ValueT, Alloc>::size() const
{
  return size_;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
bool CircularDoublyLinkedList<ValueT, Alloc>::empty() const
{
  return size_ == 0;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
void CircularDoublyLinkedList<ValueT, Alloc>::pushFront(const ValueT & val)
{
  ++size_;
  if (node_ == nullptr)
  {
    node_        = alloc_.template new_object<NodeT>(val);
    node_->next_ = node_;
    node_->prev_ = node_;
    return;
  }
  NodeT * prev = node_->prev_;
  NodeT * old  = prev->next_;

  node_ = alloc_.template new_object<NodeT>(val);

  prev->next_  = node_;
  node_->prev_ = prev;

  old->prev_   = node_;
  node_->next_ = old;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
void CircularDoublyLinkedList<ValueT, Alloc>::pushFront(ValueT && val)
{
  ++size_;
  if (node_ == nullptr)
  {
    node_        = alloc_.template new_object<NodeT>(std::forward<ValueT>(val));
    node_->next_ = node_;
    node_->prev_ = node_;
    return;
  }
  NodeT * prev = node_->prev_;
  NodeT * old  = prev->next_;

  node_ = alloc_.template new_object<NodeT>(std::forward<ValueT>(val));

  prev->next_  = node_;
  node_->prev_ = prev;

  old->prev_   = node_;
  node_->next_ = old;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
void CircularDoublyLinkedList<ValueT, Alloc>::popFront()
{
  --size_;
  NodeT * prev = node_->prev_;
  NodeT * next = node_->next_;
  alloc_.delete_object(node_);
  prev->next_ = next;
  next->prev_ = prev;
  node_ = next;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
void CircularDoublyLinkedList<ValueT, Alloc>::pushBack(const ValueT & val)
{
  ++size_;
  if (node_ == nullptr)
  {
    node_ = alloc_.template new_object<NodeT>(val);
    node_->next_ = node_;
    node_->prev_ = node_;
    return;
  }
  NodeT * prev        = node_->prev_;
  node_->prev_        = alloc_.template new_object<NodeT>(val);
  node_->prev_->next_ = node_;
  node_->prev_->prev_ = prev;
  prev->next_         = node_->prev_;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
void CircularDoublyLinkedList<ValueT, Alloc>::pushBack(ValueT && val)
{
  ++size_;
  if (node_ == nullptr)
  {
    node_        = alloc_.template new_object<NodeT>(val);
    node_->next_ = node_;
    node_->prev_ = node_;
    return;
  }
  NodeT * prev        = node_->prev_;
  node_->prev_        = alloc_.template new_object<NodeT>(std::forward<ValueT>(val));
  node_->prev_->next_ = node_;
  node_->prev_->prev_ = prev;
  prev->next_         = node_->prev_;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
void CircularDoublyLinkedList<ValueT, Alloc>::popBack()
{
  --size_;
  NodeT * prev = node_->prev_->prev_;
  alloc_.delete_object(node_->prev_);
  node_->prev_ = prev;
  prev->next_ = node_;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
void CircularDoublyLinkedList<ValueT, Alloc>::toFront(iterator it)
{
  NodeT * prev = it->prev_;
  NodeT * next = it->next_;
  NodeT * old  = it->prev_->next_;

  prev->next_ = next;
  next->prev_ = prev;

  old->prev_ = node_->prev_;
  old->next_ = node_;

  node_->prev_->next_ = old;
  node_->prev_        = old;

  node_ = old;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
void CircularDoublyLinkedList<ValueT, Alloc>::toBack(iterator it)
{
  NodeT * prev = it->prev_;
  NodeT * next = it->next_;
  NodeT * old  = it->prev_->next_;
  if (old == node_)
  {
    node_ = next;
    return;
  }

  prev->next_ = next;
  next->prev_ = prev;

  old->next_ = node_;
  old->prev_ = node_->prev_;

  node_->prev_->next_ = old;
  node_->prev_        = old;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
void CircularDoublyLinkedList<ValueT, Alloc>::clear()
{
  NodeT * cur  = node_;
  NodeT * next = nullptr;
  if (size_ != 0)
  {
    do
    {
      cur->prev_->next_ = nullptr;
      next = cur->next_;
      alloc_.delete_object(cur);
      cur = next;
    } while (cur != nullptr);
  }
  size_ = 0;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
void CircularDoublyLinkedList<ValueT, Alloc>::erase(iterator it)
{
  NodeT * prev = it->prev_;
  NodeT * next = it->next_;
  alloc_.delete_object(it->node_);
  prev->next_ = next;
  next->prev_ = prev;
  --size_;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
void CircularDoublyLinkedList<ValueT, Alloc>::erase(iterator from, iterator to)
{
  while (from != to)
  {
    erase(from);
    ++from;
  }
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
ValueT & CircularDoublyLinkedList<ValueT, Alloc>::front()
{
  return node_->value_;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
const ValueT & CircularDoublyLinkedList<ValueT, Alloc>::front() const
{
  return node_->value_;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
ValueT & CircularDoublyLinkedList<ValueT, Alloc>::back()
{
  return node_->prev_->value_;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
const ValueT & CircularDoublyLinkedList<ValueT, Alloc>::back() const
{
  return node_->prev_->value_;
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
CircularDoublyLinkedList<ValueT, Alloc>::iterator CircularDoublyLinkedList<ValueT, Alloc>::begin()
{
  return iterator(node_, size_);
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
CircularDoublyLinkedList<ValueT, Alloc>::iterator CircularDoublyLinkedList<ValueT, Alloc>::end()
{
  return iterator(node_, std::max(size_-1, (std::size_t)1), size_);
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
void CircularDoublyLinkedList<ValueT, Alloc>::print() const
{
  NodeT * cur = node_;
  do
  {
    std::cout << cur->value_ << "->";
    cur = cur->next_;
  } while (cur != node_);
  std::cout << '\n';
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
void CircularDoublyLinkedList<ValueT, Alloc>::printR() const
{
  NodeT * cur = node_->prev_;
  do
  {
    std::cout << cur->value_ << "<-";
    cur = cur->prev_;
  } while (cur != node_->prev_);
  std::cout << '\n';
}
//----------------------------------------------------------------------------
#endif // CIRCULAR_DOUBLY_LINKED_LIST_HPP
//----------------------------------------------------------------------------