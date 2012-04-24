//
// planetobj.cpp
// 
// author: Andrew Downing
// Source file for planet object class for Space Junk.
//

#include "planetobj.h"
#include "game.h"

/** constructor for planet object */
PlanetObj::PlanetObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr) : Obj(newX, newY, newXVel, newYVel, PlanetMass, PlanetRadius, gamePtr) { }

/** constructor that puts planet object in random orbit */
PlanetObj::PlanetObj(double maxPos, double minPos, Game *gamePtr) : Obj(maxPos, minPos, PlanetMass, PlanetRadius, gamePtr) { }

/** reduce health when colliding with player */
void PlanetObj::collidePlayer() {
  game->subtHealth(5);
  game->playHitSnd();
}

/** getter for object type */
Obj::ObjType PlanetObj::getType() const {
  return Planet;
}
