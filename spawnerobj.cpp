//
// spawnerobj.cpp
// 
// author: Andrew Downing
// Source file for spawner object class for Space Junk.
//

#include "spawnerobj.h"
#include "game.h"

/** set next time to self-reproduce */
void SpawnerObj::resetSpawnFrame() {
  spawnFrame = game->getFrame() + 2000 / (int)UpdateRate + rand() % (3000 / (int)UpdateRate);
}

/** constructor for spawner object */
SpawnerObj::SpawnerObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr) : Obj(newX, newY, newXVel, newYVel, SpawnerMass, SpawnerRadius, gamePtr) {
  resetSpawnFrame();
}

/** constructor that puts spawner object in random orbit */
SpawnerObj::SpawnerObj(double maxPos, double minPos, Game *gamePtr) : Obj(maxPos, minPos, SpawnerMass, SpawnerRadius, gamePtr) {
  resetSpawnFrame();
}

/** explode when colliding with player */
void SpawnerObj::collidePlayer() {
  double diffKE = collide(game->getPlayer());
  explode(15 + diffKE * 50, game->getPlayer());
  setDelete();
}

/** self-reproduce and update velocity using gravity calculation
    @return index of object collided with */
int SpawnerObj::updateVel() {
  if (game->getFrame() >= spawnFrame && game->getNObj(getType()) < 300) {
    emitObj(Spawner, game->randF() * SpawnerAccel * 2 - SpawnerAccel, game->randF() * SpawnerAccel * 2 - SpawnerAccel, true);
    resetSpawnFrame();
  }
  return Obj::updateVel();
}

/** draw image of spawner (always onscreen) */
void SpawnerObj::draw() {
  game->drawObj(getType(), x, y, rotate, true);
}

/** getter for object type */
Obj::ObjType SpawnerObj::getType() const {
  return Spawner;
}
