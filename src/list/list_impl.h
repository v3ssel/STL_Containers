#ifndef LIST_IMPL
#define LIST_IMPL

#include "list.h"
#include "list_iterator.h"

namespace stli {
template <typename T>
List<T>::List() : end_ptr_(new node_type(0)), head_(end_ptr_), size_(0) {}

template <typename T>
List<T>::List(size_type n)
    : end_ptr_(new node_type(0)), head_(end_ptr_), size_(0) {
  if (n == 0) return;
  do push_front(0);
  while (--n);
}

template <typename T>
List<T>::List(std::initializer_list<value_type> const &items)
    : end_ptr_(new node_type(0)), head_(end_ptr_), size_(0) {
  for (auto it = items.begin(); it != items.end(); it++) push_back(*it);
}

template <typename T>
List<T>::List(const List &l)
    : end_ptr_(new node_type(0)), head_(end_ptr_), size_(0) {
  for (auto it = l.begin(); it != l.end(); it++) push_back(*it);
}

template <typename T>
List<T>::List(List &&l)
    : end_ptr_(new node_type(0)), head_(end_ptr_), size_(0) {
  *this = std::move(l);
}

template <typename T>
List<T>::~List() {
  while (!empty()) pop_front();
  if (end_ptr_ != nullptr) delete end_ptr_;
}

template <typename T>
List<T> List<T>::operator=(List &&l) {
  this->head_ = l.head_;
  delete this->end_ptr_;
  this->end_ptr_ = l.end_ptr_;
  this->size_ = l.size_;

  l.head_ = nullptr;
  l.end_ptr_ = nullptr;
  l.size_ = 0;
  return *this;
}

template <typename T>
List<T> List<T>::operator=(const List &l) {
  for (auto it = l.begin(); it != l.end(); it++) {
    push_back(*it);
  }
  return *this;
}

template <typename T>
typename List<T>::const_reference List<T>::front() const {
  return head_->data;
}

template <typename T>
typename List<T>::const_reference List<T>::back() const {
  return end_ptr_->prev->data;
}

template <typename T>
typename List<T>::iterator List<T>::begin() const {
  return iterator(this->head_);
}

template <typename T>
typename List<T>::iterator List<T>::end() const {
  return iterator(this->end_ptr_);
}

template <typename T>
typename List<T>::size_type List<T>::size() const {
  return this->size_;
}

template <typename T>
bool List<T>::empty() const {
  return this->size_ == 0;
}

template <typename T>
void List<T>::clear() {
  for (auto it = begin(); it != end(); it++) {
    erase(it);
  }
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator pos,
                                           const_reference value) {
  if (pos == this->begin()) {
    push_front(value);
    return --pos;
  }
  node_type *n = new node_type(value);
  n->next = pos.node;
  n->prev = pos.node->prev;

  pos.node->prev->next = n;
  pos.node->prev = n;

  size_++;
  return --pos;
}

template <typename T>
void List<T>::erase(iterator pos) {
  if (pos == begin()) {
    pop_front();
    return;
  }
  if (pos == end()) {
    throw std::out_of_range("List: erase: Invalid position");
  }
  pos.node->prev->next = pos.node->next;
  pos.node->next->prev = pos.node->prev;
  delete pos.node;
  size_--;
}

template <typename T>
void List<T>::push_back(const_reference value) {
  if (head_ == end_ptr_) {
    push_front(value);
    return;
  }
  node_type *n = new node_type(value);

  n->next = end_ptr_;
  n->prev = end_ptr_->prev;

  end_ptr_->prev->next = n;
  end_ptr_->prev = n;

  size_++;
}

template <typename T>
void List<T>::pop_back() {
  if (empty()) throw std::out_of_range("List: pop_back: Nothing to pop");
  node_type *n = end_ptr_;
  end_ptr_ = end_ptr_->prev;
  end_ptr_->next = nullptr;
  delete n;
  size_--;
}

template <typename T>
void List<T>::push_front(const_reference value) {
  node_type *n = new node_type(value);
  n->next = head_;
  head_->prev = n;
  head_ = n;
  size_++;
}

template <typename T>
void List<T>::pop_front() {
  if (empty()) throw std::out_of_range("List: pop_front: Nothing to pop");
  node_type *n = head_;
  head_ = n->next;
  delete n;
  size_--;
}

template <typename T>
void List<T>::swap(List &other) {
  std::swap(this->end_ptr_, other.end_ptr_);
  std::swap(this->head_, other.head_);
  std::swap(this->size_, other.size_);
}

template <typename T>
void List<T>::merge(List &other) {
  node_type *result = nullptr;

  node_type **lastPtr = &result;
  node_type *endptr = nullptr;
  while (true) {
    if (this->head_ == this->end_ptr_) {
      *lastPtr = other.head_;
      endptr = other.end_ptr_;
      break;
    }
    if (other.head_ == other.end_ptr_) {
      *lastPtr = this->head_;
      endptr = this->end_ptr_;
      break;
    }
    if (this->head_->data <= other.head_->data) {
      move_node_(lastPtr, &this->head_);
    } else {
      move_node_(lastPtr, &other.head_);
    }
    lastPtr = &((*lastPtr)->next);
  }

  this->head_ = result;
  if (this->end_ptr_ != endptr) delete this->end_ptr_;
  this->end_ptr_ = endptr;
  this->size_ += other.size_;

  other.head_ = nullptr;
  other.size_ = 0;
  if (this->end_ptr_ == other.end_ptr_) other.end_ptr_ = nullptr;
}

template <typename T>
void List<T>::move_node_(node_type **dest, node_type **source) {
  node_type *new_node = *source;
  *source = new_node->next;

  new_node->next = *dest;
  *dest = new_node;
}

template <typename T>
void List<T>::splice(const_iterator pos, List &other) {
  iterator n_pos = pos.node_const_cast();

  if (pos != begin()) n_pos.node->prev->next = other.head_;
  if (pos != begin()) other.head_->prev = n_pos.node->prev;
  n_pos.node->prev = other.end_ptr_->prev;
  other.end_ptr_->prev->next = n_pos.node;

  if (pos == begin()) this->head_ = other.head_;
  this->size_ += other.size_;
  other.size_ = 0;

  other.head_ = nullptr;
  delete other.end_ptr_;
  other.end_ptr_ = nullptr;
}

template <typename T>
void List<T>::reverse() {
  List reversed;
  auto it = this->end();
  it--;
  for (; it != this->begin(); it--) reversed.push_back(*it);
  reversed.push_back(*it);
  this->clear();
  *this = std::move(reversed);
}

template <typename T>
void List<T>::unique() {
  for (auto it = begin(); it != end(); it++)
    if (it.node->data == it.node->next->data) erase(it);
}

template <typename T>
void List<T>::sort() {
  List<T> sorted;

  while (this->size() > 0) {
    auto largest_iter = this->begin();
    auto iter = largest_iter;

    for (; iter != this->end(); iter++)
      if (*iter > *largest_iter) largest_iter = iter;

    sorted.push_front(*largest_iter);
    this->erase(largest_iter);
  }
  *this = sorted;
}

template <typename T>
template <typename... Args>
typename List<T>::iterator List<T>::emplace(const_iterator pos,
                                            Args &&...args) {
  for (auto &i : {args...}) insert(pos, i);
  return pos.node_const_cast();
}

template <typename T>
template <typename... Args>
void List<T>::emplace_back(Args &&...args) {
  for (auto &i : {args...}) push_back(i);
}

template <typename T>
template <typename... Args>
void List<T>::emplace_front(Args &&...args) {
  for (auto &i : {args...}) push_front(i);
}
}  // namespace stli

#endif  // LIST_IMPL
