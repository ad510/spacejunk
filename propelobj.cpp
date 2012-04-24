//
// propelobj.cpp
// 
// author: Andrew Downing
// Source file for propellant object class for Space Junk.
//

#include "propelobj.h"
#include "game.h"

/** constructor for propellant object */
PropelObj::PropelObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr) : Obj(newX, newY, newXVel, newYVel, PrMass, PrRadius, gamePtr) { }

/** reduce health when colliding with player */
void PropelObj::collidePlayer() {
  game->subtHealth(3);
  game->playHitSnd();
}

/** update velocity using gravity calculation and remove any space junk colliding with
    @return index of object collided with */
int PropelObj::updateVel() {
  int collided = Obj::updateVel();
  if (collided >= 0 && (Junk == game->getObj(collided)->getType() || Spawner == game->getObj(collided)->getType()) && !game->getObj(collided)->getDelete()) {
    // propellant collided with space junk/spawner, explode space junk/spawner
    collide(game->getObj(collided));
    explode((Junk == game->getObj(collided)->getType()) ? 10 : 2, game->getObj(collided));
    game->getObj(collided)->setDelete();
    setDelete();
  }
  return collided;
}

/** getter for object type */
Obj::ObjType PropelObj::getType() const {
  return Propel;
}
