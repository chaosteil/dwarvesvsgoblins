#include <UnitTest++.h>

#include "utils/quadtree.h"

#include <boost/foreach.hpp>

using namespace ::dvg::utils;

struct RegularQuadTree {
  RegularQuadTree() : q(Vector2d(10, 10), 4, 1) {}
  virtual ~RegularQuadTree() {}

  QuadTree<int> q;
  QuadTree<int>::Items items;
};

SUITE (QuadTreeNode) {
  TEST_FIXTURE(RegularQuadTree, Emptiness) {
    CHECK_EQUAL(0, q.item_count());
    CHECK(Vector2d(0, 0) == q.topleft());
    CHECK(Vector2d(10, 10) == q.size());
  }

  TEST_FIXTURE(RegularQuadTree, SingleItemInsert) {
    q.Insert(8, Vector2d(5, 5));
    CHECK_EQUAL(1, q.item_count());

    q.GetFromPosition(Vector2d(5, 5), &items);
    CHECK_EQUAL(1, items.size());
    CHECK_EQUAL(8, items.begin()->first);
    CHECK(Vector2d(5, 5) == items.begin()->second);

    items.clear();
    q.GetFromPosition(Vector2d(6, 6), &items);
    CHECK_EQUAL(0, items.size());
  }

  TEST_FIXTURE(RegularQuadTree, SingleItemRemove) {
    q.Insert(8, Vector2d(5, 5));
    q.Remove(8);
    CHECK_EQUAL(0, q.item_count());

    q.GetFromPosition(Vector2d(5, 5), &items);
    CHECK_EQUAL(0, items.size());
  }

  TEST_FIXTURE(RegularQuadTree, MultipleItemsInsert) {
    q.Insert(1, Vector2d(1, 1));
    q.Insert(2, Vector2d(9, 1));
    q.Insert(3, Vector2d(1, 9));
    q.Insert(4, Vector2d(9, 9));
    q.Insert(5, Vector2d(9, 9));
    q.Insert(6, Vector2d(1, 1));
    CHECK_EQUAL(6, q.item_count());

    q.GetFromPosition(Vector2d(5, 5), &items);
    CHECK_EQUAL(0, items.size());
    items.clear();

    q.GetFromPosition(Vector2d(9, 1), &items);
    CHECK_EQUAL(1, items.size());
    CHECK_EQUAL(2, items.begin()->first);
    items.clear();

    q.GetFromPosition(Vector2d(9, 9), &items);
    CHECK_EQUAL(2, items.size());
    items.clear();
  }

  TEST_FIXTURE(RegularQuadTree, MultipleItemsRemove) {
    q.Insert(1, Vector2d(1, 1));
    q.Insert(2, Vector2d(9, 1));
    q.Insert(3, Vector2d(1, 9));
    q.Insert(4, Vector2d(9, 9));
    q.Insert(5, Vector2d(9, 9));
    q.Insert(6, Vector2d(1, 1));

    q.Remove(8);
    CHECK_EQUAL(6, q.item_count());

    q.Remove(6);
    CHECK_EQUAL(5, q.item_count());
    
    q.Remove(1);
    q.Remove(2);
    CHECK_EQUAL(3, q.item_count());

    q.GetFromPosition(Vector2d(9, 9), &items);
    CHECK_EQUAL(2, items.size());
    items.clear();

    q.GetFromPosition(Vector2d(1, 1), &items);
    CHECK_EQUAL(0, items.size());
  }
}
