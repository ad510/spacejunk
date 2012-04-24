//
// obj.h
// 
// author: Andrew Downing
// Header file for game object class for Space Junk.
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
    virtual int updateVel();
    void updatePos();
    virtual void draw();
    void setDelete();
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
