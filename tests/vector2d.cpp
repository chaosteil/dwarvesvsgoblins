#include <UnitTest++.h>

#include "utils/vector2d.h"

using namespace ::dvg::utils;

SUITE (Vector2d) {
  TEST (Defaults) {
    Vector2d v;

    CHECK_EQUAL(0.0, v.x());
    CHECK_EQUAL(0.0, v.y());

    CHECK_EQUAL(0, v.xi());
    CHECK_EQUAL(0, v.yi());
  }

  TEST (Set) {
    Vector2d v(3, 4);
    CHECK_EQUAL(3.0, v.x());
    CHECK_EQUAL(4.0, v.y());
    CHECK_EQUAL(3, v.xi());
    CHECK_EQUAL(4, v.yi());

    v.set_x(2).set_y(7);
    CHECK_EQUAL(2.0, v.x());
    CHECK_EQUAL(7.0, v.y());
    CHECK_EQUAL(2, v.xi());
    CHECK_EQUAL(7, v.yi());

    v.set_y(6).set_x(8);
    CHECK_EQUAL(8.0, v.x());
    CHECK_EQUAL(6.0, v.y());
    CHECK_EQUAL(8, v.xi());
    CHECK_EQUAL(6, v.yi());
  }

  TEST (Addition) {
    Vector2d v1(1, 4);
    Vector2d v2(2, 3);
    Vector2d v3 = v1 + v2;

    CHECK_EQUAL(3.0, v3.x());
    CHECK_EQUAL(7.0, v3.y());

    CHECK_EQUAL(1, v1.x());
    CHECK_EQUAL(4, v1.y());
  }

  TEST (Subtraction) {
    Vector2d v1(1, 4);
    Vector2d v2(2, 3);
    Vector2d v3 = v1 - v2;

    CHECK_EQUAL(-1.0, v3.x());
    CHECK_EQUAL(1.0, v3.y());

    CHECK_EQUAL(1, v1.x());
    CHECK_EQUAL(4, v1.y());
  }

  TEST (Length) {
    Vector2d v1(3, 4);
    Vector2d v2(4, 3);

    CHECK_CLOSE(5, v1.length(), 0.01);
    CHECK_CLOSE(5, v2.length(), 0.01);
  }

  TEST (ScalarMultiplication) {
    Vector2d v1(2, 3);
    Vector2d v2 = v1 * 4;

    CHECK_EQUAL(8, v2.x());
    CHECK_EQUAL(12, v2.y());

    CHECK_EQUAL(2, v1.x());
    CHECK_EQUAL(3, v1.y());
  }

  TEST (ScalarProduct) {
    Vector2d v1(1, 4);
    Vector2d v2(2, 3);
    double sp = v1 * v2;

    CHECK_EQUAL(14, sp);

    CHECK_EQUAL(1, v1.x());
    CHECK_EQUAL(4, v1.y());
  }
}
