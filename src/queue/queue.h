#ifndef QUEUE
#define QUEUE

#include "../node.h"

namespace stli {
template <typename T>
class Queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Queue();
  Queue(std::initializer_list<value_type> const &items);
  Queue(const Queue &q);
  Queue(Queue &&q);
  ~Queue();
  Queue operator=(Queue &&q);

  const_reference front() const;
  const_reference back() const;

  bool empty() const;
  size_type size() const;

  void push(const_reference value);
  void pop();
  void swap(Queue &other);

  template <typename... Args>
  void emplace_back(Args &&...args);

 private:
  Node<T> *head_, *tail_;
  size_type size_;
};
}  // namespace stli

#include "queue_impl.h"

#endif  //  QUEUE
