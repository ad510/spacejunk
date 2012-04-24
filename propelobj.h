//
// propelobj.h
// 
// author: Andrew Downing
// Header file for propellant object class for Space Junk.
//

#ifndef PROPELOBJ_H
#define PROPELOBJ_H

#include "obj.h"

/** toxic propellant emitted by the player */
class PropelObj : public Obj {
  public:
    PropelObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr);
    virtual void collidePlayer();
    virtual int updateVel();
    virtual ObjType getType() const;
};

#endif
