//
// hpackshyobj.cpp
// Source file for shy health pack object class for Space Junk.
//
// Copyright (c) 2012 Andrew Downing
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#include "hpackshyobj.h"
#include "game.h"

/** constructor for shy health pack object */
HPackShyObj::HPackShyObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr) : HPackObj(newX, newY, newXVel, newYVel, gamePtr) { }

/** constructor that puts shy health pack object in random orbit */
HPackShyObj::HPackShyObj(double maxPos, double minPos, Game *gamePtr) : HPackObj(maxPos, minPos, gamePtr) { }

/** avoid player and update velocity using gravity calculation
    @return index of object collided with */
int HPackShyObj::updateVel() {
  double distSqToPl = distSqTo(game->getPlayer()->getX(), game->getPlayer()->getY());
  if (!game->getGameOver() && distSqToPl < HPackShyAvoidDist * HPackShyAvoidDist && game->randF() * 0.1 * UpdateRate < 1) {
    // too close to player, emit propellant to move away
    double distToPl = sqrt(distSqToPl);
    emitObj(Propel, (x - game->getPlayer()->getX()) / distToPl * HPackShyAccel, (y - game->getPlayer()->getY()) / distToPl * HPackShyAccel);
  }
  return Obj::updateVel();
}

/** getter for object type */
Obj::ObjType HPackShyObj::getType() const {
  return HPackShy;
}
