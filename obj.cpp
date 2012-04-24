//
// obj.cpp
// Source file for game object class for Space Junk.
//
// Copyright (c) 2012 Andrew Downing
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#include "obj.h"
#include "game.h"

/** constructor for game object */
Obj::Obj(double newX, double newY, double newXVel, double newYVel, double newMass, double newRadius, Game *gamePtr) {
  x = newX;
  y = newY;
  xVel = newXVel;
  yVel = newYVel;
  mass = newMass;
  charge = 0; // object constructors can set this manually if they need it
  radius = newRadius;
  rotateAim = 0;
  rotate = 0;
  collidedPlLast = false;
  del = false;
  game = gamePtr;
}

/** constructor that puts game object in random orbit */
Obj::Obj(double maxPos, double minPos, double newMass, double newRadius, Game *gamePtr) {
  double pos = minPos + (maxPos - minPos) * sqrt(gamePtr->randF());
  // circular orbit velocity formula from https://en.wikipedia.org/wiki/Circular_orbit#Velocity
  // escape velocity formula from https://en.wikipedia.org/wiki/Escape_velocity
  double vel = UpdateRate * sqrt(SunMass / pos) * (gamePtr->randF() * 0.5 + 0.5) * ((rand() % 2) ? 1 : -1);
  double angle = 2 * M_PI * gamePtr->randF();
  x = pos * cos(angle);
  y = pos * sin(angle);
  xVel = vel * -sin(angle);
  yVel = vel * cos(angle);
  mass = newMass;
  charge = 0; // object constructors can set this manually if they need it
  radius = newRadius;
  rotateAim = 0;
  rotate = 0;
  collidedPlLast = false;
  del = false;
  game = gamePtr;
}

/** change velocity by specified amount */
void Obj::accel(double xAccel, double yAccel) {
  xVel += xAccel;
  yVel += yAccel;
}

/** accelerate a specified amount by emitting an object in the opposite direction
    @param centered optional parameter indicating whether object should be emitted at the center of this object instead of outside it */
void Obj::emitObj(Obj::ObjType emitType, double xAccel, double yAccel, bool centered) {
  // emit object at a velocity that conserves momentum from the frame of reference of this object before the emission
  Obj *tempObj = game->newObj(emitType, 0, 0, 0, 0); // temporary object so we can get properties of this object type
  Obj *eObj = game->newObj(emitType, (centered ? x : x - xAccel / sqrt(xAccel * xAccel + yAccel * yAccel) * (radius + tempObj->getRadius() + 1)),
                           (centered ? y : y - yAccel / sqrt(xAccel * xAccel + yAccel * yAccel) * (radius + tempObj->getRadius() + 1)),
                           -xAccel * mass / tempObj->getMass() + xVel, -yAccel * mass / tempObj->getMass() + yVel);
  game->addObj(eObj);
  delete tempObj;
  // accelerate object due to recoil
  accel(xAccel, yAccel);
  if (!centered) {
    // set image target rotation
    rotateAim = atan2(xAccel, -yAccel);
    if (rotateAim - rotate > M_PI) rotate += M_PI * 2;
    if (rotateAim - rotate < -M_PI) rotate -= M_PI * 2;
  }
}

/** create explosion of propellant between obj and this object */
void Obj::explode(int nParticle, Obj *obj, double maxSpd) {
  Obj *eObj[nParticle];
  double tempXVel, tempYVel, avgXVel = 0, avgYVel = 0;
  int i;
  // create propellant with random velocities up to maxSpd
  for (i = 0; i < nParticle; i++) {
    do {
      tempXVel = game->randF() * maxSpd * 2 - maxSpd;
      tempYVel = game->randF() * maxSpd * 2 - maxSpd;
    } while (tempXVel * tempXVel + tempYVel * tempYVel > maxSpd * maxSpd); // make sure velocity fits inside circle
    eObj[i] = game->newObj(Propel, x + (obj->getX() - x) * radius / (radius + obj->getRadius()),
                           y + (obj->getY() - y) * radius / (radius + obj->getRadius()),
                           (xVel + obj->getXVel()) / 2 + tempXVel, (yVel + obj->getYVel()) / 2 + tempYVel);
    game->addObj(eObj[i]);
    avgXVel += tempXVel;
    avgYVel += tempYVel;
  }
  avgXVel /= nParticle;
  avgYVel /= nParticle;
  // ensure average velocity of explosion particles is 0 from explosion's frame of reference (to conserve momentum from explosion's frame of reference)
  for (i = 0; i < nParticle; i++) {
    eObj[i]->accel(-avgXVel, -avgYVel);
  }
  if (game->getPlayer() == obj || game->getPlayer() == this) {
    // play sound
    game->playExplodeSnd();
  }
}

/** have an inelastic collision with specified object (objects stick together)
    @return change in kinetic energy of the other object */
double Obj::collide(Obj *obj) {
  double diffKE;
  xVel = (xVel * mass + obj->getXVel() * obj->getMass()) / (mass + obj->getMass());
  yVel = (yVel * mass + obj->getYVel() * obj->getMass()) / (mass + obj->getMass());
  diffKE = obj->getMass() * (pow(xVel - obj->getXVel(), 2) + pow(yVel - obj->getYVel(), 2));
  obj->accel(xVel - obj->getXVel(), yVel - obj->getYVel());
  return diffKE;
}

/** update velocity using gravity and electrostatic force calculation
    @return index of object collided with */
int Obj::updateVel() {
  double xAccel = 0, yAccel = 0, distSq, temp;
  int collided = -1;
  // check for collision with player
  if (!game->getGameOver() && this != game->getPlayer()) {
    bool collidedPl = game->getPlayer()->distSqTo(x, y) < pow(radius + game->getPlayer()->getRadius(), 2);
    if (collidedPl && !collidedPlLast) collidePlayer();
    collidedPlLast = collidedPl;
  }
  // calculate acceleration due to gravity and electrostatic force on object
  for (int i = 0; i < game->getNObj(); i++) {
    if (game->getObj(i) == this) continue; // skip object if it is us
    distSq = game->getObj(i)->distSqTo(x, y);
    if (distSq < pow(radius + game->getObj(i)->getRadius(), 2)) {
      if (collided < 0) {
        collided = i; // object is at this position
      }
    }
    else {
      temp = (game->getObj(i)->getMass() - charge * game->getObj(i)->getCharge() / mass) / pow(distSq, 1.5); // derived from universal law of gravitation and Coulomb's law
      xAccel += (game->getObj(i)->getX() - x) * temp;
      yAccel += (game->getObj(i)->getY() - y) * temp;
    }
  }
  xAccel *= UpdateRate * UpdateRate;
  yAccel *= UpdateRate * UpdateRate;
  // accelerate object due to gravity and electrostatic force
  accel(xAccel, yAccel);
  return collided;
}

/** update position by current velocity */
void Obj::updatePos() {
  x += xVel;
  y += yVel;
  rotate = rotateAim * 0.15 + rotate * 0.85; // smoothly rotate to targeted angle
}

/** draw image of object */
void Obj::draw() {
  game->drawObj(getType(), x, y, rotate, false);
}

/** mark object for deletion in this frame */
void Obj::setDelete() {
  del = true;
}

/** @return square of distance between (toX, toY) and this object */
double Obj::distSqTo(double toX, double toY) const {
  return pow(toX - x, 2) + pow(toY - y, 2);
}

/** getter for x */
double Obj::getX() const {
  return x;
}

/** getter for y */
double Obj::getY() const {
  return y;
}

/** getter for x velocity */
double Obj::getXVel() const {
  return xVel;
}

/** getter for y velocity */
double Obj::getYVel() const {
  return yVel;
}

/** getter for mass */
double Obj::getMass() const {
  return mass;
}

/** getter for charge */
double Obj::getCharge() const {
  return charge;
}

/** getter for radius */
double Obj::getRadius() const {
  return radius;
}

/** getter for deletion flag */
bool Obj::getDelete() const {
  return del;
}
