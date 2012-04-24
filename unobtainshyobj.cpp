//
// unobtainshyobj.cpp
// 
// author: Andrew Downing
// Source file for shy unobtainium object class for Space Junk.
//

#include "unobtainshyobj.h"
#include "game.h"

/** constructor for shy unobtainium object */
UnobtainShyObj::UnobtainShyObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr) : UnobtainObj(newX, newY, newXVel, newYVel, gamePtr) { }

/** constructor that puts shy unobtainium object in random orbit */
UnobtainShyObj::UnobtainShyObj(double maxPos, double minPos, Game *gamePtr) : UnobtainObj(maxPos, minPos, gamePtr) { }

/** avoid player and update velocity using gravity calculation
    @return index of object collided with */
int UnobtainShyObj::updateVel() {
  double distSqToPl = distSqTo(game->getObj(0)->getX(), game->getObj(0)->getY());
  if (!game->getGameOver() && distSqToPl < UnobtainShyAvoidDist * UnobtainShyAvoidDist && game->randF() * 0.1 * UpdateRate < 1) {
    // too close to player, emit propellant to move away
    double distToPl = sqrt(distSqToPl);
    emitObj(Propel, (x - game->getObj(0)->getX()) / distToPl * UnobtainShyAccel, (y - game->getObj(0)->getY()) / distToPl * UnobtainShyAccel);
  }
  return Obj::updateVel();
}

/** getter for object type */
Obj::ObjType UnobtainShyObj::getType() const {
  return UnobtainShy;
}
