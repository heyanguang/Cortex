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

#ifndef BRAINSUITEDATAMANAGER_H
#define BRAINSUITEDATAMANAGER_H

#include <list>
#include <vol3d.h>
#include <labeldescriptionset.h>
#include <connectivitymap.h>
#include <connectivityproperties.h>

class SurfaceAlpha;
class Vol3DBase;
class FiberTrackSet;
class ProtocolCurveSet;

class BrainSuiteDataManager
{
public:
  class SurfaceHandle {
  public:
    SurfaceHandle(SurfaceAlpha *surface=0, bool ownedByList=false) : surface(surface), ownedByList(ownedByList) {}
    ~SurfaceHandle();
    SurfaceAlpha *surface;
    bool ownedByList;
  };
  BrainSuiteDataManager();
  ~BrainSuiteDataManager();
  std::list<SurfaceHandle> &surfaceHandleList() { return surfaces; }
  SurfaceAlpha *firstSurface() { return (surfaces.size()) ? surfaces.front().surface : 0; }
  bool nextSurface(); // sets the next surface to "show", hides the others
  bool previousSurface();  // sets the previous surface to "show", hides the others
  bool addSurface(SurfaceAlpha *surface, bool giveOwnership);
  bool removeSurface(SurfaceAlpha *surface);
  LabelDescriptionSet labelDescriptionSet;
  Vol3DBase *volume;
  Vol3DBase *imageOverlay1Volume;
  Vol3DBase *imageOverlay2Volume;
  Vol3D<uint8> vMask;
  Vol3D<EigenSystem3x3f> vODFEig;
  Vol3DBase *vLabel;
  bool addVolume(Vol3DBase *volume);
  std::list<SurfaceHandle> surfaces;
  ConnectivityMap connectivityMap;
  ConnectivityProperties connectivityProperties;
  FiberTrackSet *fiberTrackSet;
  FiberTrackSet *fiberTrackSubset;
  ProtocolCurveSet *protocolCurveSet;
  DSPoint curveCentroid;
  DSPoint fiberCentroid;
};

#endif // BRAINSUITEDATAMANAGER_H
