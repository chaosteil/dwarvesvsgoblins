#ifndef DWARVESVSGOBLINS_SRC_MAP_MAP_TILE_H_
#define DWARVESVSGOBLINS_SRC_MAP_MAP_TILE_H_

namespace dvg {

class Tile {
 public:
  enum Type {
    kNoType = 0,
    kGround = 1,
    kWall = 2
  };

  enum Property {
    kNoProperty = 0,
    kWater = 1,
    kLava = 2,
    kDiggable = 4,
    kClaimable = 8
  }; 

  Tile(Type types, Property properties, int hp, int durability);
  virtual ~Tile();

  void Damage(int damage);

  bool HasType(Type type);
  bool HasProperty(Property property);

  int hp();
  int durability();

 private:
  Type types_;
  Property properties_;

  int hp_;
  int durability_;
};

}  // namespace dvg

#endif  // DWARVESVSGOBLINS_SRC_MAP_MAP_TILE_H
