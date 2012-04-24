//
// junkobj.cpp
// Source file for space junk object class for Space Junk.
//
// Copyright (c) 2012 Andrew Downing
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#include "junkobj.h"
#include "game.h"

/** constructor for space junk object */
JunkObj::JunkObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr) : Obj(newX, newY, newXVel, newYVel, JunkMass, JunkRadius, gamePtr) { }

/** constructor that puts space junk object in random orbit */
JunkObj::JunkObj(double maxPos, double minPos, Game *gamePtr) : Obj(maxPos, minPos, JunkMass, JunkRadius, gamePtr) { }

/** explode when colliding with player */
void JunkObj::collidePlayer() {
  double diffKE = collide(game->getPlayer());
  explode(15 + diffKE * 50, game->getPlayer());
  setDelete();
}

/** accelerate randomly and update velocity using gravity calculation
    @return index of object collided with */
int JunkObj::updateVel() {
  if (game->randF() * 3 * UpdateRate < 1) {
    emitObj(Propel, game->randF() * JunkAccel * 2 - JunkAccel, game->randF() * JunkAccel * 2 - JunkAccel);
  }
  return Obj::updateVel();
}

/** draw image of space junk (always onscreen) */
void JunkObj::draw() {
  game->drawObj(getType(), x, y, rotate, true);
}

/** getter for object type */
Obj::ObjType JunkObj::getType() const {
  return Junk;
}
