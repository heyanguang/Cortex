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


#ifndef SVREGISTRATIONTOOL_H
#define SVREGISTRATIONTOOL_H

#include <string>
#include <qstring.h>
#include <svregmanifest.h>

class CorticalExtractionSettings;

class SVRegistrationTool {
public:
  SVRegistrationTool();
  bool initializeExecutablePath(CorticalExtractionSettings &ces);
  bool setup(std::string primaryFile);
  SVRegManifest svregManifest;
  std::string subjectBase;
  std::string subjectPath;
  QString dirPath;
  std::string svregPath;
  std::string atlasPath;
  std::string atlasBase;
  enum RegistrationState {
    Initialize=0,
    LabelSurfaces=1,
    MakeVolumeMap=2,
    RegisterVolumes=3,
    RefineROIs=4,
    RefineRegistration=5,
    RefineSulci=6,
    ComputeStats=7,
    CleanUp=8,
    Finished=9
  };
  bool checkForRequiredFiles() { return checkForRequiredFiles(state); }
  bool copyAtlasFiles();
  bool checkForRequiredFiles(const RegistrationState state);
  std::string stateName(const RegistrationState &state) const;
  std::string runningStepName(const SVRegistrationTool::RegistrationState &state);
  RegistrationState state;
  std::string errorString;
  bool executablePathOK;
  bool executablesOK;
  bool atlasPathOK;
  bool atlasFilesOK;
  bool mcrOK;
  std::string MCRPath;
  std::string matlabAppPath(std::string basename);
  std::string matlabExePath(std::string basename);

  std::string matlabAppPrefix;
  std::string matlabExePrefix;
  std::string matlabAppSuffix;
  std::string matlabExeSuffix;
  std::string prepareFilesBasename;
  std::string labelSurfaceBasename;
  std::string mapToAtlasBasename;
  std::string volmapBallBasename;
  std::string volregBasename;
  std::string refineROIBasename;
  std::string refineRegistrationBasename;
  std::string refineSulciBasename;
  std::string computeStatsBasename;
  std::string cleanIntermediateFilesBasename;

  std::string prepareFilesExe;
  std::string labelSurfaceExe;
  std::string mapToAtlasExe;
  std::string volmapBallExe;
  std::string volregExe;
  std::string refineROIExe;
  std::string refineRegistrationExe;
  std::string refineSulciExe;
  std::string computeStatsExe;
  std::string cleanIntermediateFilesExe;
};

#endif // SVREGISTRATIONTOOL_H
