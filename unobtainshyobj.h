//
// unobtainshyobj.h
// 
// author: Andrew Downing
// Header file for shy unobtainium object class for Space Junk.
//

#ifndef UNOBTAINSHYOBJ_H
#define UNOBTAINSHYOBJ_H

#include "unobtainobj.h"

/** shy unobtainium object (unobtainium that emits propellent to avoid player) */
class UnobtainShyObj : public UnobtainObj {
  public:
    UnobtainShyObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr);
    UnobtainShyObj(double maxPos, double minPos, Game *gamePtr);
    virtual int updateVel();
    virtual ObjType getType() const;
};

#endif
