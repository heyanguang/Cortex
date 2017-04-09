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

#ifndef NONUNIFORMITYCORRECTIONDIALOG_H
#define NONUNIFORMITYCORRECTIONDIALOG_H

#include <QDialog>
class BrainSuiteWindow;

namespace Ui {
class NonuniformityCorrectionDialog;
}

class NonuniformityCorrectionDialog : public QDialog
{
  Q_OBJECT

public:
  explicit NonuniformityCorrectionDialog(BrainSuiteWindow *parent = 0);
  ~NonuniformityCorrectionDialog();
  void updateStepText(std::string stepNameText);
  void setProgress(const int value, const int maxValue);
  bool step();
  std::string runningStepName();
  bool isFinished();
  void updateProgressBar();
  void updateDialogFromCES();
  void updateCESfromDialog();
  void updateAutosaveInfo(bool valid);
  void updateWidgetState();
private slots:
  void on_applyButton_clicked();

  void on_runStepButton_clicked();

  void on_previousStepButton_clicked();

  void on_nextTool_clicked();

  void on_lowRangeButton_clicked();

  void on_mediumRangeButton_clicked();

  void on_highRangeButton_clicked();

  void on_iterativeModeCheckBox_clicked();

  void on_histogramRadiusEditBox_textEdited(const QString &arg1);

  void on_sampleSpacingEditBox_textEdited(const QString &arg1);

  void on_controlPointSpacingEditBox_textEdited(const QString &arg1);

  void on_splineStiffnessEditBox_textEdited(const QString &arg1);

  void on_cuboidRadioButton_clicked();

  void on_ellipsoidRadioButton_clicked();

  void on_biasRangeLowerEditBox_textEdited(const QString &arg1);

  void on_biasRangeUpperEditBox_textEdited(const QString &arg1);

  void on_restoreFromPreviousSessionButton_clicked();

private:
  Ui::NonuniformityCorrectionDialog *ui;
  BrainSuiteWindow *brainSuiteWindow;
};

#endif // NONUNIFORMITYCORRECTIONDIALOG_H
