#ifndef MAP_IMPL
#define MAP_IMPL

#include "map.h"

namespace stli {
template <typename Key, typename T>
tree_element_<Key, T>::tree_element_(Key k, T val)
    : values(std::make_pair(k, val)),
      back(nullptr),
      left(nullptr),
      right(nullptr) {}

template <typename Key, typename T>
Map<Key, T>::Map() {}

template <typename Key, typename T>
Map<Key, T>::Map(std::initializer_list<value_type> const &items) {
  for (auto it = items.begin(); it != items.end(); it++) insert(*it);
}

template <typename Key, typename T>
Map<Key, T>::Map(Map &m) {
  *this = m;
}

template <typename Key, typename T>
Map<Key, T> &Map<Key, T>::operator=(Map &m) {
  this->clear();
  for (auto it = m.begin(); it != m.end(); ++it) insert(*it);
  return *this;
}

template <typename Key, typename T>
Map<Key, T>::Map(Map &&m) {
  *this = std::move(m);
}

template <typename Key, typename T>
Map<Key, T> &Map<Key, T>::operator=(Map &&m) {
  this->clear();
  this->head_ = m.head_;
  this->end_ = m.end_;
  this->find_ = m.find_;

  m.head_ = nullptr;
  m.end_ = nullptr;
  m.find_ = nullptr;
  return *this;
}

template <typename Key, typename T>
Map<Key, T>::~Map() {
  clear();
}

template <typename Key, typename T>
typename Map<Key, T>::mapped_type &Map<Key, T>::at(const Key &key) {
  auto found = this->search_value(this->head_, key);
  if (found == this->find_) throw std::out_of_range("Map: at: out of range");
  return found->values.second;
}

template <typename Key, typename T>
typename Map<Key, T>::mapped_type &Map<Key, T>::operator[](const Key &key) {
  return this->search_value(this->head_, key)->values.second;
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::begin() {
  iterator cur(this->head_);
  if (this->head_ != nullptr) {
    while (cur.elem->left) {
      cur.elem = cur.elem->left;
    }
    end();
  }
  return cur;
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::end() {
  if (this->head_ != nullptr) {
    iterator cur(this->head_);
    while (cur.elem->right) {
      cur.elem = cur.elem->right;
    }
    if (!this->end_) {
      this->end_ = new tree_type;
      this->end_->left = nullptr;
      this->end_->right = nullptr;
    } else {
      cur.elem = cur.elem->back;
    }
    cur.elem->right = this->end_;
    this->end_->back = cur.elem;
  }
  return this->end_;
}

template <typename Key, typename T>
void Map<Key, T>::clear() {
  for (auto it = begin(); it != end(); ++it) erase(it);

  delete this->head_;
  delete this->find_;
  this->head_ = nullptr;
  this->find_ = nullptr;
  this->end_ = nullptr;
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(
    const value_type &value) {
  bool insertion = false;
  if (this->head_ == nullptr) {
    this->head_ = new tree_type(value.first, value.second);
    this->find_ = new tree_type(Key(), T());
    insertion = true;
  } else {
    if (!contains(value.first)) {
      insertion = true;
      tree_type *el = new tree_type(value.first, value.second);
      this->insert_into_tree(this->head_, el);
    }
  }
  return std::make_pair(iterator(this->search_value(this->head_, value.first)),
                        insertion);
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(
    const Key &key, const T &obj) {
  return insert(std::make_pair(key, obj));
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert_or_assign(
    const Key &key, const T &obj) {
  if (!this->empty() && contains(key)) {
    at(key) = obj;
  } else {
    return insert(std::make_pair(key, obj));
  }
  return std::make_pair(iterator(this->search_value(this->head_, key)), false);
}

template <typename Key, typename T>
void Map<Key, T>::erase(iterator pos) {
  Tree<Key, T>::erase(pos);
}

template <typename Key, typename T>
void Map<Key, T>::swap(Map<Key, T> &other) {
  std::swap(this->head_, other.head_);
  std::swap(this->end_, other.end_);
  std::swap(this->find_, other.find_);
}

template <typename Key, typename T>
void Map<Key, T>::merge(Map<Key, T> &other) {
  if (other.end_ != nullptr) {
    other.end_->back->right = nullptr;
    delete other.end_;
  }
  this->insert_into_tree(this->head_, other.head_);
  other.head_ = nullptr;
  other.end_ = nullptr;

  delete other.find_;
  other.find_ = nullptr;
}

template <typename Key, typename T>
bool Map<Key, T>::contains(const Key &key) {
  try {
    at(key);
  } catch (...) {
    return false;
  }
  return true;
}

template <typename Key, typename T>
template <typename... Args>
std::vector<std::pair<typename Map<Key, T>::iterator, bool>>
Map<Key, T>::emplace(Args &&...args) {
  std::vector<std::pair<iterator, bool>> result;

  for (auto &i : {args...}) result.push_back(insert(i));
  return result;
}
}  // namespace stli

#endif  // MAP_IMPL
