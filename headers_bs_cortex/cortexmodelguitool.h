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

#ifndef CORTEXMODELGUITOOL_H
#define CORTEXMODELGUITOOL_H

#include <extractionguitool.h>
#include <cortexmodeler.h>

class CortexModelGUITool : public ExtractionGUITool
{
public:
  CortexModelGUITool();
  int nSteps() const;
  int currentStep() const;
  bool runStep(BrainSuiteWindow *brainSuiteWindow, QWidget *caller=0);
  bool stepBack(BrainSuiteWindow *brainSuiteWindow);
  std::string stepName() const;
  std::string nextStepText() const;
  bool isFinished() const;
  bool autosaveOutputs(BrainSuiteWindow *brainSuiteWindow);
  void updateProgress(BrainSuiteWindow *brainSuiteWindow, const int value, const int maxvalue);
  enum State { FindCortex=0, Finished=1 };
  State state;
  CortexModeler cortexModeler;
};

#endif // CORTEXMODELGUITOOL_H
