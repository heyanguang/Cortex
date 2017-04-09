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

#ifndef BFCGUITOOL_H
#define BFCGUITOOL_H

#include <extractionguitool.h>
#include <BFC/bfctool.h>

class BFCGUITool : public ExtractionGUITool
{
public:
  int nSteps() const;
  int currentStep() const;
  bool runStep(BrainSuiteWindow *brainSuiteWindow, QWidget *caller=0);
  bool stepBack(BrainSuiteWindow *brainSuiteWindow);
  std::string stepName() const;
  std::string nextStepText() const;
  bool isFinished() const;
  bool autosaveOutputs(BrainSuiteWindow *brainSuiteWindow);
  void setStepName(BrainSuiteWindow *brainSuiteWindow, std::string s);
  void updateProgress(BrainSuiteWindow *brainSuiteWindow, const int value, const int maxvalue);
  bool runIterative(BrainSuiteWindow *brainSuiteWindow, QWidget *caller);
  bool finalizeOutput(BrainSuiteWindow *brainSuiteWindow, Vol3DBase *correctedVolume);
  BFCTool bfcTool;
  bool resetIterations();
  bool atEnd();
  int iterationNumber();
  int nIterations();
  bool performNextIteration(Vol3D<float32> &vWorking, Vol3D<float> &vSpline, Vol3D<uint8> &vMask);
};

#endif // BFCGUITOOL_H
