//
// game.h
// Header file for game class for Space Junk.
//
// Copyright (c) 2012 Andrew Downing
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QImage>
#include <QRect>
#include <QPainter>
#include <QSound>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTime>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>
#include <stdexcept>
#include "playerobj.h"

// game constants
const double UpdateRate = 33; // screen refresh rate in milliseconds
const int TextHeight = 25; // height of a line of text in pixels
const int HealthMax = 150; // amount of player health at start of level
const int NLevel = 4; // number of levels in game
const int NSnd = 6; // number of copies to store of each sound
const int NCollectSnd = 1; // number of collect sounds
const int NHitSnd = 3; // number of hit sounds
const int NExplodeSnd = 1; // number of explode sounds

// object constants
const int NObjType = 14; // number of types of game objects
const double OrbitMax = 500, OrbitMin = 100; // min & max initial orbiting distances
const double StdAccel = UpdateRate / 33, StdMass = 0.001, StdCharge = 0.015, StdRadius = 20; // properties shared by several types of objects
const double PlAccel = StdAccel, PlMass = StdMass, PlRadius = 10; // player properties
const double SunFlareSize = 5, SunMass = 5, SunRadius = StdRadius; // sun properties
const double PlanetMass = SunMass * 0.01, PlanetRadius = StdRadius; // planet properties
const double UnobtainMass = StdMass, UnobtainRadius = StdRadius; // unobtainium properties
const double UnobtainShyAvoidDist = 100, UnobtainShyAccel = StdAccel; // shy unobtainium properties
const double UnobtainChgCharge = StdCharge; // charged unobtainium properties
const double HPackMass = StdMass, HPackRadius = StdRadius; // health pack properties
const double HPackShyAvoidDist = 100, HPackShyAccel = StdAccel; // shy health pack properties
const double HPackChgCharge = StdCharge; // charged health pack properties
const double JunkAccel = StdAccel, JunkMass = StdMass, JunkRadius = StdRadius; // space junk properties
const double SpawnerAccel = StdAccel, SpawnerMass = StdMass, SpawnerRadius = StdRadius; // spawner properties
const double ShootMAccel = StdAccel * 3, ShootMMass = StdMass, ShootMRadius = 30; // missile shooter properties
const double MissileMaxPropel = 100, MissileAccel = StdAccel, MissileMass = StdMass, MissileEmptyMass = StdMass / 3, MissileRadius = StdRadius; // missile properties
const double PrMass = StdMass / 5, PrRadius = 10; // propellant properties (most realistic mass would be (MissileMass - MissileEmptyMass) / MissileMaxPropel)

/** Qt widget for the game window */
class Game : public QWidget {
  public:
    Game();
    ~Game();
  protected:
    /** ID of Qt timer (so timer can be stopped later) */
    int timerId;
    /** conversion factor from game to screen coordinates */
    double drawScl;
    /** current game level */
    int level;
    /** frame counter */
    int frame;
    /** records actual time since game start */
    QTime clock;
    /** whether the player lost or won */
    bool gameOver;
    /** amount of player health remaining */
    int health;
    /** number of objects of each type at start of level */
    int objsInitial[NObjType];
    /** number of objects of each type remaining */
    int objsLeft[NObjType];
    /** pointer to player object (same as objs[0]) */
    PlayerObj *player;
    /** vector containing all game objects */
    std::vector<Obj*> objs;
    /** whether to draw background images instead of a black background */
    bool bkImgsEnable;
    /** whether background images disabled due to lag */
    bool lag;
    /** background images for each level */
    QImage bkImgs[NLevel];
    /** background image of current level, scaled to window size */
    QImage bkImgScl;
    /** images of each type of game object */
    QImage objImgs[NObjType];
    /** pointer to QPainter used in this frame */
    QPainter *painter;
    /** pointers to dynamically allocated collect sounds */
    QSound *collectSnds[NSnd];
    /** pointers to dynamically allocated hit sounds */
    QSound *hitSnds[NSnd];
    /** pointers to dynamically allocated explode sounds */
    QSound *explodeSnds[NSnd];
    void clearObjs();
    void newGame(int newLevel);
    void drawCenterText(std::string text, int y);
    void paintEvent(QPaintEvent *evt);
    void timerEvent(QTimerEvent *evt);
    void keyPressEvent(QKeyEvent *evt);
    void mousePressEvent(QMouseEvent *evt);
    void resizeEvent(QResizeEvent *evt);
    void drawInstrObj(int type, int textY, int &drawX);
    void playSnd(QSound *snd[]);
    int getAllUnobtainInitial() const;
    int getAllUnobtainLeft() const;
  public:
    void drawObj(int type, double x, double y, double angle, bool alwaysOnscreen);
    double randF() const;
    Obj* newObj(Obj::ObjType newType, double newX, double newY, double newXVel, double newYVel);
    Obj* newOrbitObj(Obj::ObjType newType);
    int getNObj() const;
    int getNObj(Obj::ObjType type) const;
    Obj* getObj(int index) const;
    PlayerObj* getPlayer() const;
    void addObj(Obj *obj);
    void playCollectSnd();
    void playHitSnd();
    void playExplodeSnd();
    void subtHealth(int amount);
    void setMaxHealth();
    bool getGameOver();
    int getFrame();
};

#endif
