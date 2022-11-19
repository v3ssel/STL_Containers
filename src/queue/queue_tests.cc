#include <gtest/gtest.h>

#include "Queue.h"

namespace stli {
TEST(Constructors, Default) {
  Queue<int> q;
  EXPECT_EQ(q.empty(), true);
}

TEST(Constructors, InitList) {
  Queue<int> q = {1, 2, 3, 4, 5};
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 5);
  EXPECT_EQ(q.size(), 5);
}

TEST(Constructors, Copy) {
  Queue<int> q = {5, 3, 1, 9, 6, 7};
  Queue<int> second = q;

  EXPECT_EQ(second.front(), 5);
  EXPECT_EQ(second.back(), 7);
  EXPECT_EQ(second.size(), 6);
}

TEST(Constructors, Move) {
  Queue<int> q = {5, 3, 1, 9, 6, 7};
  Queue<int> second(std::move(q));

  EXPECT_EQ(q.size(), 0);
  EXPECT_EQ(second.front(), 5);
  EXPECT_EQ(second.back(), 7);
  EXPECT_EQ(second.size(), 6);
}

TEST(Constructors, OperatorMove) {
  Queue<int> q = {5, 3, 1, 9, 6, 7};
  Queue<int> second;
  second = std::move(q);

  EXPECT_EQ(q.size(), 0);
  EXPECT_EQ(second.front(), 5);
  EXPECT_EQ(second.back(), 7);
  EXPECT_EQ(second.size(), 6);

  second = std::move(second);
  EXPECT_EQ(second.front(), 5);
  EXPECT_EQ(second.back(), 7);
  EXPECT_EQ(second.size(), 6);
}

TEST(Queue, ElementAccess) {
  Queue<int> q = {111, 222, 333, 444, 555, 666};
  EXPECT_EQ(q.front(), 111);
  EXPECT_EQ(q.back(), 666);
  q.pop();
  EXPECT_EQ(q.front(), 222);
  q.push(777);
  EXPECT_EQ(q.back(), 777);
}

TEST(Queue, Capacity) {
  Queue<int> q;
  EXPECT_EQ(q.empty(), true);
  EXPECT_EQ(q.size(), 0);
  q.push(1);
  q.push(2);
  EXPECT_EQ(q.empty(), false);
  EXPECT_EQ(q.size(), 2);
}

TEST(QueueModifiers, Push) {
  Queue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);
  q.push(4);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 4);
}

TEST(QueueModifiers, Pop) {
  Queue<int> q;
  q.push(11);
  q.push(22);
  q.push(33);
  q.pop();
  q.pop();
  EXPECT_EQ(q.front(), 33);
  EXPECT_EQ(q.back(), 33);

  q.pop();
  EXPECT_ANY_THROW(q.pop());
}

TEST(QueueModifiers, Swap) {
  Queue<int> q = {10, 20, 30, 40};
  Queue<int> second = {1, 2, 3, 4, 5, 6, 7, 8};

  q.swap(second);

  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 8);
  EXPECT_EQ(q.size(), 8);

  EXPECT_EQ(second.front(), 10);
  EXPECT_EQ(second.back(), 40);
  EXPECT_EQ(second.size(), 4);
}

TEST(QueueModifiers, EmplaceBack) {
  Queue<int> q = {10, 20, 30, 40};
  q.emplace_back(1, 2, 3, 4, 5, 6, 7, 8);

  EXPECT_EQ(q.front(), 10);
  EXPECT_EQ(q.back(), 8);
  EXPECT_EQ(q.size(), 12);
}
}  // namespace stli

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
