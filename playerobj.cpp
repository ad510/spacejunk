//
// playerobj.cpp
// Source file for player class for Space Junk.
//
// Copyright (c) 2012 Andrew Downing
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#include "playerobj.h"
#include "propelobj.h"
#include "game.h"

/** constructor for player object */
PlayerObj::PlayerObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr) : Obj(newX, newY, newXVel, newYVel, PlMass, PlRadius, gamePtr) {
  loseFrame = -1;
}

/** accelerate a specified amount by emitting propellant in the opposite direction */
void PlayerObj::emitPropel(double accelX, double accelY) {
  emitObj(Propel, accelX, accelY);
}

/** doesn't do anything (required to implement because is pure virtual function) */
void PlayerObj::collidePlayer() { }

/** update velocity using gravity calculation and delete player some time after losing
    @return index of object collided with */
int PlayerObj::updateVel() {
  int collided = Obj::updateVel(); // update velocity by calling parent class
  if (loseFrame != -1 && (game->getFrame() >= loseFrame + 5 * UpdateRate || (collided > 0 && Sun == game->getObj(collided)->getType()))) setDelete(); // delete player and center screen on sun after losing for 5 seconds
  return collided;
}

/** draw image of player (only if hasn't lost) */
void PlayerObj::draw() {
  if (-1 == loseFrame) game->drawObj(getType(), x, y, rotate, false);
}

/** add specified charge to player's charge */
void PlayerObj::addCharge(double amount) {
  charge += amount;
}

/** remember frame that player lost (so player isn't drawn) */
void PlayerObj::setLose() {
  loseFrame = game->getFrame();
}

/** getter for object type */
Obj::ObjType PlayerObj::getType() const {
  return Player;
}
