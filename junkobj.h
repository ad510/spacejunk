//
// junkobj.h
// 
// author: Andrew Downing
// Header file for space junk object class for Space Junk.
//

#ifndef JUNKOBJ_H
#define JUNKOBJ_H

#include "obj.h"

/** space junk object (hitting this with propellent is a requirement to win) */
class JunkObj : public Obj {
  public:
    JunkObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr);
    JunkObj(double maxPos, double minPos, Game *gamePtr);
    virtual void collidePlayer();
    virtual int updateVel();
    virtual void draw();
    virtual ObjType getType() const;
};

#endif
