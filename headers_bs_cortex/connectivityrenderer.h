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

#ifndef ConnectivityRenderer_H
#define ConnectivityRenderer_H

#include <string>
#include <vector>
#include <dspoint.h>
#include <dsglslider.h>
#include <labeldetails.h>

class ConnectivityMap;
class QPainter;
class ConnectivityProperties;

class ConnectivityRenderer {
public:
  ConnectivityRenderer();
  void useScreenColors();
  void usePrintColors();
  int width() const { return vPort[2]; }
  int height() const { return vPort[3]; }
  void initialize();
  void glEnable2D();
  void glDisable2D();
  bool inSlider(float x, float y);
  void moveSlider(float x, float y);
  void clearSelection();
  void drawLinks(QPainter &painter, ConnectivityMap &connectivityMap);
  void drawQtText(QPainter &painter, std::string text, float x, float y, float angle, DSPoint color);
  void drawNodeText(QPainter &painter, ConnectivityMap &connectivityMap);
  void drawNodes(QPainter &painter, ConnectivityMap &connectivityMap, std::vector<LabelDetails> &labelDetails);
  void render(QPainter &p, ConnectivityMap &connectivityMap, std::vector<LabelDetails> &labelDetails);
  void sortOddEven(std::vector<int> &selectionVector, ConnectivityMap &connectivityMap);
  void pickSubrange(ConnectivityMap &connectivityMap, const int lower, const int upper);
  void connectivityShowAllBrain(ConnectivityMap &connectivityMap);
  void drawArcQt(QPainter &painter, const float x, const float y, const float r, const float theta0, const float theta1);
  int mapSector(ConnectivityMap &connectivityMap, float x, float y);
  bool makeSelection(ConnectivityMap &connectivityMap, float x, float y);
  bool addSelection(ConnectivityMap &connectivityMap, float x, float y);
  bool addSecondSelection(ConnectivityMap &connectivityMap, float x, float y);
  int getSelectedLabel(ConnectivityMap &connectivityMap);
  bool getSelectedLabels(std::vector<int> &labelIDs, const ConnectivityMap &connectivityMap);
  bool getSelectedNodes(std::vector<int> &nodeIDs);
  bool isSelected(const int nodeID);
  // display state variables
  int vPort[4];
  DSGLSlider slider;
  std::vector<int> connectivitySubset;
  std::string subsetName;
  std::string statusMessage;
  DSPoint clearColor;
  DSPoint mainTextColor;
  DSPoint nodeTextColor;
  DSPoint highlightedTextColor;
  DSPoint nodeHighlightColor;
  DSPoint nodeColor;
  DSPoint linkColorA;
  DSPoint linkColorB;
  int highlight;
  float weightThreshold;
  float circleRadius;
  float textZoom;
  float fontSize;
  bool drawArcs;
  bool showNodeNames;
  bool useAbbrevs;
  bool groupMode; // false = OR true = AND
  bool dither;
  float ditherDelta;
  bool computing;
  std::vector<int> &getSelection() { return selection; }
  float retinaScale;
  static float arcWidthBase;
  static float arcWidthScale;
  static float textSize;
  static float rotationShift;
private:
  std::vector<int> selection;
};

#endif
