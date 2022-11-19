#ifndef MULTISET_H
#define MULTISET_H

#include <initializer_list>
#include <iostream>

#include "../set/set.h"

namespace stli {

template <class Key, typename T = int>
class Multiset : public Set<Key, T> {
 public:
  using value_type = Key;
  using reference = Key &;
  using const_reference = const Key &;
  using iterator = SetIterator<Key, T>;
  using size_type = size_t;

  Multiset() {}
  Multiset(std::initializer_list<value_type> const &items);
  Multiset(const Multiset &s);
  Multiset(Multiset &&s);
  Multiset &operator=(const Multiset &s);

  iterator insert(const value_type &value);

  size_type count(const Key &key);
  std::pair<iterator, iterator> equal_range(const Key &key);
  iterator lower_bound(const Key &key);
  iterator upper_bound(const Key &key);

 private:
  size_type multicount(tree_element_<Key, T> *current, const Key &key);
};
}  // namespace stli

#include "multiset_impl.h"

#endif  // MULTISET_H
