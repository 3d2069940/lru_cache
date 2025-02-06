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
  CircularDoublyLinkedList() = delete;
  CircularDoublyLinkedList(const CircularDoublyLinkedList &) = delete;
  CircularDoublyLinkedList(CircularDoublyLinkedList &&) = delete;
  CircularDoublyLinkedList & operator=(const CircularDoublyLinkedList &) = delete;
  CircularDoublyLinkedList & operator=(CircularDoublyLinkedList &&) = delete;
  CircularDoublyLinkedList(std::initializer_list<ValueT> init, const Alloc & alloc = Alloc());
  ~CircularDoublyLinkedList();
//----------------------------------------------------------------------------
  ValueT & front();
  const ValueT & front() const;
//----------------------------------------------------------------------------
  ValueT & back();
  const ValueT & back() const;
//----------------------------------------------------------------------------
  void print() const;
  void printR() const;
//----------------------------------------------------------------------------
private:
  Alloc         alloc_;
  NodeT       * node_;
  std::size_t   size_;
//----------------------------------------------------------------------------
}; // class CircularDoublyLinkedList
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
CircularDoublyLinkedList<ValueT, Alloc>::CircularDoublyLinkedList(std::initializer_list<ValueT> init, const Alloc & alloc) :
  alloc_(alloc),
  size_(init.size())
{
  assert(size_ > 0);
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
  NodeT * cur  = node_;
  NodeT * next = nullptr;
  do
  {
    cur->prev_->next_ = nullptr;
    next = cur->next_;
    alloc_.delete_object(cur);
    cur = next;
  } while (cur != nullptr);
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
void CircularDoublyLinkedList<ValueT, Alloc>::print() const
{
  NodeT * cur = node_;
  std::cout << "<->" << cur->value_ << "<->";
  cur = node_->next_;
  while (cur != node_)
  {
    std::cout << cur->value_ << "<->";
    cur = cur->next_;
  }
  std::cout << '\n';
}
//----------------------------------------------------------------------------
template<class ValueT, class Alloc>
void CircularDoublyLinkedList<ValueT, Alloc>::printR() const
{
  NodeT * cur = node_;
  std::cout << "<->" << cur->value_ << "<->";
  cur = node_->prev_;
  while (cur != node_)
  {
    std::cout << cur->value_ << "<->";
    cur = cur->prev_;
  }
  std::cout << '\n';
}
//----------------------------------------------------------------------------
#endif // CIRCULAR_DOUBLY_LINKED_LIST_HPP
//----------------------------------------------------------------------------