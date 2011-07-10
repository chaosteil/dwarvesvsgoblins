#ifndef DVG_SRC_UTILS_QUADTREE_CPP_
#define DVG_SRC_UTILS_QUADTREE_CPP_

#include "utils/quadtree.h"

namespace dvg {
namespace utils {

template<class Item>
QuadtreeNode<Item>::QuadtreeNode(const Rectangle &rect,
                                 QuadtreeNode *parent, int level, int max_items)
  : rect_(rect), bottomright_(rect.pos()+rect.size()),
    center_(bottomright_.x()-rect.size().x()/2,
            bottomright_.y()-rect.size().y()/2),
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
void QuadtreeNode<Item>::GetFromRectangle(const Rectangle &rect,
                                          Items *items) const {
  if (!rect.DoesIntersect(rect_)) {
    return;
  }

  typename Items::const_iterator it;
  for (it = items_.begin(); it != items_.end(); ++it) {
    if (rect.IsPositionIn(it->second)) {
      (*items)[it->first] = it->second;
    }
  }

  if (!nodes_) {
    return;
  }

  for (int i = 0; i < 4; i++) {
    nodes_->at(i).GetFromRectangle(rect, items);
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
  if (!rect_.IsPositionIn(pos)) {
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
void QuadtreeNode<Item>::Split() {
  if (!nodes_) {
    nodes_ = new std::vector<QuadtreeNode>();
    Vector2d size(rect_.size().x()/2, rect_.size().y()/2);

    for (int i = 0; i < 4; i++) {
      Rectangle rect(Vector2d(
        rect_.pos().x() + size.x() * (int)(i%2),
        rect_.pos().y() + size.y() * (int)(i/2)),
        size);

      QuadtreeNode node(rect, this, level_-1, max_items_);

      nodes_->push_back(node);
    }
  }
}

}  // namespace utils
}  // namespace dvg

#endif  // DVG_SRC_UTILS_QUADTREE_CPP_
