// Copyright (C) 2016 The Regents of the University of California
//
// Created by David W. Shattuck, Ph.D.
//
// This file is part of BrainSuite16a1.
//
// BrainSuite16a1 is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; version 2.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
// USA.
//

#ifndef UndoSystem_H
#define UndoSystem_H

#include "brainsuitesettings.h"
#include <vol3dcompressed.h>

template <class VolType, int NUndos>
class UndoSystem {
public:
  class UndoPoint {
  public:
    Vol3DCompressed<VolType> buffer;
    IPoint3D point;
    std::string description;
  };
  UndoSystem() : undoLevel(0), undoIndex(0), lastUndoVol(0) {}
  bool set(Vol3D<VolType> &vLabel, const IPoint3D &point, std::string description)
  {
    if (&vLabel != lastUndoVol) reset();
    bool flag = next()->buffer.compress(vLabel);
    if (flag)
    {
      lastUndoVol = &vLabel;
      next()->description = description;
      next()->point = point;
      advance();
    }
    return flag;
  }
  bool undo(Vol3D<VolType> &vLabel)
  {
    if (current())
    {
      current()->buffer.uncompress(vLabel);
      rewind();
      for (int i=0;i<undoIndex;i++)
      {

      }
      return true;
    }
    return false;
  }
  bool redo(Vol3D<VolType> &vLabel)
  {
    {
      advance();
      current()->buffer.uncompress(vLabel);
      return true;
    }
    return false;
  }
  UndoPoint *next()
  {
    return &undos[undoIndex];
  }
  UndoPoint *current()
  {
    if (undoLevel==0) return 0;
    return (undoIndex>0) ? &undos[undoIndex-1] : &undos[NUndos-1];
    }
    void reset()
    {
    lastUndoVol = 0;
    undoLevel = 0;
    undoIndex = 0;
  }
  void freeUs()
  {
    lastUndoVol = 0;
    undoLevel = 0;
    undoIndex = 0;
  }
private:
  void rewind()
  {
    if (--undoLevel<0) undoLevel = 0;
    if (--undoIndex<0) undoIndex = NUndos-1;	// make circular
  }
  void advance()
  {
    undoIndex++; undoLevel++;
    if (undoLevel>=NUndos) undoLevel=NUndos-1;
    if (undoIndex>=NUndos) undoIndex=0;
  }
  UndoPoint undos[NUndos];
  int undoLevel;
  int undoIndex;
  Vol3D<VolType> *lastUndoVol; // should use serial #
};
#endif
