//
// hpackchgobj.h
// 
// author: Andrew Downing
// Header file for charged health pack object class for Space Junk.
//

#ifndef HPACKCHGOBJ_H
#define HPACKCHGOBJ_H

#include "hpackobj.h"

/** charged health pack object (repels charged objects, including player if player has collected charged objects) */
class HPackChgObj : public HPackObj {
  public:
    HPackChgObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr);
    HPackChgObj(double maxPos, double minPos, Game *gamePtr);
    virtual ObjType getType() const;
};

#endif
