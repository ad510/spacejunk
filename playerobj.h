//
// playerobj.h
// 
// author: Andrew Downing
// Header file for player class for Space Junk.
//

#ifndef PLAYEROBJ_H
#define PLAYEROBJ_H

#include "obj.h"

/** player object */
class PlayerObj : public Obj {
  protected:
    /** frame when player loses (player isn't drawn if player loses) */
    int loseFrame;
  public:
    PlayerObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr);
    void emitPropel(double accelX, double accelY);
    virtual void collidePlayer();
    virtual int updateVel();
    virtual void draw();
    void addCharge(double amount);
    void setLose();
    virtual ObjType getType() const;
};

#endif
