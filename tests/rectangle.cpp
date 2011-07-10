#include <UnitTest++.h>

#include "utils/rectangle.h"

using namespace ::dvg::utils;

SUITE (Rectangle) {
  TEST (SetData) {
    Rectangle rect(Vector2d(0, 0), Vector2d(10, 10));
    CHECK(Vector2d(0, 0) == rect.pos());
    CHECK(Vector2d(10, 10) == rect.size());

    rect.set_pos(Vector2d(1, 1));
    CHECK(Vector2d(1, 1) == rect.pos());
    CHECK(Vector2d(10, 10) == rect.size());

    rect.set_size(Vector2d(9, 9));
    CHECK(Vector2d(1, 1) == rect.pos());
    CHECK(Vector2d(9, 9) == rect.size());
  }

  TEST (IntersectionOutside) {
    Rectangle main_rect(Vector2d(0, 0), Vector2d(10, 10));
    Rectangle outside_top_rect(Vector2d(1, -8), Vector2d(5, 5));
    Rectangle outside_bot_rect(Vector2d(1, 12), Vector2d(5, 5));
    Rectangle outside_left_rect(Vector2d(-8, 2), Vector2d(5, 5));
    Rectangle outside_right_rect(Vector2d(12, 2), Vector2d(5, 5));
    Rectangle outside_topleft_rect(Vector2d(-8, -8), Vector2d(5, 5));
    Rectangle outside_topright_rect(Vector2d(12, -8), Vector2d(5, 5));
    Rectangle outside_botleft_rect(Vector2d(-8, 12), Vector2d(5, 5));
    Rectangle outside_botright_rect(Vector2d(12, 12), Vector2d(5, 5));

    CHECK_EQUAL(false, main_rect.DoesIntersect(outside_top_rect));
    CHECK_EQUAL(outside_top_rect.DoesIntersect(main_rect), main_rect.DoesIntersect(outside_top_rect));
    CHECK_EQUAL(false, main_rect.DoesIntersect(outside_bot_rect));
    CHECK_EQUAL(outside_bot_rect.DoesIntersect(main_rect), main_rect.DoesIntersect(outside_bot_rect));
    CHECK_EQUAL(false, main_rect.DoesIntersect(outside_left_rect));
    CHECK_EQUAL(outside_left_rect.DoesIntersect(main_rect), main_rect.DoesIntersect(outside_left_rect));
    CHECK_EQUAL(false, main_rect.DoesIntersect(outside_right_rect));
    CHECK_EQUAL(outside_right_rect.DoesIntersect(main_rect), main_rect.DoesIntersect(outside_right_rect));
    CHECK_EQUAL(false, main_rect.DoesIntersect(outside_topleft_rect));
    CHECK_EQUAL(outside_topleft_rect.DoesIntersect(main_rect), main_rect.DoesIntersect(outside_topleft_rect));
    CHECK_EQUAL(false, main_rect.DoesIntersect(outside_topright_rect));
    CHECK_EQUAL(outside_topright_rect.DoesIntersect(main_rect), main_rect.DoesIntersect(outside_topright_rect));
    CHECK_EQUAL(false, main_rect.DoesIntersect(outside_botleft_rect));
    CHECK_EQUAL(outside_botleft_rect.DoesIntersect(main_rect), main_rect.DoesIntersect(outside_botleft_rect));
    CHECK_EQUAL(false, main_rect.DoesIntersect(outside_botright_rect));
    CHECK_EQUAL(outside_botright_rect.DoesIntersect(main_rect), main_rect.DoesIntersect(outside_botright_rect));
  }

  TEST (IntersectionInside) {
    Rectangle main_rect(Vector2d(0, 0), Vector2d(10, 10));
    Rectangle inside_top_rect(Vector2d(2, -2), Vector2d(5, 5));
    Rectangle inside_bot_rect(Vector2d(2, 8), Vector2d(5, 5));
    Rectangle inside_left_rect(Vector2d(-2, 2), Vector2d(5, 5));
    Rectangle inside_right_rect(Vector2d(8, 2), Vector2d(5, 5));
    Rectangle inside_topleft_rect(Vector2d(-2, -2), Vector2d(5, 5));
    Rectangle inside_topright_rect(Vector2d(8, -2), Vector2d(5, 5));
    Rectangle inside_botleft_rect(Vector2d(-2, 8), Vector2d(5, 5));
    Rectangle inside_botright_rect(Vector2d(8, 8), Vector2d(5, 5));

    CHECK_EQUAL(true, main_rect.DoesIntersect(inside_top_rect));
    CHECK_EQUAL(inside_top_rect.DoesIntersect(main_rect), main_rect.DoesIntersect(inside_top_rect));
    CHECK_EQUAL(true, main_rect.DoesIntersect(inside_bot_rect));
    CHECK_EQUAL(inside_bot_rect.DoesIntersect(main_rect), main_rect.DoesIntersect(inside_bot_rect));
    CHECK_EQUAL(true, main_rect.DoesIntersect(inside_left_rect));
    CHECK_EQUAL(inside_left_rect.DoesIntersect(main_rect), main_rect.DoesIntersect(inside_left_rect));
    CHECK_EQUAL(true, main_rect.DoesIntersect(inside_right_rect));
    CHECK_EQUAL(inside_right_rect.DoesIntersect(main_rect), main_rect.DoesIntersect(inside_right_rect));
    CHECK_EQUAL(true, main_rect.DoesIntersect(inside_topleft_rect));
    CHECK_EQUAL(inside_topleft_rect.DoesIntersect(main_rect), main_rect.DoesIntersect(inside_topleft_rect));
    CHECK_EQUAL(true, main_rect.DoesIntersect(inside_topright_rect));
    CHECK_EQUAL(inside_topright_rect.DoesIntersect(main_rect), main_rect.DoesIntersect(inside_topright_rect));
    CHECK_EQUAL(true, main_rect.DoesIntersect(inside_botleft_rect));
    CHECK_EQUAL(inside_botleft_rect.DoesIntersect(main_rect), main_rect.DoesIntersect(inside_botleft_rect));
    CHECK_EQUAL(true, main_rect.DoesIntersect(inside_topright_rect));
    CHECK_EQUAL(inside_botright_rect.DoesIntersect(main_rect), main_rect.DoesIntersect(inside_botright_rect));
  }
}
