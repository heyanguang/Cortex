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


#ifndef SURFACEDISPLAYFORM_H
#define SURFACEDISPLAYFORM_H

#include <QWidget>
#include <vector>

class BrainSuiteWindow;
class SurfaceAlpha;
class QListWidgetItem;
class SurfaceAlpha;

namespace Ui {
class SurfaceDisplayForm;
}

class SurfaceDisplayForm : public QWidget
{
  Q_OBJECT

public:
  explicit SurfaceDisplayForm(BrainSuiteWindow *brainSuiteWindow, QWidget *parent = 0);
  ~SurfaceDisplayForm();
  void updateSurfaceList();
  void updateSurfaceSelection();
  void updateSliceViewStatus();
  void updateGeneralCheckboxes();
  void selectShownSurfaces(); // visible as in shown
private slots:
  void on_showSurfaceCheckBox_clicked();

  void on_surfaceListWidget_itemSelectionChanged();

  void on_showAsWireframe_clicked();

  void on_vertexColorCheckBox_clicked();

  void on_solidColorCheckBox_clicked();

  void on_disableClippingCheckBox_clicked();

  void on_colorSelectionButton_clicked();

  void on_openPushButton_clicked();

  void on_savePushButton_clicked();

  void on_removePushButton_clicked();

  void on_showImageSlicesCheckBox_clicked();

  void on_showXYSliceCheckBox_clicked();

  void on_showXZSliceCheckBox_clicked();

  void on_showYZSliceCheckBox_clicked();

  void on_backgroundColorSelectionButton_clicked();

  void on_translucentCheckBox_clicked();

  void on_depthSortCheckBox_clicked();

  void on_alphaLineEdit_textEdited(const QString &arg1);

  void on_recolorSurfacePushButton_clicked();

  void on_showFibersCheckBox_clicked();

  void on_showTensorGlyphs_clicked();

  void on_showODFGlpyhsCheckBox_clicked();

  void on_showSurfacesCheckBox_clicked();

  void on_lightingCheckBox_clicked();

  void on_sliceOpacityLineEdit_textEdited(const QString &arg1);

  void on_translucentSliceCheckBox_clicked();

  void on_zoomLineEdit_textEdited(const QString &arg1);

  void on_showSmoothedCheckBox_clicked();

  void currentColorChanged(const QColor & color);
protected:
  bool findSelectedSurfaces(std::vector<SurfaceAlpha *> &surfaces); // finds the currently selected surface
private:
  Ui::SurfaceDisplayForm *ui;
  BrainSuiteWindow *brainSuiteWindow;
};

#endif // SURFACEDISPLAYFORM_H
