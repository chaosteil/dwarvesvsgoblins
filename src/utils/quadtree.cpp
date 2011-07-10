#ifndef DVG_SRC_UTILS_QUADTREE_CPP_
#define DVG_SRC_UTILS_QUADTREE_CPP_

#include "utils/quadtree.h"

namespace dvg {
namespace utils {

template<class Item>
QuadtreeNode<Item>::QuadtreeNode(const Vector2d &topleft, const Vector2d &size,
                                 QuadtreeNode *parent, int level, int max_items)
  : topleft_(topleft), size_(size), bottomright_(topleft_+size_),
    center_(bottomright_.x()-size_.x()/2, bottomright_.y()-size_.y()/2),
    parent_(parent), nodes_(NULL),
    level_(level), max_items_(max_items), item_count_(0) {}

template<class Item>
QuadtreeNode<Item>::~QuadtreeNode() {
  if (nodes_ != NULL) {
    delete nodes_;
  }
}

template<class Item>
void QuadtreeNode<Item>::GetFromPosition(const Vector2d &pos,
                                         Items *items) const {
  int quadrant = Quadrant(pos);

  if (quadrant < 0) {
    return;
  }

  typename Items::const_iterator it;
  for (it = items_.begin(); it != items_.end(); ++it) {
    if (it->second == pos) {
      (*items)[it->first] = pos;
    }
  }

  if (!nodes_) {
    return;
  }

  for (int i = 0; i < 4; i++) {
    nodes_->at(i).GetFromPosition(pos, items);
  }
}

template<class Item>
void QuadtreeNode<Item>::GetFromRectangle(const Vector2d &topleft,
                                          const Vector2d &size,
                                          Items *items) const {
  if (!Intersects(topleft, size)) {
    return;
  }

  typename Items::const_iterator it;
  for (it = items_.begin(); it != items_.end(); ++it) {
    if (IsPositionIn(it->second, topleft, size)) {
      (*items)[it->first] = it->second;
    }
  }

  if (!nodes_) {
    return;
  }

  for (int i = 0; i < 4; i++) {
    nodes_->at(i).GetFromRectangle(topleft, size, items);
  }
}

template<class Item>
void QuadtreeNode<Item>::Insert(Item item, const Vector2d &pos) {
  if (quadrant_items_.find(item) != quadrant_items_.end()) {
    Remove(item); 
  }

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
void QuadtreeNode<Item>::Remove(Item item) {
  typename QuadrantItems::iterator it = quadrant_items_.find(item);

  if (it == quadrant_items_.end()) {
    return;
  }

  item_count_--;

  int quadrant = it->second;
  if (quadrant < 0) {
    quadrant_items_.erase(item);
    items_.erase(item);
  } else {
    nodes_->at(quadrant).Remove(item);
  }
}

template<class Item>
int QuadtreeNode<Item>::Quadrant(const Vector2d &pos) const {
  if (pos.x() < topleft_.x() || pos.x() >= bottomright_.x() ||
      pos.y() < topleft_.y() || pos.y() >= bottomright_.y()) {
    return -1;
  }

  if (pos.x() < center_.x()) {
    if (pos.y() < center_.y()) {
      return 0;  // Top Left
    } else {
      return 2;  // Bottom Left
    }
  } else {
    if (pos.y() < center_.y()) {
      return 1;  // Top Right
    } else {
      return 3;  // Bottom Right
    }
  }
}

template<class Item>
bool QuadtreeNode<Item>::Intersects(const Vector2d &topleft,
                                    const Vector2d &size) const {
  Vector2d bottomright = topleft+size;

  if (topleft_.x() < bottomright.x() && bottomright_.x() > topleft.x() &&
      topleft_.y() < bottomright.y() && bottomright_.y() > topleft.y()) {
    return true;
  } else {
    return false;
  }
}

template<class Item>
bool QuadtreeNode<Item>::IsPositionIn(const Vector2d &pos,
                                      const Vector2d &topleft,
                                      const Vector2d &size) const {
  Vector2d bottomright = topleft+size;

  if (topleft.x() <= pos.x() && topleft.y() <= pos.y() &&
      bottomright.x() >= pos.x() && bottomright.y() >= pos.y()) {
    return true;
  } else {
    return false;
  }
}

template<class Item>
void QuadtreeNode<Item>::Split() {
  if (!nodes_) {
    nodes_ = new std::vector<QuadtreeNode>();
    Vector2d size(size_.x()/2, size_.y()/2);

    for (int i = 0; i < 4; i++) {
      Vector2d topleft(topleft_.x() + size.x() * (int)(i%2),
                       topleft_.y() + size.y() * (int)(i/2));

      QuadtreeNode node(topleft, size, this, level_-1, max_items_);

      nodes_->push_back(node);
    }
  }
}

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_QUADTREE_CPP_
