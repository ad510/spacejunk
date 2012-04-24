//
// shootmobj.h
// 
// author: Andrew Downing
// Header file for missile shooter object class for Space Junk.
//

#ifndef SHOOTMOBJ_H
#define SHOOTMOBJ_H

#include "obj.h"

/** missile shooter object (shoots missiles at the player) */
class ShootMObj : public Obj {
  protected:
    /** next frame in which object will shoot a missile */
    int shootFrame;
  public:
    ShootMObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr);
    ShootMObj(double maxPos, double minPos, Game *gamePtr);
    virtual void collidePlayer();
    virtual int updateVel();
    virtual void draw();
    virtual ObjType getType() const;
};

#endif
