//
// unobtainobj.cpp
// 
// author: Andrew Downing
// Source file for unobtainium object class for Space Junk.
//

#include "unobtainobj.h"
#include "game.h"

/** constructor for unobtainium object */
UnobtainObj::UnobtainObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr) : Obj(newX, newY, newXVel, newYVel, UnobtainMass, UnobtainRadius, gamePtr) { }

/** constructor that puts unobtainium object in random orbit */
UnobtainObj::UnobtainObj(double maxPos, double minPos, Game *gamePtr) : Obj(maxPos, minPos, UnobtainMass, UnobtainRadius, gamePtr) { }

/** be collected when colliding with player */
void UnobtainObj::collidePlayer() {
  game->getPlayer()->addCharge(charge); // add unobtainium's charge to player's charge due to charge conservation
  setDelete(); // technically conservation of momentum says I should add the unobtainium's momentum to the player, but in this case I don't think that's appropriate
  game->playCollectSnd();
}

/** draw image of unobtainium (always onscreen) */
void UnobtainObj::draw() {
  game->drawObj(getType(), x, y, rotate, true);
}

/** getter for object type */
Obj::ObjType UnobtainObj::getType() const {
  return Unobtain;
}
