//
// playerobj.cpp
// 
// author: Andrew Downing
// Source file for player class for Space Junk.
//

#include "playerobj.h"
#include "propelobj.h"
#include "game.h"

/** constructor for player object */
PlayerObj::PlayerObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr) : Obj(newX, newY, newXVel, newYVel, PlMass, PlRadius, gamePtr) {
  loseFrame = -1;
}

/** accelerate a specified amount by emitting propellant in the opposite direction */
void PlayerObj::emitPropel(double accelX, double accelY) {
  emitObj(Propel, accelX, accelY);
}

/** doesn't do anything (required to implement because is pure virtual function) */
void PlayerObj::collidePlayer() { }

/** update velocity using gravity calculation and delete player some time after losing
    @return index of object collided with */
int PlayerObj::updateVel() {
  if (loseFrame != -1 && game->getFrame() >= loseFrame + 5 * UpdateRate) setDelete(); // delete player and center screen on sun after losing for 5 seconds
  return Obj::updateVel(); // update velocity by calling parent class
}

/** draw image of player (only if hasn't lost) */
void PlayerObj::draw() {
  if (-1 == loseFrame) game->drawObj(getType(), x, y, rotate, false);
}

/** add specified charge to player's charge */
void PlayerObj::addCharge(double amount) {
  charge += amount;
}

/** remember frame that player lost (so player isn't drawn) */
void PlayerObj::setLose() {
  loseFrame = game->getFrame();
}

/** getter for object type */
Obj::ObjType PlayerObj::getType() const {
  return Player;
}
