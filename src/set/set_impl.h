#ifndef SET_IMPL
#define SET_IMPL

#include "set.h"

namespace stli {

template <typename Key, typename T>
tree_element_<Key, T> *Set<Key, T>::create_tree_element(Key new_value) {
  tree_element_<Key, T> *elem = new tree_element_<Key, T>;
  elem->values = std::make_pair(new_value, T());
  elem->left = nullptr;
  elem->right = nullptr;
  elem->back = nullptr;
  return elem;
}

template <typename Key, typename T>
void Set<Key, T>::copy_Set(tree_element_<Key, T> *current) {
  insert(current->values.first);
  if (current->left != nullptr) {
    copy_Set(current->left);
  }
  if (current->right != nullptr) {
    copy_Set(current->right);
  }
}

template <typename Key, typename T>
void Set<Key, T>::clear_Set(tree_element_<Key, T> *current) {
  if (current) {
    if (current->left) {
      clear_Set(current->left);
    }
    if (current->right) {
      clear_Set(current->right);
    }
    this->obnul(current);
    delete current;
  }
}

template <typename Key, typename T>
Set<Key, T>::Set(std::initializer_list<value_type> const &items) {
  for (auto it = items.begin(); it != items.end(); it++) insert(*it);
}

template <typename Key, typename T>
Set<Key, T>::Set(const Set &s) {
  copy_Set(s.head_);
}

template <class Key, typename T>
Set<Key, T>::Set(Set &&s) {
  this->head_ = s.head_;
  s.head_ = nullptr;
}

template <typename Key, typename T>
Set<Key, T>::~Set() {
  clear_Set(this->head_);
  delete this->find_;
}

template <typename Key, typename T>
Set<Key, T> &Set<Key, T>::operator=(const Set &s) {
  copy_Set(s.head_);
  return *this;
}

template <typename Key, typename T>
typename Set<Key, T>::iterator Set<Key, T>::begin() {
  iterator cur(this->head_);
  while (cur.elem->left) {
    cur.elem = cur.elem->left;
  }
  end();
  return cur;
}

template <typename Key, typename T>
typename Set<Key, T>::iterator Set<Key, T>::end() {
  iterator cur(this->head_);
  while (cur.elem->right) {
    cur.elem = cur.elem->right;
  }
  if (!this->end_) {
    this->end_ = new tree_element_<Key, T>;
    this->end_->left = nullptr;
    this->end_->right = nullptr;
  } else {
    cur.elem = cur.elem->back;
  }
  cur.elem->right = this->end_;
  this->end_->back = cur.elem;
  return this->end_;
}

template <typename Key, typename T>
void Set<Key, T>::clear() {
  iterator x = begin();
  for (; x != end(); ++x) this->erase(x);
}

template <typename Key, typename T>
std::pair<typename Set<Key, T>::iterator, bool> Set<Key, T>::insert(
    const Key &value) {
  bool insertion = false;
  if (this->head_ == nullptr) {
    this->head_ = create_tree_element(value);
    this->find_ = create_tree_element(Key());
    insertion = true;
  } else {
    if (!contains(value)) {
      insertion = true;
      tree_element_<Key, T> *el = create_tree_element(value);
      this->insert_into_tree(this->head_, el);
    }
  }
  return std::make_pair(iterator(this->search_value(this->head_, value)),
                        insertion);
}

template <typename Key, typename T>
void Set<Key, T>::swap(Set &other) {
  std::swap(this->head_, other.head_);
  std::swap(this->end_, other.end_);
  std::swap(this->find_, other.find_);
}

template <typename Key, typename T>
void Set<Key, T>::merge(Set &other) {
  this->insert_into_tree(this->head_, other.head_);
  other.head_ = nullptr;
}

template <typename Key, typename T>
typename Set<Key, T>::iterator Set<Key, T>::find(const Key &key) {
  iterator x(this->search_value(this->head_, key));
  return x;
}

template <typename Key, typename T>
bool Set<Key, T>::contains(const Key &key) {
  return find(key).elem != this->find_;
}

template <typename Key, typename T>
template <typename... Args>
std::vector<std::pair<typename Set<Key, T>::iterator, bool>>
Set<Key, T>::emplace(Args &&...args) {
  std::vector<std::pair<iterator, bool>> result;

  for (auto &i : {args...}) result.push_back(insert(i));
  return result;
}
}  // namespace stli

#endif  // SET_IMPL
