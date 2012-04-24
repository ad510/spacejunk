//
// hpackchgobj.cpp
// 
// author: Andrew Downing
// Source file for charged health pack object class for Space Junk.
//

#include "hpackchgobj.h"
#include "game.h"

/** constructor for charged health pack object */
HPackChgObj::HPackChgObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr) : HPackObj(newX, newY, newXVel, newYVel, gamePtr) {
  charge = HPackChgCharge; // behavior for charged objects handled in obj.cpp, so this source file can be short
}

/** constructor that puts charged health pack object in random orbit */
HPackChgObj::HPackChgObj(double maxPos, double minPos, Game *gamePtr) : HPackObj(maxPos, minPos, gamePtr) {
  charge = HPackChgCharge;
}

/** getter for object type */
Obj::ObjType HPackChgObj::getType() const {
  return HPackChg;
}
