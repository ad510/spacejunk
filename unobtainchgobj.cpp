//
// unobtainchgobj.cpp
// 
// author: Andrew Downing
// Source file for charged unobtainium object class for Space Junk.
//

#include "unobtainchgobj.h"
#include "game.h"

/** constructor for charged unobtainium object */
UnobtainChgObj::UnobtainChgObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr) : UnobtainObj(newX, newY, newXVel, newYVel, gamePtr) {
  charge = UnobtainChgCharge; // behavior for charged objects handled in obj.cpp, so this source file can be short
}

/** constructor that puts charged unobtainium object in random orbit */
UnobtainChgObj::UnobtainChgObj(double maxPos, double minPos, Game *gamePtr) : UnobtainObj(maxPos, minPos, gamePtr) {
  charge = UnobtainChgCharge;
}

/** getter for object type */
Obj::ObjType UnobtainChgObj::getType() const {
  return UnobtainChg;
}
