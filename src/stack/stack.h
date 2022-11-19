#ifndef STACK_H
#define STACK_H

#include <initializer_list>
#include <iostream>

#include "../node.h"

namespace stli {
template <typename T>
class Stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Stack();
  Stack(std::initializer_list<value_type> const &items);
  Stack(const Stack &s);
  Stack(Stack &&s);
  ~Stack();
  Stack operator=(Stack &&s);

  const_reference top() const;

  bool empty() const;
  size_type size() const;

  void push(const_reference value);
  void pop();
  void swap(Stack &other);
  void reverse();

  template <typename... Args>
  void emplace_front(Args &&...args);

 private:
  Node<T> *head_;
  size_type size_;
};
}  // namespace stli

#include "stack_impl.h"

#endif  //  STACK_H
