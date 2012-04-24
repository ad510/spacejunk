//
// sunobj.cpp
// 
// author: Andrew Downing
// Source file for sun object class for Space Junk.
//

#include "sunobj.h"
#include "game.h"

/** constructor for sun object */
SunObj::SunObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr) : Obj(newX, newY, newXVel, newYVel, SunMass, SunRadius, gamePtr) { }

/** make solar flare (explosion) when colliding with player */
void SunObj::collidePlayer() {
  game->getPlayer()->explode(SunFlareSize, game->getPlayer(), 10);
  mass -= SunFlareSize * PrMass; // we can afford to conserve mass here
  accel((game->getPlayer()->getXVel() - xVel) * PrMass / mass * SunFlareSize,
        (game->getPlayer()->getYVel() - yVel) * PrMass / mass * SunFlareSize); // conserve momentum as well (yes I know this makes almost no difference)
}

/** getter for object type */
Obj::ObjType SunObj::getType() const {
  return Sun;
}
