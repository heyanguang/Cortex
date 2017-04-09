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

#ifndef SKULLSTRIPPINGDIALOG_H
#define SKULLSTRIPPINGDIALOG_H

#include <QDialog>
class BrainSuiteWindow;

namespace Ui {
class SkullStrippingDialog;
}

class SkullStrippingDialog : public QDialog
{
  Q_OBJECT

public:
  explicit SkullStrippingDialog(BrainSuiteWindow *parent);
  ~SkullStrippingDialog();
  void setProgress(const int value, const int maxValue);
  void updateStepText(std::string stepname);
  void updateStepText();
  std::string runningStepName();
  bool checkStageInputs();
  bool step();
  bool isFinished();
  void updateAutosaveInfo(bool valid);
  bool autosaveOutputs();
  void updateDialogFromCES();
  void updateCESfromDialog();
  void updateProgress();
private slots:
  void on_runStepButton_clicked();

  void on_previousStepButton_clicked();

  void on_applyButton_clicked();

  void on_bfcButton_clicked();

  void on_diffusionIterationsEditBox_textEdited(const QString &arg1);

  void on_diffusionConstantEditBox_textEdited(const QString &arg1);

  void on_edgeConstantEditBox_textEdited(const QString &arg1);

  void on_trimSpinalCordCheckBox_clicked();

  void on_erosionSizeSpinbox_valueChanged(int arg1);

  void on_skullAndScalpButton_clicked();

  void on_dilateFinalMaskCheckBox_clicked();

private:
  void updateToolSettings();
  BrainSuiteWindow *brainSuiteWindow;
  Ui::SkullStrippingDialog *ui;
};

#endif // SKULLSTRIPPINGDIALOG_H
