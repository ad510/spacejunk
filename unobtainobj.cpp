//
// unobtainobj.cpp
// Source file for unobtainium object class for Space Junk.
//
// Copyright (c) 2012 Andrew Downing
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#include "unobtainobj.h"
#include "game.h"

/** constructor for unobtainium object */
UnobtainObj::UnobtainObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr) : Obj(newX, newY, newXVel, newYVel, UnobtainMass, UnobtainRadius, gamePtr) { }

/** constructor that puts unobtainium object in random orbit */
UnobtainObj::UnobtainObj(double maxPos, double minPos, Game *gamePtr) : Obj(maxPos, minPos, UnobtainMass, UnobtainRadius, gamePtr) { }

/** be collected when colliding with player */
void UnobtainObj::collidePlayer() {
  game->getPlayer()->addCharge(charge); // add unobtainium's charge to player's charge due to charge conservation
  setDelete(); // technically conservation of momentum says I should add the unobtainium's momentum to the player, but in this case I don't think that's appropriate
  game->playCollectSnd();
}

/** draw image of unobtainium (always onscreen) */
void UnobtainObj::draw() {
  game->drawObj(getType(), x, y, rotate, true);
}

/** getter for object type */
Obj::ObjType UnobtainObj::getType() const {
  return Unobtain;
}
