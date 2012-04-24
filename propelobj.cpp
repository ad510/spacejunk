//
// propelobj.cpp
// Source file for propellant object class for Space Junk.
//
// Copyright (c) 2012 Andrew Downing
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
