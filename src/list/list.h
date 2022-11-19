#ifndef LIST
#define LIST

#include <initializer_list>
#include <iostream>

#include "../node.h"

namespace stli {
template <typename T>
class ListConstIterator;

template <typename T>
class List;
template <typename T>
class ListIterator {
 public:
  using self = ListIterator;
  using value_type = T;
  using reference = T &;
  using node_type = Node<T>;

  ListIterator();
  ListIterator(node_type *node);
  ~ListIterator();
  value_type operator*() const;
  self &operator++();
  self &operator--();
  self operator++(int);
  self operator--(int);
  bool operator==(const self &rhs) const;
  bool operator!=(const self &rhs) const;

 private:
  node_type *node;

  friend class ListConstIterator<T>;
  friend class List<T>;
};

template <typename T>
class ListConstIterator : public ListIterator<T> {
 public:
  using self = ListConstIterator;
  using iterator = ListIterator<T>;
  using value_type = T;
  using reference = T &;
  using node_type = Node<T>;

  ListConstIterator();
  ListConstIterator(const iterator &it);
  ListConstIterator(const node_type *node);
  ~ListConstIterator();
  iterator node_const_cast() const;

 private:
  const node_type *node;

  friend class List<T>;
};

template <typename T>
class List {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  using size_type = size_t;
  using node_type = Node<T>;

  List();
  List(size_type n);
  List(std::initializer_list<value_type> const &items);
  List(const List &l);
  List(List &&l);
  ~List();
  List operator=(List &&l);
  List operator=(const List &l);

  const_reference front() const;
  const_reference back() const;

  iterator begin() const;
  iterator end() const;

  bool empty() const;
  size_type size() const;

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(List &other);
  void merge(List &other);
  void splice(const_iterator pos, List &other);
  void reverse();
  void unique();
  void sort();

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);

  template <typename... Args>
  void emplace_back(Args &&...args);

  template <typename... Args>
  void emplace_front(Args &&...args);

 private:
  void move_node_(node_type **dest, node_type **source);
  node_type *end_ptr_;
  node_type *head_;
  size_type size_;
};
}  // namespace stli

#include "list_impl.h"

#endif  // LIST
