//
// game.cpp
// 
// author: Andrew Downing
// Source file for game class for Space Junk.
//

#include "game.h"
#include "playerobj.h"
#include "sunobj.h"
#include "planetobj.h"
#include "unobtainobj.h"
#include "unobtainshyobj.h"
#include "unobtainchgobj.h"
#include "hpackobj.h"
#include "hpackshyobj.h"
#include "hpackchgobj.h"
#include "junkobj.h"
#include "spawnerobj.h"
#include "shootmobj.h"
#include "missileobj.h"
#include "propelobj.h"

/** constructor for game window */
Game::Game() {
  int i;
  // initialize window
  resize(640, 480);
  setStyleSheet("background-color: black;");
  // load background images
  for (i = 0; i < NLevel; i++) {
    std::stringstream ss;
    ss << "rsc/bk" << i << ".png";
    bkImgs[i].load(ss.str().c_str());
  }
  // load game object images
  for (i = 0; i < NObjType; i++) {
    std::stringstream ss;
    ss << "rsc/obj" << i << ".png";
    objImgs[i].load(ss.str().c_str());
  }
  // load sounds
  for (i = 0; i < NSnd; i++) {
    std::stringstream ss;
    ss << "rsc/collect" << (i % NCollectSnd) << ".wav";
    collectSnds[i] = new QSound(ss.str().c_str());
    ss.str("");
    ss << "rsc/hit" << (i % NHitSnd) << ".wav";
    hitSnds[i] = new QSound(ss.str().c_str());
    ss.str("");
    ss << "rsc/explode" << (i % NExplodeSnd) << ".wav";
    explodeSnds[i] = new QSound(ss.str().c_str());
  }
  if (!QSound::isAvailable()) {
    // notify user that sound isn't available
    std::cout << "The nas package is required to play sounds. On Ubuntu, you can install it by running:" << std::endl
              << "sudo apt-get install nas" << std::endl;
  }
  // start a game
  bkImgsEnable = true;
  drawScl = 1;
  newGame(0);
  // show window
  show();
}

/** destructor for game window */
Game::~Game() {
  clearObjs();
  for (int i = 0; i < NSnd; i++) {
    delete hitSnds[i];
    delete explodeSnds[i];
  }
}

/** delete all game objects and stop timer */
void Game::clearObjs() {
  killTimer(timerId);
  for (int i = 0; i < (int)objs.size(); i++) {
    delete objs[i];
  }
  objs.clear();
}

/** start a new game of specified level */
void Game::newGame(int newLevel) {
  std::stringstream ss;
  int i, j;
  // reset variables
  clearObjs();
  frame = 0;
  gameOver = false;
  for (i = 0; i < NObjType; i++) {
    objsInitial[i] = 0;
  }
  // set level settings
  level = newLevel;
  ss << "Space Junk - ";
  healthMax = 150;
  objsInitial[Obj::Player] = 1;
  objsInitial[Obj::Sun] = 1;
  switch (level) {
    case 0:
      ss << "Classic Mode";
      objsInitial[Obj::Planet] = 5;
      objsInitial[Obj::Unobtain] = 10;
      objsInitial[Obj::Junk] = 1;
      break;
    case 1:
      ss << "They Don't Like You";
      objsInitial[Obj::UnobtainShy] = 3;
      objsInitial[Obj::UnobtainChg] = 3;
      objsInitial[Obj::HPackShy] = 1;
      objsInitial[Obj::HPackChg] = 1;
      break;
    case 2:
      ss << "Spawners";
      objsInitial[Obj::Spawner] = 10;
      break;
    case 3:
      ss << "War of the Worlds";
      objsInitial[Obj::Planet] = 5;
      objsInitial[Obj::HPack] = 3;
      objsInitial[Obj::ShootM] = 1;
      break;
  }
  setWindowTitle(ss.str().c_str());
  health = healthMax;
  // make game objects
  for (i = 0; i < NObjType; i++) {
    for (j = 0; j < objsInitial[i]; j++) {
      objs.push_back(newOrbitObj((Obj::ObjType)i));
    }
    objsLeft[i] = objsInitial[i];
  }
  // player is first object in vector
  player = (PlayerObj*)objs[0];
  // update background image
  resizeEvent(NULL);
  // display instructions
  repaint();
}

/** draw text centered horizontally on the screen */
void Game::drawCenterText(std::string text, int y) {
  QFont font("Arial", 14);
  QFontMetrics fontM(font);
  painter->setPen(Qt::white);
  painter->setFont(font);
  painter->drawText((width() - fontM.width(text.c_str())) / 2, y, text.c_str());
}

/** draw all objects and text (event triggered when the screen refreshes) */
void Game::paintEvent(QPaintEvent *evt) {
  QPainter localPainter(this);
  std::stringstream ss;
  int textY = TextHeight;
  painter = &localPainter;
  // draw background image
  if (bkImgsEnable) painter->drawImage(bkImgScl.rect(), bkImgScl);
  if (0 == frame) {
    int drawX;
    // draw instructions
    drawCenterText(windowTitle().toStdString(), TextHeight);
    textY += TextHeight * 2;
    drawCenterText("Use arrow keys to move, and +/- to zoom", textY);
    if (getAllUnobtainInitial()) {
      // unobtainium
      textY += TextHeight * 2;
      painter->drawText(0, textY, "Collect these:");
      drawX = 200;
      drawInstrObj(Obj::Unobtain, textY, drawX);
      drawInstrObj(Obj::UnobtainShy, textY, drawX);
      drawInstrObj(Obj::UnobtainChg, textY, drawX);
    }
    if (objsInitial[Obj::Junk] || objsInitial[Obj::Spawner]) {
      // space junk and spawners
      textY += TextHeight * 2;
      painter->drawText(0, textY, "Hit these with propellant:");
      drawX = 200;
      drawInstrObj(Obj::Junk, textY, drawX);
      drawInstrObj(Obj::Spawner, textY, drawX);
    }
    if (objsInitial[Obj::ShootM]) {
      // missile shooters and missiles
      textY += TextHeight * 2;
      painter->drawText(0, textY, "Make          collide with");
      drawX = 50;
      drawInstrObj(Obj::Missile, textY, drawX);
      drawX = 200;
      drawInstrObj(Obj::ShootM, textY, drawX);
    }
    if (objsInitial[Obj::HPack] || objsInitial[Obj::HPackShy] || objsInitial[Obj::HPackChg]) {
      // health packs
      textY += TextHeight * 2;
      painter->drawText(0, textY, "These give you health:");
      drawX = 200;
      drawInstrObj(Obj::HPack, textY, drawX);
      drawInstrObj(Obj::HPackShy, textY, drawX);
      drawInstrObj(Obj::HPackChg, textY, drawX);
    }
    drawCenterText("Don't run into ANYTHING except the objects you collect", textY + TextHeight * 2);
    drawCenterText("Press any key to continue", height() - TextHeight);
    painter = NULL;
    return; // we don't need to draw everything else yet
  }
  // draw objects
  for (int i = 0; i < (int)objs.size(); i++) {
    objs[i]->draw();
  }
  if (health > 0) {
    // draw health bar
    painter->setPen(Qt::green);
    painter->setBrush(QBrush(Qt::green));
    painter->drawRect(0, TextHeight / 3, health, TextHeight * 0.75);
  }
  // draw status text
  painter->setPen(Qt::white);
  painter->setFont(QFont("Arial", 14));
  if (getAllUnobtainInitial() > 0) {
    textY += TextHeight;
    ss.str("");
    ss << "unobtainium: " << (getAllUnobtainInitial() - getAllUnobtainLeft()) << "/" << getAllUnobtainInitial();
    painter->drawText(0, textY, ss.str().c_str());
  }
  if (objsLeft[Obj::Junk] > 0) {
    textY += TextHeight;
    ss.str("");
    ss << objsLeft[Obj::Junk] << " space junk remaining";
    painter->drawText(0, textY, ss.str().c_str());
  }
  if (objsLeft[Obj::Spawner] > 0) {
    textY += TextHeight;
    ss.str("");
    ss << objsLeft[Obj::Spawner] << ((1 == objsLeft[Obj::Spawner]) ? " spawner remaining" : " spawners remaining");
    painter->drawText(0, textY, ss.str().c_str());
  }
  if (objsLeft[Obj::ShootM] > 0) {
    textY += TextHeight;
    ss.str("");
    ss << objsLeft[Obj::ShootM] << " missile shooter remaining";
    painter->drawText(0, textY, ss.str().c_str());
  }
  if (gameOver) {
    // draw game over text
    if (health > 0) {
      drawCenterText("YOU WIN", height() / 2 + TextHeight * 3);
    }
    else {
      drawCenterText("YOU LOSE", height() / 2 + TextHeight * 3);
    }
    ss.str("");
    ss << "Press R to replay level, ";
    if (level > 0) ss << "P to play previous level, ";
    if (level < NLevel - 1) ss << "N to play next level, ";
    ss << "Esc to exit";
    drawCenterText(ss.str(), height() / 2 + TextHeight * 5);
  }
  painter = NULL;
}

/** run a single game frame (event triggered at a fixed time interval using a timer) */
void Game::timerEvent(QTimerEvent *evt) {
  int i;
  frame++;
  // accelerate objects (e.g. due to gravity or object AI)
  for (i = 0; i < (int)objs.size(); i++) {
    objs[i]->updateVel();
  }
  // move objects (in separate loop from accelerating objects to obey conservation of energy)
  for (i = 0; i < (int)objs.size(); i++) {
    objs[i]->updatePos();
  }
  // check win/lose conditions
  if (!gameOver) {
    if (health <= 0) {
      // player lost, don't draw player
      gameOver = true;
      player->setLose();
      if (1 == frame) newGame(level); // if player loses on first frame then restart level
    }
    else if (getAllUnobtainLeft() <= 0 && objsLeft[Obj::Junk] <= 0 && objsLeft[Obj::Spawner] <= 0 && objsLeft[Obj::ShootM] <= 0) {
      // player won
      gameOver = true;
    }
  }
  // delete objects marked for deletion
  for (i = 0; i < (int)objs.size(); i++) {
    if (objs[i]->getDelete()) {
      objsLeft[objs[i]->getType()]--;
      delete objs[i];
      objs.erase(objs.begin() + i);
      i--;
    }
  }
  // refresh the screen
  repaint();
}

/** handle key press from user */
// for future reference, use evt->isAutoRepeat() to check if this is a simulated repeat key press
void Game::keyPressEvent(QKeyEvent *evt) {
  double xMove = 0, yMove = 0;
  if (0 == frame && evt->key() != Qt::Key_Escape) {
    // start game
    killTimer(timerId); // in case timer is still running
    timerId = startTimer(UpdateRate);
    return;
  }
  switch (evt->key()) {
    // move player
    case Qt::Key_Up:
      yMove = -1;
      break;
    case Qt::Key_Left:
      xMove = -1;
      break;
    case Qt::Key_Down:
      yMove = 1;
      break;
    case Qt::Key_Right:
      xMove = 1;
      break;
    // zoom view
    case Qt::Key_Minus:
      if (drawScl > 0.3) drawScl /= 1.1;
      break;
    case Qt::Key_Equal:
      drawScl *= 1.1;
      if (drawScl > 1) drawScl = 1;
      break;
    // toggle background images
    case Qt::Key_B:
      bkImgsEnable = !bkImgsEnable;
      break;
    // new game
    case Qt::Key_R:
      newGame(level);
      break;
    case Qt::Key_P:
      if (level > 0) newGame(level - 1);
      break;
    case Qt::Key_N:
      if (level < NLevel - 1) newGame(level + 1);
      break;
    // exit game
    case Qt::Key_Escape:
      close();
      break;
  }
  // move player in the direction user specified
  if (!gameOver && (xMove != 0 || yMove != 0)) player->emitPropel(xMove * PlAccel, yMove * PlAccel);
}

/** handle mouse press from user (to move player) */
void Game::mousePressEvent(QMouseEvent *evt) {
  double xMove, yMove;
  if (Qt::LeftButton == evt->button() && !gameOver) {
    xMove = evt->pos().x() - width() / 2;
    yMove = evt->pos().y() - height() / 2;
    player->emitPropel(xMove / sqrt(xMove * xMove + yMove * yMove) * PlAccel, yMove / sqrt(xMove * xMove + yMove * yMove) * PlAccel);
  }
}

/** regenerate scaled background image when window is resized */
void Game::resizeEvent(QResizeEvent *evt) {
  bkImgScl = bkImgs[level].transformed(QTransform().scale(width() / (double)bkImgs[level].rect().width(), height() / (double)bkImgs[level].rect().height()));
}

/** draw object of specified type for instructions screen */
void Game::drawInstrObj(int type, int textY, int &drawX) {
  if (objsInitial[type] > 0 || Obj::Missile == type) {
    painter->drawImage(objImgs[type].rect().translated(drawX, textY - TextHeight), objImgs[type]);
    drawX += 50;
  }
}

/** play specified sound */
void Game::playSnd(QSound *snd[]) {
  if (QSound::isAvailable()) {
    // try to play sound that isn't playing
    int id;
    for (int i = 0; i < 100; i++) {
      id = rand() % NSnd;
      if (snd[id]->isFinished()) {
        snd[id]->play();
        return;
      }
    }
    // don't play an existing sound if all sounds tried are playing already;
    // doing this under heavy load may give NAS an error that crashes the program (try/catch doesn't help)
  }
}

/** @return total number of unobtainium and unobtainium-derived objects at start of game */
int Game::getAllUnobtainInitial() const {
  return objsInitial[Obj::Unobtain] + objsInitial[Obj::UnobtainShy] + objsInitial[Obj::UnobtainChg];
}

/** @return total number of unobtainium and unobtainium-derived objects remaining */
int Game::getAllUnobtainLeft() const {
  return objsLeft[Obj::Unobtain] + objsLeft[Obj::UnobtainShy] + objsLeft[Obj::UnobtainChg];
}

/** draw object of specified type at specified x and y (in game coordinates) */
void Game::drawObj(int type, double x, double y, double angle, bool alwaysOnscreen) {
  QImage img = objImgs[type].transformed(QTransform().rotateRadians(angle)); // get rotated object image
  QRect imgRect(0, 0, img.rect().width() * drawScl, img.rect().height() * drawScl); // get scaled drawing rectangle
  int xDraw = (x - objs[0]->getX()) * drawScl;
  int yDraw = (y - objs[0]->getY()) * drawScl;
  int halfWidth = (width() - imgRect.width()) / 2;
  int halfHeight = (height() - imgRect.height()) / 2;
  if (alwaysOnscreen) {
    // ensure object always draws onscreen
    if (xDraw < -halfWidth) {
      yDraw *= -halfWidth / (double)xDraw;
      xDraw = -halfWidth;
    }
    if (xDraw > halfWidth) {
      yDraw *= halfWidth / (double)xDraw;
      xDraw = halfWidth;
    }
    if (yDraw < -halfHeight) {
      xDraw *= -halfHeight / (double)yDraw;
      yDraw = -halfHeight;
    }
    if (yDraw > halfHeight) {
      xDraw *= halfHeight / (double)yDraw;
      yDraw = halfHeight;
    }
  }
  if (abs(xDraw) > width() || abs(yDraw) > height()) return; // don't draw objects that are far off screen
  painter->drawImage(imgRect.translated(xDraw + halfWidth, yDraw + halfHeight), img); // draw image
}

/** @return random double between 0 and 1 */
double Game::randF() const {
  return (double)rand() / (double)RAND_MAX;
}

/** @return pointer to new game object with specified properties */
Obj* Game::newObj(Obj::ObjType newType, double newX, double newY, double newXVel, double newYVel) {
  switch (newType) {
    case Obj::Player:
      return new PlayerObj(newX, newY, newXVel, newYVel, this);
    case Obj::Sun:
      return new SunObj(newX, newY, newXVel, newYVel, this);
    case Obj::Planet:
      return new PlanetObj(newX, newY, newXVel, newYVel, this);
    case Obj::Unobtain:
      return new UnobtainObj(newX, newY, newXVel, newYVel, this);
    case Obj::UnobtainShy:
      return new UnobtainShyObj(newX, newY, newXVel, newYVel, this);
    case Obj::UnobtainChg:
      return new UnobtainChgObj(newX, newY, newXVel, newYVel, this);
    case Obj::HPack:
      return new HPackObj(newX, newY, newXVel, newYVel, this);
    case Obj::HPackShy:
      return new HPackShyObj(newX, newY, newXVel, newYVel, this);
    case Obj::HPackChg:
      return new HPackChgObj(newX, newY, newXVel, newYVel, this);
    case Obj::Junk:
      return new JunkObj(newX, newY, newXVel, newYVel, this);
    case Obj::Spawner:
      return new SpawnerObj(newX, newY, newXVel, newYVel, this);
    case Obj::ShootM:
      return new ShootMObj(newX, newY, newXVel, newYVel, this);
    case Obj::Missile:
      return new MissileObj(newX, newY, newXVel, newYVel, this);
    case Obj::Propel:
      return new PropelObj(newX, newY, newXVel, newYVel, this);
    default:
      throw std::invalid_argument("asked to make object of undefined type");
  }
}

/** @return pointer to new game object orbiting around the sun */
Obj* Game::newOrbitObj(Obj::ObjType newType) {
  switch (newType) {
    case Obj::Player:
      return new PlayerObj(0, -200, -0.15 * UpdateRate, 0, this);
    case Obj::Sun:
      return new SunObj(0, 0, 0, 0, this);
    case Obj::Planet:
      return new PlanetObj(OrbitMax, OrbitMin, this);
    case Obj::Unobtain:
      return new UnobtainObj(OrbitMax, OrbitMin, this);
    case Obj::UnobtainShy:
      return new UnobtainShyObj(OrbitMax, OrbitMin, this);
    case Obj::UnobtainChg:
      return new UnobtainChgObj(OrbitMax, OrbitMin, this);
    case Obj::HPack:
      return new HPackObj(OrbitMax, OrbitMin, this);
    case Obj::HPackShy:
      return new HPackShyObj(OrbitMax, OrbitMin, this);
    case Obj::HPackChg:
      return new HPackChgObj(OrbitMax, OrbitMin, this);
    case Obj::Junk:
      return new JunkObj(OrbitMax, OrbitMin, this);
    case Obj::Spawner:
      return new SpawnerObj(OrbitMax, OrbitMin, this);
    case Obj::ShootM:
      return new ShootMObj(OrbitMax, OrbitMin, this);
    default:
      throw std::invalid_argument("invalid orbiting object type");
  }
}

/** @return number of game objects in objs vector */
int Game::getNObj() const {
  return (int)objs.size();
}

/** @return number of game objects of specified type in objs vector */
int Game::getNObj(Obj::ObjType type) const {
  return objsLeft[type];
}

/** @return game object at specified index */
Obj* Game::getObj(int index) const {
  return objs[index];
}

/** @return pointer to player object */
PlayerObj* Game::getPlayer() const {
  return player;
}

/** add specified game object to list */
void Game::addObj(Obj *obj) {
  objs.push_back(obj);
  objsLeft[obj->getType()]++;
}

/** play collect sound */
void Game::playCollectSnd() {
  playSnd(collectSnds);
}

/** play hit sound */
void Game::playHitSnd() {
  playSnd(hitSnds);
}

/** play explode sound */
void Game::playExplodeSnd() {
  playSnd(explodeSnds);
}

/** subtract a specified amount of player health */
void Game::subtHealth(int amount) {
  if (!gameOver) health -= amount;
}

/** set player health to maximum amount for this level */
void Game::setMaxHealth() {
  if (!gameOver) health = healthMax;
}

/** getter for game over */
bool Game::getGameOver() {
  return gameOver;
}

/** getter for frame count */
int Game::getFrame() {
  return frame;
}
