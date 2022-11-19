#ifndef MULTISET_IMPL
#define MULTISET_IMPL

#include "multiset.h"

namespace stli {

template <typename Key, typename T>
Multiset<Key, T>::Multiset(std::initializer_list<value_type> const &items) {
  for (auto it = items.begin(); it != items.end(); it++) this->insert(*it);
}

template <class Key, typename T>
Multiset<Key, T>::Multiset(Multiset &&s) {
  this->head_ = s.head_;
  s.head_ = nullptr;
}

template <typename Key, typename T>
Multiset<Key, T> &Multiset<Key, T>::operator=(const Multiset &s) {
  this->copy_set(s.head_);
  return *this;
}

template <typename Key, typename T>
typename Multiset<Key, T>::iterator Multiset<Key, T>::insert(
    const value_type &value) {
  if (this->head_ == nullptr) {
    this->head_ = this->create_tree_element(value);
    this->find_ = this->create_tree_element(Key());
  } else {
    tree_element_<Key, T> *el = this->create_tree_element(value);
    this->insert_into_tree(this->head_, el);
  }
  return iterator(this->head_);
}

template <typename Key, typename T>
typename Multiset<Key, T>::size_type Multiset<Key, T>::count(const Key &key) {
  auto s = multicount(this->head_, key);
  return this->end_ && s ? s - 1 : s;
}

template <typename Key, typename T>
typename Multiset<Key, T>::size_type Multiset<Key, T>::multicount(
    tree_element_<Key, T> *current, const Key &key) {
  size_type res = 0;
  if (current == nullptr) return 0;
  if (current->values.first == key) res = 1;
  return res + multicount(current->left, key) + multicount(current->right, key);
}

template <typename Key, typename T>
typename Multiset<Key, T>::iterator Multiset<Key, T>::lower_bound(
    const Key &key) {
  iterator x(this->begin());
  iterator end(this->end());
  --end;
  if (*end < key) {
    x = this->end();
  } else {
    while (*x < key) ++x;
  }
  return x;
}

template <typename Key, typename T>
typename Multiset<Key, T>::iterator Multiset<Key, T>::upper_bound(
    const Key &key) {
  iterator x(this->begin());
  iterator end(this->end());
  --end;
  if (*end < key) {
    x = this->end();
  } else {
    while (*x <= key) ++x;
  }
  return x;
}

template <typename Key, typename T>
std::pair<SetIterator<Key, T>, SetIterator<Key, T>>
Multiset<Key, T>::equal_range(const Key &key) {
  return std::make_pair(lower_bound(key), upper_bound(key));
}
}  // namespace stli

#endif  // MULTISET_IMPL
