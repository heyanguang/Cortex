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

#ifndef SVREGISTRATIONDIALOG_H
#define SVREGISTRATIONDIALOG_H

#include <QDialog>
#include <sstream>
class BrainSuiteWindow;

namespace Ui {
class SVRegistrationDialog;
}

class SVRegistrationDialog : public QDialog
{
  Q_OBJECT

public:
  explicit SVRegistrationDialog(BrainSuiteWindow *brainSuiteWindow);
  ~SVRegistrationDialog();
  void updateDialogFromCES();
  void updateCESfromDialog();
  void updateStepText(std::string status);
  bool initialize();
  bool labelSurfaces();
  bool makeVolumeMap();
  bool registerVolumes();
  bool refineROIs();
  bool refineRegistration();
  bool refineSulci();
  bool computeMeasurements();
  void updateStatusText();
  void updateProgressBar();
  void setProgress(const int value, const int maxValue);
  bool isFinished();
  bool step();
  std::string runningStepName();
  void updateSVRegPath();
private slots:
  void on_applyButton_clicked();
  void on_runStepButton_clicked();

  void on_surfaceRegistrationOnlyCheckBox_clicked();

  void on_refineSulcalCurvesCheckBox_clicked();

  void on_labeledAtlasComboBox_currentIndexChanged(int index);

  void on_extendLabelsCheckBox_clicked();

private:
  Ui::SVRegistrationDialog *ui;
  BrainSuiteWindow *brainSuiteWindow;
  std::ostringstream statusStream;
};

#endif // SVREGISTRATIONDIALOG_H
