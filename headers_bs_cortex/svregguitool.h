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


#ifndef SVREGGUITOOL_H
#define SVREGGUITOOL_H

#include <extractionguitool.h>
#include <svregistrationtool.h>
class QWidget;
class SurfaceAlpha;
class CorticalExtractionSettings;

class SVRegGUITool : public ExtractionGUITool {
public:
    SVRegGUITool();
		bool initializeTool(CorticalExtractionSettings &ces);
    std::string stepName() const;
		int nSteps() const;
		int currentStep() const;
    bool runStep(BrainSuiteWindow *brainSuiteWindow, QWidget *caller=0);
    bool stepBack(BrainSuiteWindow *brainSuiteWindow);
    bool isFinished() const;
    std::string nextStepText() const;
		void setStepName(BrainSuiteWindow *brainSuiteWindow, std::string s);
    bool initialize(BrainSuiteWindow *brainSuiteWindow);
    bool labelSurfaces(BrainSuiteWindow *brainSuiteWindow, QWidget *caller=0);
    bool makeVolumeMap(BrainSuiteWindow *brainSuiteWindow, QWidget *caller=0);
    bool registerVolumes(BrainSuiteWindow *brainSuiteWindow, QWidget *caller=0);
    bool refineROIs(BrainSuiteWindow *brainSuiteWindow, QWidget *caller=0);
    bool refineRegistration(BrainSuiteWindow *brainSuiteWindow, QWidget *caller=0);
    bool refineSulci(BrainSuiteWindow *brainSuiteWindow, QWidget *caller=0);
		bool computeStats(BrainSuiteWindow *brainSuiteWindow);
		bool cleanupFiles(BrainSuiteWindow *brainSuiteWindow);
    void updateProgress(BrainSuiteWindow *brainSuiteWindow, const int value, const int maxvalue);
//private:
    SVRegistrationTool svreg;
    bool initialized;
    SurfaceAlpha *left,*right;
};

#endif // SVREGGUITOOL_H
