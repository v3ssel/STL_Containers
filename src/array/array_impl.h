#ifndef ARRAY_IMPL
#define ARRAY_IMPL

#include "array.h"

namespace stli {

template <typename T, size_t S>
void Array<T, S>::copy_array_(const Array &v) {
  for (size_t i = 0; i < m_size_; i++) arr_[i] = v.arr_[i];
}

template <typename T, size_t S>
void Array<T, S>::move_array_(Array &v) {
  copy_array_(v);
}

template <typename T, size_t S>
Array<T, S>::Array(std::initializer_list<value_type> const &items) {
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    arr_[i] = *it;
    i++;
  }
  if (i > (int)S) throw std::out_of_range("error: too many initializers");
}

template <typename T, size_t S>
Array<T, S>::Array(const Array &v) {
  copy_array_(v);
}

template <typename T, size_t S>
Array<T, S>::Array(Array &&v) {
  move_array_(v);
}

template <typename T, size_t S>
Array<T, S> &Array<T, S>::operator=(const Array &v) {
  copy_array_(v);
  return *this;
}

template <typename T, size_t S>
typename Array<T, S>::reference Array<T, S>::at(size_type i) {
  if (i >= size()) throw std::out_of_range("Out of range");
  return arr_[i];
}

template <typename T, size_t S>
typename Array<T, S>::reference Array<T, S>::operator[](size_type pos) {
  return arr_[pos];
}

template <typename T, size_t S>
typename Array<T, S>::const_reference Array<T, S>::front() {
  return arr_[0];
}

template <typename T, size_t S>
typename Array<T, S>::const_reference Array<T, S>::back() {
  return arr_[m_size_ - 1];
}

template <typename T, size_t S>
bool Array<T, S>::empty() {
  return m_size_ == 0;
}

template <typename T, size_t S>
typename Array<T, S>::size_type Array<T, S>::size() {
  return m_size_;
}

template <typename T, size_t S>
typename Array<T, S>::size_type Array<T, S>::max_size() {
  return S;
}

template <typename T, size_t S>
void Array<T, S>::swap(Array &other) {
  Array<T, S> loc = std::move(other);
  other.move_array_(*this);
  move_array_(loc);
}

template <typename T, size_t S>
void Array<T, S>::fill(const_reference value) {
  for (size_t i = 0; i < m_size_; i++) arr_[i] = value;
}
}  // namespace stli

#endif  // ARRAY_IMPL
