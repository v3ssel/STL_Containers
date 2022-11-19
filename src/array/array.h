#ifndef ARRAY_H
#define ARRAY_H

#include <initializer_list>
#include <iostream>

namespace stli {
template <class T, size_t S>
class Array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  Array() : m_size_(S) {}
  Array(std::initializer_list<value_type> const &items);
  Array(const Array &v);
  Array(Array &&v);
  Array &operator=(const Array &v);

  reference at(size_type i);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  value_type *data() { return arr_; };

  iterator begin() { return arr_; }
  iterator end() { return arr_ + m_size_; }

  bool empty();
  size_type size();
  size_type max_size();

  void swap(Array &other);
  void fill(const_reference value);

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
  void copy_array_(const Array &v);
  void move_array_(Array &v);

  size_type m_size_ = S;
  value_type arr_[S];
};
}  // namespace stli

#include "array_impl.h"

#endif  // ARRAY_H
