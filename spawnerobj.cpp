//
// spawnerobj.cpp
// Source file for spawner object class for Space Junk.
//
// Copyright (c) 2012 Andrew Downing
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
