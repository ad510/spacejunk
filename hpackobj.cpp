//
// hpackobj.cpp
// 
// author: Andrew Downing
// Source file for health pack object class for Space Junk.
//

#include "hpackobj.h"
#include "game.h"

/** constructor for health pack object */
HPackObj::HPackObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr) : Obj(newX, newY, newXVel, newYVel, HPackMass, HPackRadius, gamePtr) { }

/** constructor that puts health pack object in random orbit */
HPackObj::HPackObj(double maxPos, double minPos, Game *gamePtr) : Obj(maxPos, minPos, HPackMass, HPackRadius, gamePtr) { }

/** give player max health when colliding with player */
void HPackObj::collidePlayer() {
  game->setMaxHealth();
  game->getPlayer()->addCharge(charge); // add health pack's charge to player's charge due to charge conservation
  setDelete(); // technically conservation of momentum says I should add the health pack's momentum to the player, but in this case I don't think that's appropriate
  game->playCollectSnd();
}

/** draw image of health pack (always onscreen) */
void HPackObj::draw() {
  game->drawObj(getType(), x, y, rotate, true);
}

/** getter for object type */
Obj::ObjType HPackObj::getType() const {
  return HPack;
}
