//
// unobtainchgobj.h
// Header file for charged unobtainium object class for Space Junk.
//
// Copyright (c) 2012 Andrew Downing
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
