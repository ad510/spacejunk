//
// unobtainobj.h
// 
// author: Andrew Downing
// Header file for unobtainium object class for Space Junk.
//

#ifndef UNOBTAINOBJ_H
#define UNOBTAINOBJ_H

#include "obj.h"

/** unobtainium object (collecting all of these is a requirement to win) */
class UnobtainObj : public Obj {
  public:
    UnobtainObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr);
    UnobtainObj(double maxPos, double minPos, Game *gamePtr);
    virtual void collidePlayer();
    virtual void draw();
    virtual ObjType getType() const;
};

#endif
