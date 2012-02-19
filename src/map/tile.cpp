#include "map/tile.h"

namespace dvg {

Tile::Tile(Type types, Property properties, int hp, int durability)
  : types_(types), properties_(properties), hp_(hp), durability_(durability) {

}

Tile::~Tile() {

}

void Tile::Damage(int damage) {
  hp_ -= damage;
}

bool Tile::HasType(Type type) {
  return (bool)(types_ & type);
}

bool Tile::HasProperty(Property property) {
  return (bool)(properties_ & property);
}

int Tile::hp() {
  return hp_;
}

int Tile::durability() {
  return durability_;
}

}  // namespace dvg
