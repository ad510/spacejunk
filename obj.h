//
// obj.h
// Header file for game object class for Space Junk.
//
// Copyright (c) 2012 Andrew Downing
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#ifndef OBJ_H
#define OBJ_H

class Game; // forward declare game class

/** abstract base class representing a generic game object */
class Obj {
  public:
    enum ObjType {
      Player,
      Sun,
      Planet,
      Unobtain,
      UnobtainShy,
      UnobtainChg,
      HPack,
      HPackShy,
      HPackChg,
      Junk,
      Spawner,
      ShootM,
      Missile,
      Propel
    };
  protected:
    /** position x coordinate */
    double x;
    /** position y coordinate */
    double y;
    /** velocity x coordinate */
    double xVel;
    /** velocity y coordinate */
    double yVel;
    /** mass of object (used in gravity calculation) */
    double mass;
    /** charge of object (used in electrostatic force calculation) */
    double charge;
    /** radius of object (used in collision detection) */
    double radius;
    /** target angle to smoothly rotate to */
    double rotateAim;
    /** angle to rotate image */
    double rotate;
    /** flag marking object for deletion in this frame */
    bool del;
    /** index of object collided with */
    int collided;
    /** whether collided with player in previous frame */
    bool collidedPlLast;
    /** pointer to game class */
    Game *game;
  public:
    Obj(double newX, double newY, double newXVel, double newYVel, double newMass, double newRadius, Game *gamePtr);
    Obj(double maxPos, double minPos, double newMass, double newRadius, Game *gamePtr);
    void accel(double xAccel, double yAccel);
    void emitObj(ObjType emitType, double xAccel, double yAccel, bool centered = false);
    void explode(int nParticle, Obj *obj, double maxSpd = 2);
    double collide(Obj *obj);
    virtual void collidePlayer() = 0;
    virtual void updateVel();
    void updatePos();
    virtual void draw();
    void setDelete();
    void setCollided(int newCollided);
    double distSqTo(double toX, double toY) const;
    virtual ObjType getType() const = 0;
    double getX() const;
    double getY() const;
    double getXVel() const;
    double getYVel() const;
    double getMass() const;
    double getCharge() const;
    double getRadius() const;
    bool getDelete() const;
};

#endif
