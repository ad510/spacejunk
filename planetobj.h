//
// planetobj.h
// 
// author: Andrew Downing
// Header file for planet object class for Space Junk.
//

#ifndef PLANETOBJ_H
#define PLANETOBJ_H

#include "obj.h"

/** planet object (an obstacle for the player to avoid) */
class PlanetObj : public Obj {
  public:
    PlanetObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr);
    PlanetObj(double maxPos, double minPos, Game *gamePtr);
    virtual void collidePlayer();
    virtual ObjType getType() const;
};

#endif
