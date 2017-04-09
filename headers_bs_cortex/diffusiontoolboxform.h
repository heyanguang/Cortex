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

#ifndef DIFFUSIONTOOLBOXFORM_H
#define DIFFUSIONTOOLBOXFORM_H

#include <QWidget>
#include <vol3d.h>
#include <sphereroi.h>

class BrainSuiteWindow;
class HARDITool;
class FiberTrackSet;
class ImageWidget;

namespace Ui {
class DiffusionToolboxForm;
}

class DiffusionToolboxForm : public QWidget
{
  Q_OBJECT

public:

  class ROIColumns {
  public:
    enum   { Active=0, Include, And, Color, Position, Radius, NItems };
  };
  explicit DiffusionToolboxForm(BrainSuiteWindow *brainSuiteWindow, QWidget *parent = 0);
  ~DiffusionToolboxForm();
  void initTrackFilterPage();
  QSize sizeHint() const;
  void setSamplingSlider(const int n);
  void setODFWindow(const int n);
  void setODFSampling(const int n);
  void setTrackSeeding(const float f);
  void setStepsize(const float f);
  void setMaxSteps(const int n);
  void setAngleThreshold(const float f);
  void setFAThreshold(const float f);
  void setGFAThreshold(const float f);
  void update();
  bool updateGlyphs(bool recomputeBasis);
  void updateImages();
  void updateDiffusionProperties();
  void showDTIPage();
  void showHARDIPage();
  void showTractographyPage();
  void showTrackDisplayPage();
  void showTrackFilteringPage();
  void showConnectivityPage();
  void applyCurrentFilters();
  float getLengthThreshold();
  bool selectDTITracking();
  bool selectODFTracking();
  void resetDiffusionScale();
  void moveSelectedROIto(const IPoint3D &position);
  void mouseMoveTo(ImageWidget *port, const IPoint3D &position, QMouseEvent *event);
  void updateROISphereTable();
  void updateROISphereTableRadii();
  bool showSphereROIsInSliceView();
  void updateROIViews();

  bool showSphereROIs_in3D();
  bool sphereWireframe();
  bool computeODFTracks();
  void computeConnectivity();
  void increaseSphereRadius();
  void decreaseSphereRadius();
  size_t nSphereROIs();
  std::vector<SphereROI> sphereROIs;
protected:
  bool sampleODFs(Vol3D<EigenSystem3x3f> &vEig, HARDITool &hardiTool, Vol3D<uint8> &vMask);
  bool computeFiberTracks(FiberTrackSet &fiberTrackSet, Vol3D<EigenSystem3x3f> &vEig, const Vol3D<uint8> &vMask,
                          const float vStep=1.0f, float stepsize=0.1f, int nSteps=500, const float angleThresh=0.98f);
  bool makeTracks();
  DSPoint sphereColor;
  DSPoint sphere2Color;
private slots:
  void on_ellipseScaleSlider_valueChanged(int value);
  void on_samplingSlider_valueChanged(int value);
  void on_windowSlider_valueChanged(int value);
  void on_coefficientSlider_valueChanged(int value);
  void on_flipXCheckBox_clicked();
  void on_flipYCheckBox_clicked();
  void on_flipZCheckBox_clicked();
  void on_showXYPlaneCheckBox_clicked();
  void on_showXZPlaneCheckBox_clicked();
  void on_showYZPlaneCheckBox_clicked();
  void on_showODFGlyphsCheckBox_clicked();
  void on_computeTractsPushButton_clicked();
  void on_findODFMaximaPushButton_clicked();
  void on_showDTI_XYPlaneCheckBox_clicked();
  void on_showDTI_XZPlaneCheckBox_clicked();
  void on_showDTI_YZPlaneCheckBox_clicked();
  void on_tubeRadiusSlider_valueChanged(int value);
  void on_tubeRadiusEditBox_textEdited(const QString &arg1);
  void on_renderFibersAsTubesCheckBox_clicked();
  void on_tractLengthSlider_valueChanged(int value);
  void on_tractLengthEdit_textChanged(const QString &arg1);
  void on_sphereRadiusSlider_valueChanged(int value);
  void on_showSphereIn3DViewCheckBox_clicked();
  void on_showSphereAsWireframeCheckBox_clicked();
  void on_showTensorGlyphsCheckBox_clicked();
  void on_computeConnectivityPushButton_clicked();
  void on_clipGlyphsCheckBox_clicked();
  void on_glyphQualityComboBox_currentIndexChanged(int index);

  void on_showTensorsUsingColorFA_clicked();

  void on_clipTensorGlyphsCheckBox_clicked();

  void on_downsampleFactorEditBox_textEdited(const QString &arg1);

  void on_downsampleTractsCheckBox_clicked();

  void on_odfScaleLineEdit_textEdited(const QString &arg1);

  void on_odfScaleSlider_valueChanged(int value);

  void on_trackDisplayColorSelectionButton_clicked();

  void on_roiTableWidget_cellDoubleClicked(int row, int column);

  void on_roiTableWidget_cellChanged(int row, int column);

  void on_addSpherePushButton_clicked();

  void on_removeSpherePushButton_clicked();

  void on_roiTableWidget_itemSelectionChanged();

  void on_saveROIsPushButton_clicked();

  void on_loadROIsPushButton_clicked();

  void on_showSphereInSliceViewCheckBox_clicked();

  void on_excludeLabelsLineEdit_textChanged();

  void on_excludeLabelListCheckBox_clicked();

  void on_odfMinMaxCheckBox_clicked();

  void on_trackDisplayColorModelComboBox_activated(int index);

  void on_lineWidthLineEdit_textEdited(const QString &arg1);

  void on_enableTrackClippingCheckBox_toggled(bool checked);

private:
  Ui::DiffusionToolboxForm *ui;
  BrainSuiteWindow *brainSuiteWindow;
  float tubeSliderScale;
  float ellipseRadiusSliderScale;
  float odfScaleSliderScale;
  int downsampleFactor;
  bool initializing;
  bool blocking;
};

#endif // DIFFUSIONTOOLBOXFORM_H
