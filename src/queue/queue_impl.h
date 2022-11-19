#ifndef QUEUE_IMPL
#define QUEUE_IMPL

#include "queue.h"

namespace stli {
template <typename T>
Queue<T>::Queue() : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
Queue<T>::Queue(std::initializer_list<value_type> const &items)
    : head_(nullptr), tail_(nullptr), size_(0) {
  for (auto it = items.begin(); it != items.end(); it++) {
    push(*it);
  }
}

template <typename T>
Queue<T>::Queue(const Queue &q) : head_(nullptr), tail_(nullptr), size_(0) {
  Node<int> *tmp = q.head_;
  while (tmp != nullptr) {
    push(tmp->data);
    tmp = tmp->next;
  }
}

template <typename T>
Queue<T>::Queue(Queue &&q) : head_(nullptr), tail_(nullptr), size_(0) {
  *this = std::move(q);
}

template <typename T>
Queue<T>::~Queue() {
  while (!empty()) pop();
}

template <typename T>
Queue<T> Queue<T>::operator=(Queue &&q) {
  if (this->head_ == q.head_ && this->tail_ == q.tail_) return *this;
  head_ = q.head_;
  q.head_ = nullptr;

  tail_ = q.tail_;
  q.tail_ = nullptr;

  size_ = q.size_;
  q.size_ = 0;
  return *this;
}

template <typename T>
typename Queue<T>::const_reference Queue<T>::front() const {
  if (tail_ == nullptr) throw std::out_of_range("Queue: Nothing in the front");
  return this->head_->data;
}

template <typename T>
typename Queue<T>::const_reference Queue<T>::back() const {
  if (tail_ == nullptr) throw std::out_of_range("Queue: Nothing in the back");
  return this->tail_->data;
}

template <typename T>
bool Queue<T>::empty() const {
  return this->size_ == 0;
}

template <typename T>
typename Queue<T>::size_type Queue<T>::size() const {
  return this->size_;
}

template <typename T>
void Queue<T>::push(const_reference data) {
  Node<T> *tmp = new Node<T>(data);
  size_++;
  if (tail_ == nullptr) {
    head_ = tail_ = tmp;
    return;
  }
  tail_->next = tmp;
  tail_ = tmp;
}

template <typename T>
void Queue<T>::pop() {
  if (empty()) throw std::out_of_range("Queue: Nothing to pop");
  size_--;
  Node<T> *tmp = head_;
  head_ = head_->next;
  if (head_ == nullptr) tail_ = nullptr;
  delete tmp;
}

template <typename T>
void Queue<T>::swap(Queue &other) {
  std::swap(this->head_, other.head_);
  std::swap(this->tail_, other.tail_);
  std::swap(this->size_, other.size_);
}

template <typename T>
template <typename... Args>
void Queue<T>::emplace_back(Args &&...args) {
  for (auto &i : {args...}) push(i);
}

}  // namespace stli

#endif  // QUEUE_IMPL
