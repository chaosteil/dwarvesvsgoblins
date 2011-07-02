#ifndef DVG_SRC_UTILS_QUADTREE_H_
#define DVG_SRC_UTILS_QUADTREE_H_

#include <list>
#include <vector>

namespace dvg {
namespace utils {

template<class Item>
class QuadTreeNode {
 public:
  QuadTreeNode(const Vector2d &topleft, const Vector2d &size,
               QuadTreeNode *parent, int level, int max_items)
      : topleft_(topleft), size_(size),
        downright_(topleft_+size_),
        center_(downright_.x()-size_.x()/2, downright_.y()-size_.y()/2),
        parent_(parent), nodes_(NULL),
        level_(level), max_items_(max_items), item_count_(0) {}

  virtual ~QuadTreeNode() {
    if (nodes_ != NULL) {
      delete nodes_;
    }
  }

  int item_count() const { return item_count_; }

  const std::list<Item> &items() const { return items_; }

  void Insert(Item item, const Vector2d &pos) {
    if (level_ > 0 && items_.size() >= max_items_) {
      Split();
      int quadrant = Quadrant(pos);
      nodes_->at(quadrant).Insert(item, pos);
    } else {
      items_.push_back(item);
    }

    item_count_++;
  }

 private:
  int Quadrant(const Vector2d &pos) {
    if (pos.x() < topleft_.x() || pos.x() >= downright_.x() ||
        pos.y() < topleft_.y() || pos.y() >= downright_.y()) {
      return -1;
    }

    if (pos.x() < center_.x()) {
      if (pos.y() < center_.y()) {
        return 0;
      } else {
        return 3;
      }
    } else {
      if (pos.y() < center_.y()) {
        return 1;
      } else {
        return 2;
      }
    }
  }

  void Split() {
    if (!nodes_) {
      nodes_ = new std::vector<QuadTreeNode>();
      Vector2d size(size_.x()/2, size_.y()/2);

      for (int i = 0; i < 4; i++) {
        Vector2d topleft(topleft_.x() + size.x() * (i%2),
                         topleft_.y() + size.y() * (i/2));

        QuadTreeNode node(topleft, size, this, level_-1, max_items_);

        nodes_.push_back(node);
      }
    }
  }

  std::list<Item> items_;

  Vector2d topleft_;
  Vector2d size_;
  Vector2d downright_;
  Vector2d center_;

  QuadTreeNode *parent_;
  std::vector<QuadTreeNode> *nodes_;

  int level_;
  int max_items_;
  int item_count_;
};

template<class Item>
class QuadTree : public QuadTreeNode<Item> {
 public:
  explicit QuadTree(const Vector2d &size, int levels, int max_items = 1)
    : QuadTreeNode<Item>(Vector2d(0, 0), size, NULL, levels, max_items) {}
  virtual ~QuadTree() {}
};

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_QUADTREE_H_
