#include <gtest/gtest.h>

#include <vector>

#include "vector.h"

TEST(vector, 1) {
  stli::Vector<double> v = {6, 5, 8};
  std::vector<double> vc = {6, 5, 8};

  ASSERT_EQ(v.at(0), vc.at(0));
  ASSERT_EQ(v[1], vc[1]);
}

TEST(vector, 2) {
  stli::Vector<double> v = {6, 5, 8};
  std::vector<double> vc = {6, 5, 8};

  ASSERT_EQ(v.front(), vc.front());
  ASSERT_EQ(v.back(), vc.back());
}

TEST(vector, 3) {
  stli::Vector<double> v = {-2, 6, 5, 8};
  std::vector<double> vc = {-2, 6, 5, 8};

  ASSERT_EQ(*v.begin(), *vc.begin());
}

TEST(vector, 4) {
  stli::Vector<double> v = {-2, 6, 5, 8};
  std::vector<double> vc = {-2, 6, 5, 8};

  ASSERT_EQ(v.empty(), vc.empty());
  ASSERT_EQ(v.size(), vc.size());
  ASSERT_EQ(v.max_size(), vc.max_size());
}

TEST(vector, 5) {
  stli::Vector<double> v = {-2, 6, 5, 8};
  std::vector<double> vc = {-2, 6, 5, 8};
  v.reserve(20);
  vc.reserve(20);

  ASSERT_EQ(v.empty(), vc.empty());
  ASSERT_EQ(v.size(), vc.size());
  ASSERT_EQ(v.max_size(), vc.max_size());
  ASSERT_EQ(v.capacity(), vc.capacity());
}

TEST(vector, 6) {
  stli::Vector<double> v = {-2, 6, 5, 8};
  std::vector<double> vc = {-2, 6, 5, 8};
  v.reserve(20);
  vc.reserve(20);
  v.shrink_to_fit();
  vc.shrink_to_fit();

  ASSERT_EQ(v.empty(), vc.empty());
  ASSERT_EQ(v.size(), vc.size());
  ASSERT_EQ(v.max_size(), vc.max_size());
  ASSERT_EQ(v.capacity(), vc.capacity());
}

TEST(vector, 7) {
  stli::Vector<double> v = {-2, 6, 5, 8};
  std::vector<double> vc = {-2, 6, 5, 8};
  v.clear();
  vc.clear();

  ASSERT_EQ(v.empty(), vc.empty());
  ASSERT_EQ(v.size(), vc.size());
  ASSERT_EQ(v.max_size(), vc.max_size());
  ASSERT_EQ(v.capacity(), vc.capacity());
}

TEST(vector, 8) {
  stli::Vector<double> v = {-2, 6, 5, 8};
  std::vector<double> vc = {-2, 6, 5, 8};
  v.insert(v.begin(), 15);
  vc.insert(vc.begin(), 15);

  ASSERT_EQ(v.empty(), vc.empty());
  ASSERT_EQ(v.size(), vc.size());
  ASSERT_EQ(v[0], vc[0]);
  ASSERT_EQ(v.capacity(), vc.capacity());
}

TEST(vector, 9) {
  stli::Vector<double> v = {-2, 6, 5, 8};
  std::vector<double> vc = {-2, 6, 5, 8};
  v.erase(v.begin());
  vc.erase(vc.begin());

  ASSERT_EQ(v.empty(), vc.empty());
  ASSERT_EQ(v.size(), vc.size());
  ASSERT_EQ(v[0], vc[0]);
  ASSERT_EQ(v.capacity(), vc.capacity());
}

TEST(vector, 10) {
  stli::Vector<double> v = {-2, 6, 5, 8};
  std::vector<double> vc = {-2, 6, 5, 8};
  v.push_back(15);
  vc.push_back(15);

  ASSERT_EQ(v.size(), vc.size());
  ASSERT_EQ(v[4], vc[4]);
  ASSERT_EQ(v.capacity(), vc.capacity());
}

TEST(vector, 11) {
  stli::Vector<double> v = {-2, 6, 5, 8};
  std::vector<double> vc = {-2, 6, 5, 8};
  v.pop_back();
  vc.pop_back();

  ASSERT_EQ(v.size(), vc.size());
  ASSERT_EQ(v.capacity(), vc.capacity());
}

TEST(vector, 12) {
  stli::Vector<double> v = {-2, 6, 5, 8};
  std::vector<double> vc = {-2, 6, 5, 8};
  stli::Vector<double> v2;
  std::vector<double> vc2;

  v.swap(v2);
  vc.swap(vc2);

  ASSERT_EQ(v2.size(), vc2.size());
  ASSERT_EQ(v2.capacity(), vc2.capacity());
}

TEST(vector, 13) {
  stli::Vector<double> v = {-2, 6, 5, 8};
  std::vector<double> vc = {-2, 6, 5, 8};

  auto v2 = v.begin();
  auto vc2 = vc.begin();

  ASSERT_EQ(*v2, *vc2);
  v2++;
  vc2++;
  ASSERT_EQ(*v2, *vc2);
}

TEST(vector, 14) {
  stli::Vector<double> v = {-2, 6, 5, 8};
  auto it = v.begin();
  ++ ++it;
  v.emplace(it, 8, 1, 4, 12, -6);

  ASSERT_EQ(v.size(), 9);
  ASSERT_EQ(v.at(3), 5);
}

TEST(vector, 15) {
  stli::Vector<double> v = {-2, 6, 5, 8};
  auto it = v.begin();
  ++ ++it;
  v.emplace_back(8, 1, 4, 12, -6);

  ASSERT_EQ(v.size(), 9);
  ASSERT_EQ(v.at(5), 1);
  ASSERT_EQ(v.back(), -6);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
