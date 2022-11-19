#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>
#include <iostream>

namespace stli {
template <class T>
class Vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  Vector() : m_size_(0U), m_capacity_(0U), arr_(nullptr) {}
  explicit Vector(size_type n)
      : m_size_(n), m_capacity_(n), arr_(n ? new T[n] : nullptr) {}
  Vector(std::initializer_list<value_type> const &items);
  Vector(const Vector &v);
  Vector(Vector &&v);
  ~Vector() { delete[] arr_; }
  Vector &operator=(const Vector &v);

  reference at(size_type i);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  value_type *data() { return arr_; }

  iterator begin() { return arr_; }
  iterator end() { return arr_ + m_size_; }

  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(value_type v);
  void pop_back();
  void swap(Vector &other);

  template <typename... Args>
  iterator emplace(iterator pos, Args &&...args);

  template <typename... Args>
  void emplace_back(Args &&...args);

  reference operator+(int n) { return *(arr_ += n); }
  reference operator-(int n) { return *(arr_ -= n); }
  reference operator++(int) { return *arr_++; }
  reference operator--(int) { return *arr_--; }
  reference operator++() { return *++arr_; }
  reference operator--() { return *--arr_; }
  bool operator!=(const iterator &it) { return arr_ != it.arr_; }
  bool operator==(const iterator &it) { return arr_ == it.arr_; }
  reference operator*() { return *arr_; }

 private:
  void reserve_more_capacity_(size_type size);
  void copy_vector_(const Vector &v);
  void move_vector_(Vector &v);

  size_t m_size_;
  size_t m_capacity_;
  value_type *arr_;
};
}  // namespace stli

#include "vector_impl.h"

#endif  // VECTOR_H
