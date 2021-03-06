//
// sunobj.cpp
// Source file for sun object class for Space Junk.
//
// Copyright (c) 2012 Andrew Downing
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#include "sunobj.h"
#include "game.h"

/** constructor for sun object */
SunObj::SunObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr) : Obj(newX, newY, newXVel, newYVel, SunMass, SunRadius, gamePtr) { }

/** make solar flare (explosion) when colliding with player */
void SunObj::collidePlayer() {
  game->getPlayer()->explode(SunFlareSize, game->getPlayer(), 10);
  mass -= SunFlareSize * PrMass; // we can afford to conserve mass here
  accel((game->getPlayer()->getXVel() - xVel) * PrMass / mass * SunFlareSize,
        (game->getPlayer()->getYVel() - yVel) * PrMass / mass * SunFlareSize); // conserve momentum as well (yes I know this makes almost no difference)
}

/** getter for object type */
Obj::ObjType SunObj::getType() const {
  return Sun;
}
