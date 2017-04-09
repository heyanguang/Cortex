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

#ifndef DELINEATIONTOOLBOXFORM_H
#define DELINEATIONTOOLBOXFORM_H

#include <QWidget>

#include <labelbrush.h>
class ImageWidget;
class EditDSBitmap;
class BrainSuiteWindow;
class UndoWrapper;
class QModelIndex;

namespace Ui {
class DelineationToolboxForm;
}

class BrainSuiteWindow;

enum MaskStates { DrawEverywhere = 0, DrawInsideMask = 1, DrawOutsideMask = 2 };

class DelineationToolboxForm : public QWidget
{
  Q_OBJECT
public:
  explicit DelineationToolboxForm(BrainSuiteWindow *brainSuiteWindow, QWidget *parent = 0);
  ~DelineationToolboxForm();
  QSize sizeHint() const;
  bool chooseLabel(const int labelID);
  int currentLabel() { return currentLabelID; }
  void setThresholdRange(float minv, float maxv, int nlevels);
  void setThresholdRange(int minv, int maxv);
  void showMaskTool();
  void showPainterTool();
  bool incrementLabel();
  bool decrementLabel();
  bool isEditingMask();
  bool isEditingLabels();
  bool alwaysEditMask();
  bool alwaysEditLabels();
  bool toggleEditState();
  void updateUndoButton();
  void updateEditBitmaps();
  bool setUndoPoint(std::string description);
  bool setUndoPoint(IPoint3D &point, std::string description);
  void mousePressed(ImageWidget *port, const IPoint3D &position, QMouseEvent *event);
  void mouseMoveTo(ImageWidget *port, const IPoint3D &position, QMouseEvent *event);
  void maskToolMouseMoveTo(ImageWidget *port, const IPoint3D &position, QMouseEvent *event);
  void labelPainterMouseMoveTo(ImageWidget *port, const IPoint3D &position, QMouseEvent *event);
  void mouseReleased(ImageWidget *port, const IPoint3D &position, QMouseEvent *event);
  void thresholdIfAutomatic();
  bool threshold(bool saveUndoPoint=false);
  void disableEdits();
  void undoLastAction();
  void decreaseBrushSize();
  void increaseBrushSize();
  void updateLabelSelectionComboBox();
  void updateColorSelectionButton();
  bool newVolume();
  float getThreshold();
  EditDSBitmap *editBitmap(Orientation::Code orientation);
  MaskStates getMaskState();
  LabelBrush brushXY;
  LabelBrush brushXZ;
  LabelBrush brushYZ;
private slots:
  void on_loadMaskButton_clicked();
  void on_dilateCubeButton_clicked();
  void on_dilateDiamondButton_clicked();
  void on_erodeCubeButton_clicked();
  void on_erodeDiamondButton_clicked();
  void on_brushSizeSpinBox_valueChanged(int arg1);
  void on_use3DBrushCheckBox_clicked();
  void on_saveMaskButton_clicked();
  void on_thresholdEditBox_textEdited(const QString &arg1);
  void on_autoUpdateCheckbox_clicked();
  void on_thresholdButton_clicked();
  void on_thresholdSlider_valueChanged(int value);
  void on_invertButton_clicked();
  void on_applyMasktoImage_clicked();
  void on_fillBackgroundButton_clicked();
  void on_selectForeground_clicked();
  void on_editMaskButton_clicked();
  void on_undoButton_clicked();
  void on_redoButton_clicked();
  void on_thresholdSlider_sliderReleased();
  void on_thresholdSlider_sliderPressed();
  void on_quickSurfaceButton_clicked();

  void on_editLabelButton_clicked();
  void on_colorSelectionButton_clicked();
  void on_labelIDEditBox_textEdited(const QString &arg1);
  void on_labelDescriptionEditBox_textEdited(const QString &arg1);
  void on_labelAbbrevEditBox_textEdited(const QString &arg1);
  void on_eyedropButton_clicked();
  void on_loadLabelDescriptionsButton_clicked();
  void on_saveLabelDescriptions_clicked();
  void on_newLabelVolumeButton_clicked();
  void on_loadLabelVolumeButton_clicked();
  void on_saveLabelVolumeButton_clicked();
  void on_fill2DButton_clicked();
  void on_fill3DButton_clicked();
  void on_labelBrushSizeSpinBox_valueChanged(int arg1);
  void on_labelSelectionComboBox_currentIndexChanged(int index);
  void on_computeVolumesPushButton_clicked();
  void on_toolBox_currentChanged(int index);

  void on_labelTableWidget_doubleClicked(const QModelIndex &index);
  void on_saveROIDetailsTextPushButton_clicked();

  void on_makeMaskFromLabelsPushButton_clicked();

  void on_updateMaskLabelListPushButton_clicked();

  void on_makeSurfacesFromLabelsPushButton_clicked();

  void on_roiFilterLineEdit_textEdited(const QString &filter);

  void on_labelMaskLineEdit_textEdited(const QString &arg1);

  void on_labelMaskTableWidget_itemSelectionChanged();

  void slot_labelTableHeaderClicked(int);
  void slot_labelMaskTableHeaderClicked(int);

private:
  Ui::DelineationToolboxForm *ui;
  BrainSuiteWindow *brainSuiteWindow;
  UndoWrapper *maskToolundoSystem;
  int currentLabelID;
  bool lockCombobox;
  bool paintedSomething;
  int sortColumn;
  bool sortAscending;
};

#endif // DELINEATIONTOOLBOXFORM_H
