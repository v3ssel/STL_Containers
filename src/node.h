#ifndef NODE_H
#define NODE_H

namespace stli {
template <typename T>
class Node {
 public:
  T data;
  Node *next;
  Node *prev;

  Node(T n) : data(n), next(nullptr), prev(nullptr) {}
};
}  // namespace stli

#endif  // NODE_H
