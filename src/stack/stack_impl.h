#ifndef STACK_IMPL
#define STACK_IMPL

#include "stack.h"

namespace stli {
template <typename T>
Stack<T>::Stack() : head_(nullptr), size_(0) {}

template <typename T>
Stack<T>::Stack(std::initializer_list<value_type> const &items)
    : head_(nullptr), size_(0) {
  for (auto it = items.begin(); it != items.end(); it++) push(*it);
}

template <typename T>
Stack<T>::Stack(const Stack &s) : head_(nullptr), size_(0) {
  Node<T> *ptr = s.head_;
  while (ptr != nullptr) {
    push(ptr->data);
    ptr = ptr->next;
  }
  reverse();
}

template <typename T>
Stack<T>::Stack(Stack &&s) : head_(nullptr), size_(0) {
  *this = std::move(s);
}

template <typename T>
Stack<T>::~Stack() {
  while (!empty()) pop();
}

template <typename T>
Stack<T> Stack<T>::operator=(Stack &&s) {
  this->head_ = s.head_;
  this->size_ = s.size_;
  s.head_ = nullptr;
  s.size_ = 0;
  return *this;
}

template <typename T>
void Stack<T>::push(const_reference value) {
  Node<T> *node = new Node<T>(value);
  node->data = value;
  node->next = this->head_;
  this->head_ = node;
  size_++;
}

template <typename T>
void Stack<T>::pop() {
  if (empty()) throw std::out_of_range("Stack: Nothing to pop");
  Node<T> *tmp = head_;
  head_ = head_->next;
  delete tmp;
  size_--;
}

template <typename T>
void Stack<T>::swap(Stack &other) {
  std::swap(this->head_, other.head_);
  std::swap(this->size_, other.size_);
}

template <typename T>
void Stack<T>::reverse() {
  Node<T> *prev, *cur, *succ;
  cur = prev = head_;
  cur = cur->next;
  prev->next = NULL;
  while (cur != NULL) {
    succ = cur->next;
    cur->next = prev;
    prev = cur;
    cur = succ;
  }
  head_ = prev;
}

template <typename T>
template <typename... Args>
void Stack<T>::emplace_front(Args &&...args) {
  for (auto &i : {args...}) push(i);
}

template <typename T>
typename Stack<T>::const_reference Stack<T>::top() const {
  if (empty()) throw std::out_of_range("Stack: Nothing to show");
  return head_->data;
}

template <typename T>
typename Stack<T>::size_type Stack<T>::size() const {
  return this->size_;
}

template <typename T>
bool Stack<T>::empty() const {
  return this->size_ == 0;
}
}  // namespace stli

#endif  // STACK_IMPL
