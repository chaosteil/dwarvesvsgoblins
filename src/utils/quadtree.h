#ifndef DVG_SRC_UTILS_QUADTREE_H_
#define DVG_SRC_UTILS_QUADTREE_H_

#include <vector>
#include <boost/unordered_map.hpp>
#include "utils/vector2d.h"

namespace dvg {
namespace utils {

template<class Item>
class QuadtreeNode {
 public:
  typedef boost::unordered_map<Item, Vector2d> Items;

  QuadtreeNode(const Vector2d &topleft, const Vector2d &size,
               QuadtreeNode *parent, int level, int max_items);
  virtual ~QuadtreeNode();

  void GetFromPosition(const Vector2d &pos, Items *items) const;
  // TODO: Use proper rectangle class
  void GetFromRectangle(const Vector2d &topleft, const Vector2d &size,
                        Items *items) const;

  int item_count() const { return item_count_; }

  const Vector2d topleft() const { return topleft_; }
  const Vector2d size() const { return size_; }

  void Insert(Item item, const Vector2d &pos);
  void Remove(Item item);

 private:
  typedef boost::unordered_map<Item, int> QuadrantItems;

  int Quadrant(const Vector2d &pos) const;
  bool Intersects(const Vector2d &topleft, const Vector2d &size) const;
  bool IsPositionIn(const Vector2d &pos, const Vector2d &topleft,
                    const Vector2d &size) const;

  void Split();

  Items items_;
  QuadrantItems quadrant_items_;

  Vector2d topleft_;
  Vector2d size_;
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
  explicit Quadtree(const Vector2d &size, int levels, int max_items = 1)
    : QuadtreeNode<Item>(Vector2d(0, 0), size, NULL, levels, max_items) {}
  virtual ~Quadtree() {}
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_QUADTREE_H_

#include "utils/quadtree.cpp"
