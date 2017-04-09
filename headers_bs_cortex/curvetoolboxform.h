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

#ifndef CURVETOOLBOXFORM_H
#define CURVETOOLBOXFORM_H

#include <QWidget>

class BrainSuiteWindow;
class QListWidgetItem;
class DSPoint;
class ProtocolCurve;
class SurfaceAlpha;

namespace Ui {
class CurveToolboxForm;
}

class CurveToolboxForm : public QWidget
{
  Q_OBJECT

public:
  explicit CurveToolboxForm(BrainSuiteWindow *brainSuiteWindow, QWidget *parent = 0);
  ~CurveToolboxForm();
  void initialize();
  void updatePointList();
  void updateProtocol();
  void updateCurveInfo();
  void updateCurveList();
  bool addCurve();
  ProtocolCurve *currentCurve();
  int currentCurveIndex(); // returns -1 if none selected
private slots:
  void on_renderAsTubesCheckBox_clicked();

  void on_tubeRadiusLineEdit_textEdited(const QString &arg1);

  void on_tubeRadiusSlider_valueChanged(int value);

  void on_showCurvesCheckBox_clicked();

  void on_curveListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

  void on_curveColorSelectionButton_clicked();

  void on_showCurvesOnImageSlicesCheckBox_clicked();
  void on_lineWidthLineEdit_textEdited(const QString &arg1);
  void on_showCurvePointsCheckBox_clicked();


  void on_loadProtocolPushButton_clicked();

  void on_loadCurvesetPushButton_clicked();

  void on_saveCurveSetButton_clicked();

  void on_showProtocolCheckBox_clicked();

  void on_protocolLinkPushButton_clicked();

  void on_protocolNameTextLabel_fileDropped(const QString &);

  void on_imageCurveWidthLineEdit_textEdited(const QString &arg1);

private:
  static const float curveTubeSizeScale;
  Ui::CurveToolboxForm *ui;
  BrainSuiteWindow *brainSuiteWindow;
};

#endif // CURVETOOLBOXFORM_H
