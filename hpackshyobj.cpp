//
// hpackshyobj.cpp
// 
// author: Andrew Downing
// Source file for shy health pack object class for Space Junk.
//

#include "hpackshyobj.h"
#include "game.h"

/** constructor for shy health pack object */
HPackShyObj::HPackShyObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr) : HPackObj(newX, newY, newXVel, newYVel, gamePtr) { }

/** constructor that puts shy health pack object in random orbit */
HPackShyObj::HPackShyObj(double maxPos, double minPos, Game *gamePtr) : HPackObj(maxPos, minPos, gamePtr) { }

/** avoid player and update velocity using gravity calculation
    @return index of object collided with */
int HPackShyObj::updateVel() {
  double distSqToPl = distSqTo(game->getPlayer()->getX(), game->getPlayer()->getY());
  if (!game->getGameOver() && distSqToPl < HPackShyAvoidDist * HPackShyAvoidDist && game->randF() * 0.1 * UpdateRate < 1) {
    // too close to player, emit propellant to move away
    double distToPl = sqrt(distSqToPl);
    emitObj(Propel, (x - game->getPlayer()->getX()) / distToPl * HPackShyAccel, (y - game->getPlayer()->getY()) / distToPl * HPackShyAccel);
  }
  return Obj::updateVel();
}

/** getter for object type */
Obj::ObjType HPackShyObj::getType() const {
  return HPackShy;
}
