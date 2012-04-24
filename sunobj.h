//
// sunobj.h
// 
// author: Andrew Downing
// Header file for sun object class for Space Junk.
//

#ifndef SUNOBJ_H
#define SUNOBJ_H

#include "obj.h"

/** sun object (very heavy, so everything generally orbits around it) */
class SunObj : public Obj {
  public:
    SunObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr);
    virtual void collidePlayer();
    virtual ObjType getType() const;
};

#endif
