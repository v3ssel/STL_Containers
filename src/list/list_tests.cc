#include <gtest/gtest.h>

#include <list>

#include "list.h"

TEST(ListConstructors, Default) {
  stli::List<int> slist;
  std::list<int> olist;

  EXPECT_EQ(slist.size(), olist.size());
}

TEST(ListConstructors, Sized) {
  stli::List<int> slist(8);
  std::list<int> olist(8);

  auto si = slist.begin();
  auto oi = olist.begin();
  for (; si != slist.end() && oi != olist.end(); ++si, ++oi)
    EXPECT_EQ(*si, *oi);

  EXPECT_EQ(slist.size(), olist.size());
}

TEST(ListConstructors, InitList) {
  stli::List<int> slist = {101, 1111, 212, 8008};
  std::list<int> olist = {101, 1111, 212, 8008};

  auto si = slist.begin();
  auto oi = olist.begin();
  for (; si != slist.end() && oi != olist.end(); ++si, ++oi)
    EXPECT_EQ(*si, *oi);

  EXPECT_EQ(slist.size(), olist.size());
}

TEST(ListConstructors, Copy) {
  stli::List<int> s_list = {101, 1111, 212, 8008};
  stli::List<int> s_copy = s_list;

  std::list<int> o_list = {101, 1111, 212, 8008};
  std::list<int> o_copy = o_list;

  auto si = s_copy.begin();
  auto oi = o_copy.begin();
  for (; si != s_copy.end() && oi != o_copy.end(); si++, oi++)
    EXPECT_EQ(*si, *oi);
  EXPECT_EQ(s_copy.size(), o_copy.size());
}

TEST(ListConstructors, Move) {
  stli::List<int> s_list = {101, 1111, 212, 8008};
  stli::List<int> s_moved = std::move(s_list);

  std::list<int> o_list = {101, 1111, 212, 8008};
  std::list<int> o_moved = std::move(o_list);

  auto si = s_moved.begin();
  auto oi = o_moved.begin();
  for (; si != s_moved.end() && oi != o_moved.end(); si++, oi++)
    EXPECT_EQ(*si, *oi);
  EXPECT_EQ(s_moved.size(), o_moved.size());

  EXPECT_EQ(s_list.size(), o_list.size());
}

TEST(ListElementAccess, Front) {
  stli::List<int> slist = {99, 0, -22, -1001, 5999, 1};
  std::list<int> olist = {99, 0, -22, -1001, 5999, 1};

  EXPECT_EQ(slist.front(), olist.front());
}

TEST(ListElementAccess, Back) {
  stli::List<int> slist = {99, 0, -22, -1001, 5999, 1};
  std::list<int> olist = {99, 0, -22, -1001, 5999, 1};

  EXPECT_EQ(slist.back(), olist.back());
}

TEST(ListIterators, Begin) {
  stli::List<int> slist = {99, 0, -22, -1001, 5999, 1};
  std::list<int> olist = {99, 0, -22, -1001, 5999, 1};

  EXPECT_EQ(*(slist.begin()), *(olist.begin()));
}

TEST(ListIterators, End) {
  stli::List<int> slist = {99, 0, -22, -1001, 5999, 1};
  std::list<int> olist = {99, 0, -22, -1001, 5999, 1};

  auto si = slist.end();
  auto oi = olist.end();
  si--;
  --oi;

  EXPECT_EQ(*si, *oi);
}

TEST(ListCapacity, Empty) {
  stli::List<int> slist = {99, 0, -22, -1001, 5999, 1};
  std::list<int> olist = {99, 0, -22, -1001, 5999, 1};

  EXPECT_EQ(slist.empty(), olist.empty());
}

TEST(ListCapacity, Size) {
  stli::List<int> slist = {99, 0, -22, -1001, 5999, 1};
  std::list<int> olist = {99, 0, -22, -1001, 5999, 1};

  EXPECT_EQ(slist.size(), olist.size());
}

TEST(ListModifiers, Clear) {
  stli::List<int> slist = {99, 0, -22, -1001, 5999, 1};
  std::list<int> olist = {99, 0, -22, -1001, 5999, 1};

  slist.clear();
  olist.clear();
  EXPECT_EQ(slist.size(), olist.size());

  slist.push_front(11);
  slist.push_back(22);
  slist.push_front(33);
  slist.push_back(44);
  slist.push_front(55);
  slist.push_back(66);

  olist.push_front(11);
  olist.push_back(22);
  olist.push_front(33);
  olist.push_back(44);
  olist.push_front(55);
  olist.push_back(66);

  auto si = slist.begin();
  auto oi = olist.begin();
  for (; si != slist.end() && oi != olist.end(); ++si, ++oi)
    EXPECT_EQ(*si, *oi);

  EXPECT_EQ(slist.size(), olist.size());

  slist.clear();
  olist.clear();
  EXPECT_EQ(slist.size(), olist.size());
}

TEST(ListModifiers, Insert) {
  stli::List<int> slist = {99, 0, -22, -1001, 5999, 1};
  std::list<int> olist = {99, 0, -22, -1001, 5999, 1};

  auto s_it = slist.end();
  s_it--;
  s_it--;
  s_it--;
  slist.insert(s_it, 33);

  auto o_it = olist.end();
  o_it--;
  o_it--;
  o_it--;
  olist.insert(o_it, 33);

  s_it = slist.end();
  o_it = olist.end();

  slist.insert(s_it, 199);
  olist.insert(o_it, 199);

  s_it = slist.begin();
  o_it = olist.begin();

  slist.insert(s_it, -9);
  olist.insert(o_it, -9);

  auto si = slist.begin();
  auto oi = olist.begin();
  for (; si != slist.end() && oi != olist.end(); ++si, ++oi)
    EXPECT_EQ(*si, *oi);
  EXPECT_EQ(slist.size(), olist.size());
}

TEST(ListModifiers, Erase) {
  stli::List<int> slist = {99, 0, -22, -1001, 5999, 1};
  std::list<int> olist = {99, 0, -22, -1001, 5999, 1};

  auto s_it = slist.end();
  s_it--;
  s_it--;
  s_it--;
  slist.erase(s_it);

  auto o_it = olist.end();
  o_it--;
  o_it--;
  o_it--;
  olist.erase(o_it);

  s_it = slist.end();
  s_it--;
  o_it = olist.end();
  o_it--;

  slist.erase(s_it);
  olist.erase(o_it);

  s_it = slist.begin();
  o_it = olist.begin();

  slist.erase(s_it);
  olist.erase(o_it);

  auto si = slist.begin();
  auto oi = olist.begin();
  for (; si != slist.end() && oi != olist.end(); ++si, ++oi)
    EXPECT_EQ(*si, *oi);
  EXPECT_EQ(slist.size(), olist.size());

  EXPECT_ANY_THROW(slist.erase(slist.end()));
}

TEST(ListModifiers, PushBack) {
  stli::List<int> slist;
  std::list<int> olist;
  slist.push_back(11);
  slist.push_back(22);
  slist.push_back(33);

  olist.push_back(11);
  olist.push_back(22);
  olist.push_back(33);

  auto si = slist.begin();
  auto oi = olist.begin();
  for (; si != slist.end() && oi != olist.end(); ++si, ++oi)
    EXPECT_EQ(*si, *oi);

  EXPECT_EQ(slist.size(), olist.size());
}

TEST(ListModifiers, PopBack) {
  stli::List<int> slist;
  std::list<int> olist;

  EXPECT_ANY_THROW(slist.pop_back());

  slist.push_front(11);
  slist.push_front(22);
  slist.push_front(33);
  slist.pop_back();

  olist.push_front(11);
  olist.push_front(22);
  olist.push_front(33);
  olist.pop_back();

  auto si = slist.begin();
  auto oi = olist.begin();
  for (; si != slist.end() && oi != olist.end(); ++si, ++oi)
    EXPECT_EQ(*si, *oi);

  EXPECT_EQ(slist.size(), olist.size());
}

TEST(ListModifiers, PushFront) {
  stli::List<int> slist;
  std::list<int> olist;
  slist.push_front(11);
  slist.push_front(22);
  slist.push_front(33);
  slist.push_front(44);

  olist.push_front(11);
  olist.push_front(22);
  olist.push_front(33);
  olist.push_front(44);

  auto si = slist.begin();
  auto oi = olist.begin();
  for (; si != slist.end() && oi != olist.end(); ++si, ++oi)
    EXPECT_EQ(*si, *oi);

  EXPECT_EQ(slist.size(), olist.size());
}

TEST(ListModifiers, PopFront) {
  stli::List<int> slist;
  std::list<int> olist;

  EXPECT_ANY_THROW(slist.pop_front());

  slist.push_front(11);
  slist.push_front(22);
  slist.push_front(33);
  slist.push_front(44);
  slist.pop_front();
  slist.pop_front();

  olist.push_front(11);
  olist.push_front(22);
  olist.push_front(33);
  olist.push_front(44);
  olist.pop_front();
  olist.pop_front();

  auto si = slist.begin();
  auto oi = olist.begin();
  for (; si != slist.end() && oi != olist.end(); ++si, ++oi)
    EXPECT_EQ(*si, *oi);

  EXPECT_EQ(slist.size(), olist.size());
}

TEST(ListModifiers, Swap) {
  stli::List<int> f_slist = {99, 0, -22, -1001, 5999, 1};
  stli::List<int> s_slist = {101, 1111, 212, 8008};
  f_slist.swap(s_slist);

  std::list<int> f_olist = {99, 0, -22, -1001, 5999, 1};
  std::list<int> s_olist = {101, 1111, 212, 8008};
  f_olist.swap(s_olist);

  auto si = f_slist.begin();
  auto oi = f_olist.begin();
  for (; si != f_slist.end() && oi != f_olist.end(); si++, oi++)
    EXPECT_EQ(*si, *oi);
  EXPECT_EQ(f_slist.size(), f_olist.size());

  si = s_slist.begin();
  oi = s_olist.begin();
  for (; si != s_slist.end() && oi != s_olist.end(); si++, oi++)
    EXPECT_EQ(*si, *oi);
  EXPECT_EQ(s_slist.size(), s_olist.size());
}

TEST(ListModifiers, Merge) {
  stli::List<int> f_slist = {10, 20, 30, 44, 55, 99, 111};
  stli::List<int> s_slist = {0, 1, 2, 33, 41, 56, 100, 1001};
  f_slist.merge(s_slist);

  std::list<int> f_olist = {10, 20, 30, 44, 55, 99, 111};
  std::list<int> s_olist = {0, 1, 2, 33, 41, 56, 100, 1001};
  f_olist.merge(s_olist);

  auto si = f_slist.begin();
  auto oi = f_olist.begin();
  for (; si != f_slist.end() && oi != f_olist.end(); si++, oi++)
    EXPECT_EQ(*si, *oi);
  EXPECT_EQ(f_slist.size(), f_olist.size());
}

TEST(ListModifiers, MergeNotSort) {
  stli::List<int> f_slist = {101, 20, -30, 444, 5, 99, 111};
  stli::List<int> s_slist = {43, 22, 26, 33, 4, 3, 10, 11};
  f_slist.merge(s_slist);

  std::list<int> f_olist = {101, 20, -30, 444, 5, 99, 111};
  std::list<int> s_olist = {43, 22, 26, 33, 4, 3, 10, 11};
  f_olist.merge(s_olist);

  auto si = f_slist.begin();
  auto oi = f_olist.begin();
  for (; si != f_slist.end() && oi != f_olist.end(); si++, oi++)
    EXPECT_EQ(*si, *oi);
  EXPECT_EQ(f_slist.size(), f_olist.size());
}

TEST(ListModifiers, Splice) {
  stli::List<int> f_slist = {101, 20, -30, 444, 5, 99, 111};
  stli::List<int> s_slist = {43, 22, 26, 33, 4, 3, 10, 11};
  auto s_pos = f_slist.begin();
  s_pos++;
  s_pos++;
  s_pos++;
  f_slist.splice(s_pos, s_slist);

  std::list<int> f_olist = {101, 20, -30, 444, 5, 99, 111};
  std::list<int> s_olist = {43, 22, 26, 33, 4, 3, 10, 11};
  auto o_pos = f_olist.begin();
  o_pos++;
  o_pos++;
  o_pos++;
  f_olist.splice(o_pos, s_olist);

  auto si = f_slist.begin();
  auto oi = f_olist.begin();
  for (; si != f_slist.end() && oi != f_olist.end(); si++, oi++)
    EXPECT_EQ(*si, *oi);
  EXPECT_EQ(f_slist.size(), f_olist.size());
}

TEST(ListModifiers, Reverse) {
  stli::List<int> slist = {101, 20, -30, 444, 5, 99, 111};
  std::list<int> olist = {101, 20, -30, 444, 5, 99, 111};

  slist.reverse();
  olist.reverse();

  auto si = slist.begin();
  auto oi = olist.begin();
  for (; si != slist.end() && oi != olist.end(); si++, oi++)
    EXPECT_EQ(*si, *oi);
  EXPECT_EQ(slist.size(), olist.size());
}

TEST(ListModifiers, Unique) {
  stli::List<int> slist = {10, -123, 10,  10,  1220, 12, -3,  -3,
                           -3, -3,   241, 555, 555,  0,  -123};

  std::list<int> olist = {10, -123, 10,  10,  1220, 12, -3,  -3,
                          -3, -3,   241, 555, 555,  0,  -123};

  slist.unique();
  olist.unique();

  auto si = slist.begin();
  auto oi = olist.begin();
  for (; si != slist.end() && oi != olist.end(); si++, oi++)
    EXPECT_EQ(*si, *oi);
  EXPECT_EQ(slist.size(), olist.size());
}

TEST(ListModifiers, Sort) {
  stli::List<int> slist = {10, -123, 10,  10,  1220, 12, -3,  -3,
                           -3, -3,   241, 555, 555,  0,  -123};

  std::list<int> olist = {10, -123, 10,  10,  1220, 12, -3,  -3,
                          -3, -3,   241, 555, 555,  0,  -123};

  slist.sort();
  olist.sort();

  auto si = slist.begin();
  auto oi = olist.begin();
  for (; si != slist.end() && oi != olist.end(); si++, oi++)
    EXPECT_EQ(*si, *oi);
  EXPECT_EQ(slist.size(), olist.size());
}

TEST(ListModifiers, Emplace) {
  stli::List<int> slist = {10, -123, 10,  10,  1220, 12, -3,  -3,
                           -3, -3,   241, 555, 555,  0,  -123};

  auto it = slist.emplace((++slist.begin()), 101, 20, -30, 444, 5, 99, 111);

  EXPECT_EQ(*it, -123);
  EXPECT_EQ(slist.size(), 22);
}

TEST(ListModifiers, EmplaceBack) {
  stli::List<int> slist = {10, -123, 10,  10,  1220, 12, -3,  -3,
                           -3, -3,   241, 555, 555,  0,  -123};

  slist.emplace_back(101, 20, -30, 444, 5, 99, 111);

  EXPECT_EQ(slist.back(), 111);
  EXPECT_EQ(slist.front(), 10);
  EXPECT_EQ(slist.size(), 22);
}

TEST(ListModifiers, EmplaceFront) {
  stli::List<int> slist = {10, -123, 10,  10,  1220, 12, -3,  -3,
                           -3, -3,   241, 555, 555,  0,  -123};

  slist.emplace_front(101, 20, -30, 444, 5, 99, 111);

  EXPECT_EQ(slist.back(), -123);
  EXPECT_EQ(slist.front(), 111);
  EXPECT_EQ(slist.size(), 22);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
