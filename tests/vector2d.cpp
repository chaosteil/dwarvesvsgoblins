#include <UnitTest++.h>

#include "utils/vector2d.h"

using namespace ::dvg::utils;

SUITE (Vector2d) {
  TEST (Defaults) {
    Vector2d v;

    CHECK_EQUAL(v.x(), 0.0);
    CHECK_EQUAL(v.y(), 0.0);

    CHECK_EQUAL(v.xi(), 0);
    CHECK_EQUAL(v.yi(), 0);
  }

  TEST (Set) {
    Vector2d v(3, 4);
    CHECK_EQUAL(v.x(), 3.0);
    CHECK_EQUAL(v.y(), 4.0);
    CHECK_EQUAL(v.xi(), 3);
    CHECK_EQUAL(v.yi(), 4);

    v.set_x(2).set_y(7);
    CHECK_EQUAL(v.x(), 2.0);
    CHECK_EQUAL(v.y(), 7.0);
    CHECK_EQUAL(v.xi(), 2);
    CHECK_EQUAL(v.yi(), 7);

    v.set_y(6).set_x(8);
    CHECK_EQUAL(v.x(), 8.0);
    CHECK_EQUAL(v.y(), 6.0);
    CHECK_EQUAL(v.xi(), 8);
    CHECK_EQUAL(v.yi(), 6);
  }

  TEST (Addition) {
    Vector2d v1(1, 4);
    Vector2d v2(2, 3);
    Vector2d v3 = v1 + v2;

    CHECK_EQUAL(v3.x(), 3.0);
    CHECK_EQUAL(v3.y(), 7.0);
  }

  TEST (Subtraction) {
    Vector2d v1(1, 4);
    Vector2d v2(2, 3);
    Vector2d v3 = v1 - v2;

    CHECK_EQUAL(v3.x(), -1.0);
    CHECK_EQUAL(v3.y(), 1.0);
  }

  TEST (Length) {
    Vector2d v1(3, 4);
    Vector2d v2(4, 3);

    CHECK_CLOSE(v1.length(), 5, 0.01);
    CHECK_CLOSE(v2.length(), 5, 0.01);
  }

  TEST (ScalarMultiplication) {
    Vector2d v1(2, 3);
    Vector2d v2 = v1 * 4;

    CHECK_EQUAL(v2.x(), 8);
    CHECK_EQUAL(v2.y(), 12);
  }

  TEST (ScalarProduct) {
    Vector2d v1(1, 4);
    Vector2d v2(2, 3);
    double sp = v1 * v2;

    CHECK_EQUAL(sp, 14);
  }
}
