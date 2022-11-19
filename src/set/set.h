#ifndef SET_H
#define SET_H

#include <initializer_list>
#include <iostream>
#include <vector>

#include "../tree.h"

namespace stli {
template <class Key, typename T>
class Set;
template <class Key, typename T>
class SetIterator;

template <typename Key, typename T>
class tree_element_ {
 public:
  std::pair<Key, T> values;
  tree_element_<Key, T> *left, *right, *back;

  friend Set<Key, T>;
  friend SetIterator<Key, T>;
};

template <class Key, typename T>
class SetIterator : public MainIterator<Key, T> {
 public:
  SetIterator(tree_element_<Key, T> *current) { this->elem = current; }
  Key &operator*() { return this->elem->values.first; }

  friend Set<Key, T>;
};

template <class Key, typename T = int>
class Set : public Tree<Key, T> {
 public:
  using value_type = Key;
  using reference = Key &;
  using const_reference = const Key &;
  using iterator = SetIterator<Key, T>;
  using size_type = size_t;

  Set() {}
  Set(std::initializer_list<value_type> const &items);
  Set(const Set &s);
  Set(Set &&s);
  ~Set();
  Set &operator=(const Set &s);

  iterator begin();
  iterator end();

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void swap(Set &other);
  void merge(Set &other);

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args &&...args);

  iterator find(const Key &key);
  bool contains(const Key &key);

 protected:
  tree_element_<Key, T> *create_tree_element(Key new_value);
  void copy_Set(tree_element_<Key, T> *current);
  void clear_Set(tree_element_<Key, T> *current);
};
}  // namespace stli

#include "set_impl.h"

#endif  // SET_H
