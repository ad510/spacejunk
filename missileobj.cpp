//
// missileobj.cpp
// 
// author: Andrew Downing
// Source file for missile object class for Space Junk.
//

#include "missileobj.h"
#include "game.h"

/** constructor for missile object */
MissileObj::MissileObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr) : Obj(newX, newY, newXVel, newYVel, MissileMass, MissileRadius, gamePtr) {
  nPropel = MissileMaxPropel;
}

/** explode when colliding with player */
void MissileObj::collidePlayer() {
  double diffKE = collide(game->getPlayer());
  explode(5 + diffKE * 50, game->getPlayer());
  setDelete();
}

/** accelerate towards player, update velocity using gravity calculation, and remove any missile shooter colliding with
    @return index of object collided with */
int MissileObj::updateVel() {
  int collided;
  // make emission rate proportional to propellant remaining
  if (!game->getGameOver() && game->randF() * 0.1 * UpdateRate < nPropel / MissileMaxPropel && (game->getPlayer()->getX() != x || game->getPlayer()->getY() != y)) {
    double xTarget = game->getPlayer()->getX();
    double yTarget = game->getPlayer()->getY();
    // reduce mass due to ejected propellent
    nPropel--;
    mass = MissileEmptyMass + (MissileMass - MissileEmptyMass) * nPropel / MissileMaxPropel;
    if (game->getPlayer()->getXVel() != xVel || game->getPlayer()->getYVel() != yVel) {
      // find where player would be if missile moved in current direction (relative to player) for a distance slightly less than its distance to the player
      // this is sort of an estimate of where player will be by the time missile arrives at player's current location
      double timeToPl = 0.9 * sqrt(distSqTo(xTarget, yTarget) / (pow(game->getPlayer()->getXVel() - xVel, 2) + pow(game->getPlayer()->getYVel() - yVel, 2))); // time = distance / speed
      xTarget += (game->getPlayer()->getXVel() - xVel) * timeToPl; // distance = speed * time
      yTarget += (game->getPlayer()->getYVel() - yVel) * timeToPl;
    }
    // emit propellant to accelerate missile to target pos
    double distToTarget = sqrt(distSqTo(xTarget, yTarget));
    emitObj(Propel, (xTarget - x) / distToTarget * MissileAccel * MissileMass / mass, (yTarget - y) / distToTarget * MissileAccel * MissileMass / mass);
  }
  collided = Obj::updateVel();
  if (collided >= 0 && ShootM == game->getObj(collided)->getType()) {
    // missile collided with missile shooter, explode and remove missile shooter and self
    collide(game->getObj(collided));
    explode(35, game->getObj(collided));
    game->getObj(collided)->setDelete();
    setDelete();
  }
  return collided;
}

/** getter for object type */
Obj::ObjType MissileObj::getType() const {
  return Missile;
}
