//
// main.cpp
// 
// author: Andrew Downing
// Source file for Qt initialization code for Space Junk.
//

/**
@mainpage Space Junk Qt game
 
@section overview Overview

A growing problem is the increasing amount of space junk orbiting around Earth, consisting of unused satellites and bits of objects that aren't used anymore. The game Space Junk encourages you to explore the solar system while keeping the planetary neighborhood clean. You lose health if you run into any object (including your own propellant!) other than those that you collect. (I got permission from Prof. Crowley to use health as a more powerful replacement for lives.) There are 4 solar systems in the game: Classic Mode, They Don't Like You, Spawners, and War of the Worlds.

@section controls Controls

- arrow keys or mouse click: move (emitting toxic propellant as you do so)
- -: zoom out
- +: zoom in
- R: replay level
- P: play previous level
- N: play next level
- B: toggle fancy background images (in case streaming backgrounds over ssh causes lag)
- escape: exit

@section objects The Objects

Some of these objects are fairly passive. Considering that I implemented more types of objects than required by the assignment, you can think of these as "bonus" objects. Also, I tried to implement as much functionality as possible in the generic object class, the result being that many of the specific object classes are relatively short despite implementing unique behaviors. (Inheritance is awesome!)
\image html "../rsc/obj0.png" "You (the player)"
\image html "../rsc/obj1.png" "The sun. You lose health if you run into it."
\image html "../rsc/obj2.png" "A planet. You lose health if you run into these."
\image html "../rsc/obj3.png" "Unobtainium. To win, you have to collect all of these by running into them."
\image html "../rsc/obj4.png" "Shy unobtainium. This is a type of unobtainium that avoids you by shooting propellant at you if you get too close."
\image html "../rsc/obj5.png" "Charged unobtainium. As you collect these, their charge is transferred to you, making other charged objects repel you more as the game progresses."
\image html "../rsc/obj6.png" "A health pack. These restore your health to the maximum level if you collect these."
\image html "../rsc/obj7.png" "A shy health pack. Yes, this is a health pack that shoots at you (if you get too close)."
\image html "../rsc/obj8.png" "A charged health pack. As you collect these, their charge is transferred to you, making other charged objects repel you more."
\image html "../rsc/obj9.png" "Space junk that ejects propellant in random directions, gradually changing the orbit it's in. To win, you have to hit this with your propellant. If you run into it, it explodes."
\image html "../rsc/obj10.png" "A spawner that self-reproduces. To win, you have to hit all of these with your propellant. If you run into it, it explodes."
\image html "../rsc/obj11.png" "A missile shooter. To win, make a homing missile it shoots out run into it. I can assure you that it shoots out missiles directly at the player at a nonzero velocity."
\image html "../rsc/obj12.png" "A homing missile, and if anyone else wrote a more intelligent flight software than what I wrote for these missiles, I want to see it. Also, it has limited propellant and loses mass as it shoots out propellant."
\image html "../rsc/obj13.png" "Propellant. Every time you accelerate, you emit a piece of toxic propellant, and if you run into that propellant you lose health. Use sparingly!"

@section sounds The Sounds

Since sound doesn't travel through space, you only hear sounds when the player runs into something. The hit and explode sounds were taken from the public domain video at http://www.nasa.gov/mp4/157765main_srbiPod.mp4 . (According to http://www.nasa.gov/audience/formedia/features/MP_Photo_Guidelines.html , basically anything NASA releases is not copyrighted except for NASA logos.) The hit sounds are modified from the sounds of pieces of propellant hitting the solid rocket booster around 0:40-0:45, and the explode sound is modified from the parachute deployment sound around 4:17. I recorded the collect sound myself.

@section reqs Code Requirements

- Qt GUI
- multiple levels and types of objects
- displaying instructions
- user input
- collision detection
- inelastic collision response
- gravity and electrostatics simulation
- conservation of momentum (I tried to be strict as possible about following this, considering that the game often violates conservation of mass)
- status display
- health bar (as a more powerful replacement for lives; I got permission from Prof. Crowley to do this)
- game over text
- inheritance and polymorphism for game objects

@section globals Global Data/Functions

There are no global variables, and the only global function is main(). Practically everything is implemented in classes.

@section arch High-level Architecture

The high level game logic is handled in the game window class. At fixed intervals, a timer calls timerEvent(), which moves objects and handles collisions, checks win/lose conditions, and refreshes the screen, in that order. Different events are triggered to handle user input and redrawing the screen. The game window class has a vector containing pointers to all game objects, using polymorphism so each type of object can have a different class. Object child classes often overwrite collidePlayer() and updateVel() to implement a special collision response or AI. Images and sounds are stored directly in the game window class so those resources aren't duplicated for every object.

@section ui User Interface

Space Junk uses the Qt framework to display the GUI. The view is centered on the player and there is a status display in the upper left corner. Important objects that are off the screen are displayed at the edge of the screen so the player knows which direction to go to get them. Before each level, instructions are displayed. If the player wins or loses, controls to move the player are disabled and text is displayed, saying whether the player won or lost and giving directions to exit or play again.

@section testing Test Cases

Given that the UI of Space Junk isn't particularly data-oriented, there aren't obvious sets of input that are particularly nominal or problematic. Important situations to test include the player and/or propellant colliding with each type of object, winning, losing, and making sure certain objects stop moving after winning or losing.
*/

#include <QApplication>
#include "game.h"

int main(int argc, char *argv[])
{
  srand(time(NULL)); // seed random number generator
  QApplication app(argc, argv);
  Game window;
  return app.exec();
}
