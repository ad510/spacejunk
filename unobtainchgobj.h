//
// unobtainchgobj.h
// 
// author: Andrew Downing
// Header file for charged unobtainium object class for Space Junk.
//

#ifndef UNOBTAINCHGOBJ_H
#define UNOBTAINCHGOBJ_H

#include "unobtainobj.h"

/** charged unobtainium object (repels charged objects, including player if player has collected charged objects) */
class UnobtainChgObj : public UnobtainObj {
  public:
    UnobtainChgObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr);
    UnobtainChgObj(double maxPos, double minPos, Game *gamePtr);
    virtual ObjType getType() const;
};

#endif
