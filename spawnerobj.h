//
// spawnerobj.h
// 
// author: Andrew Downing
// Header file for spawner object class for Space Junk.
//

#ifndef SPAWNEROBJ_H
#define SPAWNEROBJ_H

#include "obj.h"

/** spawner object (self-reproduces) */
class SpawnerObj : public Obj {
  protected:
    /** next frame in which spawner will self-reproduce */
    int spawnFrame;
    void resetSpawnFrame();
  public:
    SpawnerObj(double newX, double newY, double newXVel, double newYVel, Game *gamePtr);
    SpawnerObj(double maxPos, double minPos, Game *gamePtr);
    virtual void collidePlayer();
    virtual int updateVel();
    virtual void draw();
    virtual ObjType getType() const;
};

#endif
