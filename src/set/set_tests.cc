#include <gtest/gtest.h>

#include <set>

#include "set.h"

TEST(Set, 1) {
  stli::Set<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  std::set<double> vc = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  stli::Set<double> v1 = v;
  std::set<double> vc1 = vc;

  ASSERT_EQ(*v1.begin(), *vc1.begin());
  ASSERT_EQ(v1.empty(), vc1.empty());
  ASSERT_EQ(v1.size(), vc1.size());
}

TEST(Set, 2) {
  stli::Set<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  std::set<double> vc = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  auto x = v.begin();
  auto y = vc.begin();

  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(Set, 3) {
  stli::Set<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  std::set<double> vc = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  v.clear();
  vc.clear();
  auto x = v.begin();
  auto y = vc.begin();

  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(Set, 4) {
  stli::Set<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  std::set<double> vc = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  v.insert(15);
  vc.insert(15);
  v.erase(v.begin());
  vc.erase(vc.begin());
  auto x = v.begin();
  auto y = vc.begin();
  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(Set, 5) {
  stli::Set<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  std::set<double> vc = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  stli::Set<double> v1 = {100, 200, 300, 400, 500};
  std::set<double> vc1 = {100, 200, 300, 400, 500};
  v.swap(v1);
  vc.swap(vc1);

  auto x = v.begin();
  auto y = vc.begin();
  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(Set, 6) {
  stli::Set<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  stli::Set<double> v1 = {100, 200, 300, 400, 500};
  stli::Set<double> vc = {-3, 1,  -5,  42,  2,   -6,  8,
                          20, 26, 100, 200, 300, 400, 500};
  v.merge(v1);

  auto x = v.begin();
  auto y = vc.begin();
  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(Set, 7) {
  stli::Set<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  std::set<double> vc = {-3, 1, -5, 42, 2, -6, 8, 20, 26};

  ASSERT_EQ(*v.find(20), *vc.find(20));
}

TEST(Set, 8) {
  stli::Set<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};

  ASSERT_EQ(v.contains(100), false);
}

TEST(Set, 9) {
  stli::Set<double> s = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  std::set<double> o = {-3, 1, -5, 42, 2, -6, 8, 20, 26};

  auto r = s.emplace(100, 200, 42, 400);

  auto pr1 = o.emplace(100);
  auto pr2 = o.emplace(200);
  auto pr3 = o.emplace(42);
  auto pr4 = o.emplace(400);

  EXPECT_EQ(*(r[0].first), *(pr1.first));
  EXPECT_EQ(r[0].second, pr1.second);

  EXPECT_EQ(*(r[1].first), *(pr2.first));
  EXPECT_EQ(r[1].second, pr2.second);

  EXPECT_EQ(*(r[2].first), *(pr3.first));
  EXPECT_EQ(r[2].second, pr3.second);

  EXPECT_EQ(*(r[3].first), *(pr4.first));
  EXPECT_EQ(r[3].second, pr4.second);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
