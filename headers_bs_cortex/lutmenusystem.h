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

#ifndef LUTMENUSYSTEM_H
#define LUTMENUSYSTEM_H

#include <qmenu.h>
#include <string>
#include <vol3ddatatypes.h>
class BrainSuiteWindow;
class QPoint;
class QAction;

class LUTMenuItem {
public:
  LUTMenuItem(QAction *action=0, uint32 *LUT=0, uint32 **parentLUT=0) : action(action), LUT(LUT), parentLUT(parentLUT) {}
  QAction *action;
  uint32 *LUT;
  uint32 **parentLUT;
};

class LUTMenuSystem {
public:
  LUTMenuSystem(BrainSuiteWindow *brainSuiteWindow);
  LUTMenuSystem(BrainSuiteWindow *brainSuiteWindow, uint32 *&imageLUT);
  QMenu *makeLUTMenu(QMenu *parentMenu, uint32 **targetLUT, std::string menuName);
  void doPopup(const QPoint &pos);
private:
  BrainSuiteWindow *brainSuiteWindow;
  QMenu popupMenu;
  std::vector<LUTMenuItem> lutMenuItems;
};

#endif // LUTMENUSYSTEM_H
