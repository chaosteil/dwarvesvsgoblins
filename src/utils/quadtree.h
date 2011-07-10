#ifndef DVG_SRC_UTILS_QUADTREE_H_
#define DVG_SRC_UTILS_QUADTREE_H_

#include <vector>
#include <boost/unordered_map.hpp>
#include "utils/rectangle.h"
#include "utils/vector2d.h"

namespace dvg {
namespace utils {

template<class Item>
class QuadtreeNode {
 public:
  typedef boost::unordered_map<Item, Vector2d> Items;

  QuadtreeNode(const Rectangle& rect,
               QuadtreeNode *parent, int level, int max_items);
  virtual ~QuadtreeNode();

  void GetFromPosition(const Vector2d &pos, Items *items) const;
  void GetFromRectangle(const Rectangle &rect, Items *items) const;

  int item_count() const { return item_count_; }

  const Rectangle &rect() const { return rect_; }

  void Insert(Item item, const Vector2d &pos);
  void Remove(Item item);

 private:
  typedef boost::unordered_map<Item, int> QuadrantItems;

  int Quadrant(const Vector2d &pos) const;

  void Split();

  Items items_;
  QuadrantItems quadrant_items_;

  Rectangle rect_;
  Vector2d bottomright_;
  Vector2d center_;

  QuadtreeNode *parent_;
  std::vector<QuadtreeNode> *nodes_;

  int level_;
  int max_items_;
  int item_count_;
};

template<class Item>
class Quadtree : public QuadtreeNode<Item> {
 public:
  explicit Quadtree(const Rectangle &rect, int levels, int max_items = 1)
    : QuadtreeNode<Item>(rect, NULL, levels, max_items) {}
  virtual ~Quadtree() {}
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_QUADTREE_H_

#include "utils/quadtree.cpp"
