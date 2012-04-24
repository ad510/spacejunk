//
// hpackobj.h
// 
// author: Andrew Downing
// Header file for health pack object class for Space Junk.
//

#ifndef HPACKOBJ_H
#define HPACKOBJ_H

#include "obj.h"

/** health pack object (restores player's health to maximum level if collected) */
class HPackObj : public Obj {
  public:
    HPackObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr);
    HPackObj(double maxPos, double minPos, Game *gamePtr);
    virtual void collidePlayer();
    virtual void draw();
    virtual ObjType getType() const;
};

#endif
