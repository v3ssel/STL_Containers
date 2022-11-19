#ifndef LIST_ITERATOR
#define LIST_ITERATOR

#include "list.h"

template <typename T>
stli::ListIterator<T>::ListIterator() : node(nullptr) {}

template <typename T>
stli::ListIterator<T>::ListIterator(Node<T> *n_node) : node(n_node) {}

template <typename T>
stli::ListIterator<T>::~ListIterator() {
  this->node = nullptr;
}

template <typename T>
typename stli::ListIterator<T>::value_type stli::ListIterator<T>::operator*()
    const {
  return node->data;
}

template <typename T>
typename stli::ListIterator<T>::self &stli::ListIterator<T>::operator++() {
  node = node->next;
  return *this;
}

template <typename T>
typename stli::ListIterator<T>::self &stli::ListIterator<T>::operator--() {
  node = node->prev;
  return *this;
}

template <typename T>
typename stli::ListIterator<T>::self stli::ListIterator<T>::operator++(int) {
  self tmp = *this;
  node = node->next;
  return tmp;
}

template <typename T>
typename stli::ListIterator<T>::self stli::ListIterator<T>::operator--(int) {
  self tmp = *this;
  node = node->prev;
  return tmp;
}

template <typename T>
bool stli::ListIterator<T>::operator==(const self &rhs) const {
  return this->node == rhs.node;
}

template <typename T>
bool stli::ListIterator<T>::operator!=(const self &rhs) const {
  return !(this->node == rhs.node);
}

template <typename T>
stli::ListConstIterator<T>::ListConstIterator()
    : iterator(nullptr), node(nullptr) {}

template <typename T>
stli::ListConstIterator<T>::ListConstIterator(const iterator &it)
    : iterator(it.node), node(it.node) {}

template <typename T>
stli::ListConstIterator<T>::ListConstIterator(const Node<T> *n_node)
    : iterator(n_node), node(n_node) {}

template <typename T>
stli::ListConstIterator<T>::~ListConstIterator() {
  this->node = nullptr;
}

template <typename T>
typename stli::ListConstIterator<T>::iterator
stli::ListConstIterator<T>::node_const_cast() const {
  return iterator(const_cast<Node<T> *>(node));
}

#endif  // LIST_ITERATOR
