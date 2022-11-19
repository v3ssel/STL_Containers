#include <gtest/gtest.h>

#include "array.h"

TEST(array, 1) {
  stli::Array<double, 10> v = {6, 5, 8};
  std::array<double, 10> vc = {6, 5, 8};

  ASSERT_EQ(v.at(0), vc.at(0));
  ASSERT_EQ(v[1], vc[1]);
}

TEST(array, 2) {
  stli::Array<double, 10> v = {6, 5, 8};
  std::array<double, 10> vc = {6, 5, 8};

  ASSERT_EQ(v.front(), vc.front());
}

TEST(array, 3) {
  stli::Array<double, 10> v = {-2, 6, 5, 8};
  std::array<double, 10> vc = {-2, 6, 5, 8};

  ASSERT_EQ(*v.begin(), *vc.begin());
}

TEST(array, 4) {
  stli::Array<double, 10> v = {-2, 6, 5, 8};
  std::array<double, 10> vc = {-2, 6, 5, 8};

  ASSERT_EQ(v.empty(), vc.empty());
  ASSERT_EQ(v.size(), vc.size());
  ASSERT_EQ(v.max_size(), vc.max_size());
}

TEST(array, 5) {
  stli::Array<double, 10> v = {-2, 6, 5, 8};
  std::array<double, 10> vc = {-2, 6, 5, 8};
  stli::Array<double, 10> v2;
  std::array<double, 10> vc2;

  v.swap(v2);
  vc.swap(vc2);

  ASSERT_EQ(v2.size(), vc2.size());
  ASSERT_EQ(v2[1], vc2[1]);
}

TEST(array, 6) {
  stli::Array<double, 10> v = {-2, 6, 5, 8};
  std::array<double, 10> vc = {-2, 6, 5, 8};

  auto v2 = v.begin();
  auto vc2 = vc.begin();

  ASSERT_EQ(*v2, *vc2);
  v2++;
  vc2++;
  ASSERT_EQ(*v2, *vc2);
}

TEST(array, 7) {
  stli::Array<double, 10> v;
  v.fill(20);

  ASSERT_EQ(v.at(9), 20);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
