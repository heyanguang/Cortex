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

#ifndef BrainSuiteSettings_H
#define BrainSuiteSettings_H

#include <dspoint.h>
#include <uvpoint.h>
#include <vol3ddatatypes.h>

class BrainSuiteSettings {
public:
  enum Clipping { Off=0, Positive=1, Negative=2 };
  enum TrackColorModel { SingleColor=0, AverageAngle=1, LocalAngle=2, FiberLength=3 };
  BrainSuiteSettings() {}
  static std::string defaultCerebrumAtlasBrain;
  static std::string defaultCerebrumAtlasTemplate;
  static bool noConsole;
  static bool showAnnotations;
  static bool showFibersAsTubes;
  static bool showCurvesAsTubes;
  static bool advancedDebugging;
  static bool pretrack;
  static bool autofitOnResize;
  static bool showSurfaces;
  static bool showTensors;
  static bool showODFs;
  static bool clipODFs;
  static bool showFibers;
  static bool clipFibers;
  static bool useColorFA;
  static bool clipTensors;
  static float ellipseRadius; // for glyphs
  static bool drawTensorsXY;
  static bool drawTensorsXZ;
  static bool drawTensorsYZ;
  static int glyphQuality;
  static int glyphMode;
  static bool curveProtocolTrackPosition;
  static bool curveProtocolDrawLabels;
  static int curveProtocolBrushSize;
  static DSPoint pendingCurveColor;
  static int textOffset;
  static int sliderWidth;
  static bool showCoords;
  static int coordWidth;
  static bool showOrientation;
  static bool cycleSurfacesFlag;
  static UVPoint uvSpeed;
  static float rotationSpeed;
  static bool cycling;
  static bool useSliceOpacity;
  static float sliceOpacity;
  static uint8 textureAlpha;
  static float material_shininess;
  static int alphasortMode;
  static bool ignoreVolumePosition;
  static Clipping clipXPlane;
  static Clipping clipYPlane;
  static Clipping clipZPlane;
  static float clipXPlaneOffset;
  static float clipYPlaneOffset;
  static float clipZPlaneOffset;
  static bool showTensorAxes;
  static bool wireframeTensors;
  static bool animated;
  static float tubeSize;
  static float curveTubeSize;
  static int nCylinderPanels;
  static bool fiberWireframe;
  static bool showTrackSubset;
  static bool showCurves;
  static bool showCurvesOnImageSlices;
  static float defaultCurveWidth;
  static bool useLighting;
  static bool renderSlices; // in the surface view
  static bool maskUndoDisabled;
  static bool disableInternetChecking;
  static bool zoomBestFitOnResize;
  static DSPoint defaultFiberColor;
  static TrackColorModel trackColorModel;
  static float fiberLineWidth;
  static bool showConnectivityNodesUsingLabelColors;
  static bool autosaveCorticalExtraction;
  static std::string autosavePrefix;
  static bool depthSortSurfaceTriangles;
  static bool dontAutoScale;
};

#endif
