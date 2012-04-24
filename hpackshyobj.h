//
// hpackshyobj.h
// 
// author: Andrew Downing
// Header file for shy health pack object class for Space Junk.
//

#ifndef HPACKSHYOBJ_H
#define HPACKSHYOBJ_H

#include "hpackobj.h"

/** shy health pack object (health pack that emits propellent to avoid player) */
class HPackShyObj : public HPackObj {
  public:
    HPackShyObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr);
    HPackShyObj(double maxPos, double minPos, Game *gamePtr);
    virtual int updateVel();
    virtual ObjType getType() const;
};

#endif
