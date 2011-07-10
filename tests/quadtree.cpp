#include <UnitTest++.h>

#include "utils/quadtree.h"

#include <boost/foreach.hpp>

using namespace ::dvg::utils;

struct RegularQuadtree {
  RegularQuadtree() : q(Rectangle(Vector2d(0, 0), Vector2d(10, 10)), 4, 1) {}
  virtual ~RegularQuadtree() {}

  Quadtree<int> q;
  Quadtree<int>::Items items;
};

SUITE (QuadtreeNode) {
  TEST_FIXTURE(RegularQuadtree, Emptiness) {
    CHECK_EQUAL(0, q.item_count());
    CHECK(Vector2d(0, 0) == q.rect().pos());
    CHECK(Vector2d(10, 10) == q.rect().size());
  }

  TEST_FIXTURE(RegularQuadtree, SingleItemInsert) {
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

  TEST_FIXTURE(RegularQuadtree, SingleItemRemove) {
    q.Insert(8, Vector2d(5, 5));
    q.Remove(8);
    CHECK_EQUAL(0, q.item_count());

    q.GetFromPosition(Vector2d(5, 5), &items);
    CHECK_EQUAL(0, items.size());
  }

  TEST_FIXTURE(RegularQuadtree, MultipleItemsInsert) {
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

  TEST_FIXTURE(RegularQuadtree, MultipleItemsRemove) {
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

  TEST_FIXTURE(RegularQuadtree, GetRectangle) {
    q.Insert(1, Vector2d(1, 1));
    q.Insert(2, Vector2d(9, 1));
    q.Insert(3, Vector2d(1, 9));
    q.Insert(4, Vector2d(9, 9));
    q.Insert(5, Vector2d(9, 9));
    q.Insert(6, Vector2d(5, 5));

    q.GetFromRectangle(Rectangle(Vector2d(4, 4), Vector2d(2, 2)), &items);
    CHECK_EQUAL(1, items.size());
    CHECK_EQUAL(6, items.begin()->first);
    items.clear();

    q.GetFromRectangle(Rectangle(Vector2d(1, 1), Vector2d(8, 2)), &items);
    CHECK_EQUAL(2, items.size());
    items.clear();

    q.GetFromRectangle(Rectangle(Vector2d(1, 1), Vector2d(8, 8)), &items);
    CHECK_EQUAL(6, items.size());
  }
}
