#ifndef TREE_H
#define TREE_H

namespace stli {
template <typename Key, typename T>
class tree_element_;

template <typename Key, typename T>
class MainIterator {
 public:
  MainIterator<Key, T> &operator++();
  MainIterator<Key, T> &operator--();
  bool operator!=(const MainIterator<Key, T> &it) { return elem != it.elem; }
  bool operator==(const MainIterator<Key, T> &it) { return elem == it.elem; }

  MainIterator() : elem(nullptr) {}
  MainIterator(tree_element_<Key, T> *current) : elem(current) {}

  tree_element_<Key, T> *elem;
};

template <typename Key, typename T>
MainIterator<Key, T> &MainIterator<Key, T>::operator++() {
  if (elem->right) {
    elem = elem->right;
    while (elem->left) elem = elem->left;
  } else {
    if (elem->back->back && elem->back->right == elem) {
      while (elem == elem->back->right) elem = elem->back;
      elem = elem->back;
    } else {
      elem = elem->back;
    }
  }
  return *this;
}

template <typename Key, typename T>
MainIterator<Key, T> &MainIterator<Key, T>::operator--() {
  if (elem->left) {
    elem = elem->left;
    while (elem->right) elem = elem->right;
  } else {
    if (elem->back->back && elem->back->left == elem) {
      while (elem == elem->back->left) elem = elem->back;
      elem = elem->back;
    } else {
      elem = elem->back;
    }
  }
  return *this;
}

template <typename Key, typename T>
class Tree {
 public:
  using size_type = size_t;
  using iterator = MainIterator<Key, T>;
  void insert_into_tree(tree_element_<Key, T> *head,
                        tree_element_<Key, T> *current);
  void balance_tree(tree_element_<Key, T> *current);
  void balance_tree_head(tree_element_<Key, T> *current);
  void obnul(tree_element_<Key, T> *current);
  void erase(iterator pos);

  int counter(tree_element_<Key, T> *current);
  int counter_left(tree_element_<Key, T> *current);
  int counter_right(tree_element_<Key, T> *current);

  tree_element_<Key, T> *search_value(tree_element_<Key, T> *head,
                                      const Key &key);
  size_type size();
  bool empty();

  Tree() : head_(nullptr), end_(nullptr), find_(nullptr) {}

 protected:
  tree_element_<Key, T> *head_, *end_, *find_;
  int count_ = 0;
};

template <typename Key, typename T>
void Tree<Key, T>::insert_into_tree(tree_element_<Key, T> *head,
                                    tree_element_<Key, T> *current) {
  if (current->values.first < head->values.first ||
      (current->values.first == head->values.first && count_ == 0)) {
    if (head->left == nullptr) {
      head->left = current;
      current->back = head;
      count_ = 1;
    } else {
      count_ = 1;
      insert_into_tree(head->left, current);
    }
  } else {
    if (head->right == nullptr) {
      head->right = current;
      current->back = head;
      count_ = 0;
    } else {
      count_ = 0;
      insert_into_tree(head->right, current);
    }
  }
  balance_tree(head_);
  balance_tree_head(head_);
}

template <typename Key, typename T>
void Tree<Key, T>::balance_tree(tree_element_<Key, T> *current) {
  if ((current->left && current->right) || current == head_) {
    if (current->left) balance_tree(current->left);
    if (current->right) balance_tree(current->right);
  } else if (current->left) {
    if (current->left->left || current->left->right) {
      if (current->back->right == current) {
        current->back->right = current->left;
      } else {
        current->back->left = current->left;
      }
      current->left->back = current->back;
      obnul(current);
      insert_into_tree(head_, current);
    }
  } else if (current->right) {
    if (current->right->left || current->right->right) {
      if (current->back->left == current) {
        current->back->left = current->right;
      } else {
        current->back->right = current->right;
      }
      current->right->back = current->back;
      obnul(current);
      insert_into_tree(head_, current);
    }
  }
}

template <typename Key, typename T>
void Tree<Key, T>::balance_tree_head(tree_element_<Key, T> *current) {
  if ((counter_left(current) - counter_right(current)) < -2) {
    if (head_ != current) {
      if (current->back->left == current) {
        current->back->left = current->right;
      } else {
        current->back->right = current->right;
      }
      current->right->back = current->back;
    } else {
      head_ = current->right;
    }
    current->right = nullptr;
    insert_into_tree(head_, current);
  } else if ((counter_left(current) - counter_right(current)) > 2) {
    if (head_ != current) {
      if (current->back->right == current) {
        current->back->right = current->left;
      } else {
        current->back->left = current->left;
      }
      current->left->back = current->back;
    } else {
      head_ = current->left;
    }
    current->left = nullptr;
    insert_into_tree(head_, current);
  } else {
    if (current->left != nullptr) balance_tree_head(current->left);
    if (current->right != nullptr) balance_tree_head(current->right);
  }
}

template <typename Key, typename T>
void Tree<Key, T>::obnul(tree_element_<Key, T> *current) {
  current->left = nullptr;
  current->right = nullptr;
  current->back = nullptr;
}

template <typename Key, typename T>
int Tree<Key, T>::counter(tree_element_<Key, T> *current) {
  if (current == nullptr) return 0;
  return 1 + counter(current->left) + counter(current->right);
}

template <typename Key, typename T>
int Tree<Key, T>::counter_left(tree_element_<Key, T> *current) {
  current = current->left;
  if (current == nullptr) return 0;
  return 1 + counter(current->left) + counter(current->right);
}

template <typename Key, typename T>
int Tree<Key, T>::counter_right(tree_element_<Key, T> *current) {
  current = current->right;
  if (current == nullptr) return 0;
  return 1 + counter(current->left) + counter(current->right);
}

template <typename Key, typename T>
tree_element_<Key, T> *Tree<Key, T>::search_value(tree_element_<Key, T> *head,
                                                  const Key &key) {
  if (key < head->values.first) {
    if (head->left) head = search_value(head->left, key);
  }
  if (key > head->values.first) {
    if (head->right) head = search_value(head->right, key);
  }
  if (key == head->values.first) {
    return head;
  } else {
    head = find_;
  }
  return head;
}

template <typename Key, typename T>
typename Tree<Key, T>::size_type Tree<Key, T>::size() {
  auto s = counter(head_);
  return end_ && s ? s - 1 : s;
}

template <typename Key, typename T>
bool Tree<Key, T>::empty() {
  return size() == 0;
}

template <typename Key, typename T>
void Tree<Key, T>::erase(iterator pos) {
  if (pos.elem != head_) {
    if (pos.elem->back->left == pos.elem)
      pos.elem->back->left = nullptr;
    else
      pos.elem->back->right = nullptr;
    if (pos.elem->left) insert_into_tree(head_, pos.elem->left);
    if (pos.elem->right) insert_into_tree(head_, pos.elem->right);
  } else {
    if (pos.elem->left) {
      head_ = pos.elem->left;
      if (pos.elem->right) insert_into_tree(head_, pos.elem->right);
    } else if (pos.elem->right) {
      head_ = pos.elem->right;
      if (pos.elem->left) insert_into_tree(head_, pos.elem->left);
    }
  }
  delete pos.elem;
  pos.elem = nullptr;
}
}  // namespace stli

#endif  // TREE_H
