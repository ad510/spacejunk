//
// junkobj.cpp
// 
// author: Andrew Downing
// Source file for space junk object class for Space Junk.
//

#include "junkobj.h"
#include "game.h"

/** constructor for space junk object */
JunkObj::JunkObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr) : Obj(newX, newY, newXVel, newYVel, JunkMass, JunkRadius, gamePtr) { }

/** constructor that puts space junk object in random orbit */
JunkObj::JunkObj(double maxPos, double minPos, Game *gamePtr) : Obj(maxPos, minPos, JunkMass, JunkRadius, gamePtr) { }

/** explode when colliding with player */
void JunkObj::collidePlayer() {
  double diffKE = collide(game->getPlayer());
  explode(15 + diffKE * 50, game->getPlayer());
  setDelete();
}

/** accelerate randomly and update velocity using gravity calculation
    @return index of object collided with */
int JunkObj::updateVel() {
  if (game->randF() * 3 * UpdateRate < 1) {
    emitObj(Propel, game->randF() * JunkAccel * 2 - JunkAccel, game->randF() * JunkAccel * 2 - JunkAccel);
  }
  return Obj::updateVel();
}

/** draw image of space junk (always onscreen) */
void JunkObj::draw() {
  game->drawObj(getType(), x, y, rotate, true);
}

/** getter for object type */
Obj::ObjType JunkObj::getType() const {
  return Junk;
}
