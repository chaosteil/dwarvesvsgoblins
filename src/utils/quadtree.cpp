#ifndef DVG_SRC_UTILS_QUADTREE_CPP_
#define DVG_SRC_UTILS_QUADTREE_CPP_

#include "utils/quadtree.h"

namespace dvg {
namespace utils {

template<class Item>
QuadTreeNode<Item>::QuadTreeNode(const Vector2d &topleft, const Vector2d &size,
                                 QuadTreeNode *parent, int level, int max_items)
  : topleft_(topleft), size_(size), bottomright_(topleft_+size_),
    center_(bottomright_.x()-size_.x()/2, bottomright_.y()-size_.y()/2),
    parent_(parent), nodes_(NULL),
    level_(level), max_items_(max_items), item_count_(0) {}

template<class Item>
QuadTreeNode<Item>::~QuadTreeNode() {
  if (nodes_ != NULL) {
    delete nodes_;
  }
}

template<class Item>
void QuadTreeNode<Item>::Insert(Item item, const Vector2d &pos) {
  if (level_ > 0 && items_.size() >= max_items_) {
    Split();
    int quadrant = Quadrant(pos);
    quadrant_items_[item] = quadrant;

    nodes_->at(quadrant).Insert(item, pos);
  } else {
    quadrant_items_[item] = -1;

    items_[item] = pos;
  }

  item_count_++;
}

template<class Item>
void QuadTreeNode<Item>::Remove(Item item) {
  typename QuadrantItems::iterator it = quadrant_items_.find(item);

  if (it == quadrant_items_.end()) {
    return;
  }

  item_count_--;

  int quadrant = *it;
  if (quadrant < 0) {
    quadrant_items_.erase(item);
  } else {
    nodes_->at(quadrant).Remove(item);
  }
}

template<class Item>
int QuadTreeNode<Item>::Quadrant(const Vector2d &pos) {
  if (pos.x() < topleft_.x() || pos.x() >= bottomright_.x() ||
      pos.y() < topleft_.y() || pos.y() >= bottomright_.y()) {
    return -1;
  }

  if (pos.x() < center_.x()) {
    if (pos.y() < center_.y()) {
      return 0;  // Top Left
    } else {
      return 3;  // Bottom Left
    }
  } else {
    if (pos.y() < center_.y()) {
      return 1;  // Top Right
    } else {
      return 2;  // Bottom Right
    }
  }
}

template<class Item>
void QuadTreeNode<Item>::Split() {
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

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_QUADTREE_CPP_
