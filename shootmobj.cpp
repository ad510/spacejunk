//
// shootmobj.cpp
// 
// author: Andrew Downing
// Source file for missile shooter object class for Space Junk.
//

#include "shootmobj.h"
#include "game.h"

/** constructor for missile shooter object */
ShootMObj::ShootMObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr) : Obj(newX, newY, newXVel, newYVel, ShootMMass, ShootMRadius, gamePtr) {
  shootFrame = 0;
}

/** constructor that puts missile shooter object in random orbit */
ShootMObj::ShootMObj(double maxPos, double minPos, Game *gamePtr) : Obj(maxPos, minPos, ShootMMass, ShootMRadius, gamePtr) {
  shootFrame = 0;
}

/** create explosion when colliding with player */
void ShootMObj::collidePlayer() {
  collide(game->getPlayer());
  explode(20, game->getPlayer());
}

/** shoot missile and update velocity using gravity calculation
    @return index of object collided with */
int ShootMObj::updateVel() {
  if (!game->getGameOver() && game->getFrame() >= shootFrame) {
    // shoot missile at player
    double distToPl = sqrt(distSqTo(game->getPlayer()->getX(), game->getPlayer()->getY()));
    emitObj(Missile, (x - game->getPlayer()->getX()) / distToPl * ShootMAccel, (y - game->getPlayer()->getY()) / distToPl * ShootMAccel);
    shootFrame = game->getFrame() + 5000 / (int)UpdateRate + rand() % (5000 / (int)UpdateRate);
  }
  return Obj::updateVel();
}

/** draw image of missile shooter (always onscreen) */
void ShootMObj::draw() {
  game->drawObj(getType(), x, y, rotate, true);
}

/** getter for object type */
Obj::ObjType ShootMObj::getType() const {
  return ShootM;
}
