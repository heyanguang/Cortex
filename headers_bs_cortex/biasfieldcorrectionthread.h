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

#ifndef BiasFieldCorrectionThread_H
#define BiasFieldCorrectionThread_H

#include <QThread>
#include <vol3d.h>

class BFCThreadDialog;
class BFCGUITool;

class BFCThread : public QThread
{
  Q_OBJECT
public:
  explicit BFCThread(BFCThreadDialog *parent, BFCGUITool *tool, Vol3D<float32> &vWorking, Vol3D<float32> &vSpline, Vol3D<uint8> &vMask);

protected:
  void run();
private:
  BFCThreadDialog *parent;
  BFCGUITool *tool;
  Vol3D<float32> &vWorking;
  Vol3D<float32> &vSpline;
  Vol3D<uint8> &vMask;
signals:
  void notifyParentFinished(BFCThread *sender);
  void notifyParentStartingIteration(int iteration);
public slots:
  void whenFinished()
  {
    if (parent)
    {
      emit notifyParentFinished(this);
    }
  }
};

#endif // BIASFIELDCORRECTIONTHREAD_H
