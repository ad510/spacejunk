//
// missileobj.h
// 
// author: Andrew Downing
// Header file for missile object class for Space Junk.
//

#ifndef MISSILEOBJ_H
#define MISSILEOBJ_H

#include "obj.h"

/** missile object (accelerates itself towards the player) */
class MissileObj : public Obj {
  protected:
    /** amount of propellant left in fuel tank */
    int nPropel;
  public:
    MissileObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr);
    virtual void collidePlayer();
    virtual int updateVel();
    virtual ObjType getType() const;
};

#endif
