#include <gtest/gtest.h>

#include "stack.h"

namespace stli {
TEST(Constructors, Default) {
  Stack<double> Stack;
  EXPECT_EQ(Stack.size(), 0);
  EXPECT_ANY_THROW(Stack.top());
}

TEST(Constructors, InitList) {
  Stack<double> Stack = {1.23, 23.3, 3.13, 99.999, 55.55};
  EXPECT_EQ(Stack.top(), 55.55);
  EXPECT_EQ(Stack.size(), 5);
}

TEST(Constructors, Copy) {
  Stack<int> s = {9, 7, 5, 3, 1, 4, 8};
  Stack<int> second = s;

  EXPECT_EQ(second.top(), 8);
  EXPECT_EQ(second.size(), 7);
}

TEST(Constructors, Move) {
  Stack<int> s = {9, 7, 5, 3, 1, 4, 8};
  Stack<int> second(std::move(s));

  EXPECT_EQ(s.size(), 0);
  EXPECT_ANY_THROW(s.top());
  EXPECT_EQ(second.top(), 8);
  EXPECT_EQ(second.size(), 7);
}

TEST(Constructors, OperatorMove) {
  Stack<int> s = {9, 7, 5, 3, 1, 4, 8};
  Stack<int> second;
  second = std::move(s);

  EXPECT_EQ(s.size(), 0);
  EXPECT_ANY_THROW(s.top());
  EXPECT_EQ(second.top(), 8);
  EXPECT_EQ(second.size(), 7);
}

TEST(Stack, ElementAccess) {
  Stack<int> s = {9, 7, 5, 3, 1, 4, 8};
  EXPECT_EQ(s.top(), 8);
}

TEST(Stack, Capacity) {
  Stack<int> s;
  EXPECT_EQ(s.size(), 0);
  EXPECT_EQ(s.empty(), true);
  s.push(11);
  s.push(22);
  EXPECT_EQ(s.size(), 2);
  EXPECT_EQ(s.empty(), false);
}

TEST(StackModifiers, Push) {
  Stack<int> s;
  EXPECT_ANY_THROW(s.top());
  s.push(11);
  EXPECT_EQ(s.top(), 11);
  s.push(22);
  EXPECT_EQ(s.top(), 22);
}

TEST(StackModifiers, Pop) {
  Stack<int> s;
  EXPECT_ANY_THROW(s.pop());
  s.push(11);
  s.push(22);
  EXPECT_EQ(s.top(), 22);
  s.pop();
  EXPECT_EQ(s.top(), 11);
}

TEST(StackModifiers, Swap) {
  Stack<int> s = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  Stack<int> second = {16, 32, 64, 96};
  s.swap(second);

  EXPECT_EQ(s.size(), 4);
  EXPECT_EQ(s.top(), 96);
  EXPECT_EQ(second.size(), 10);
  EXPECT_EQ(second.top(), 10);
}

TEST(StackModifiers, EmplaceFront) {
  Stack<int> s = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s.emplace_front(16, 32, 64, 96);

  EXPECT_EQ(s.size(), 14);
  EXPECT_EQ(s.top(), 96);
}

}  // namespace stli

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
