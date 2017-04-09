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

#ifndef SKULLANDSCALPDIALOG_H
#define SKULLANDSCALPDIALOG_H

#include <QDialog>

namespace Ui {
class SkullAndScalpDialog;
}

class BrainSuiteWindow;

class SkullAndScalpDialog : public QDialog
{
  Q_OBJECT

public:
  explicit SkullAndScalpDialog(BrainSuiteWindow *brainSuiteWindow);
  ~SkullAndScalpDialog();
  void setProgress(const int value, const int maxValue);
  void updateStepText(std::string stepname);
  void updateProgress();
  void updateDialogFromCES();
  void updateCESfromDialog();
private slots:
  void on_skullComputeThresholdsCheckBox_clicked();

  void on_skullThresholdEditBox_textEdited(const QString &arg1);

  void on_scalpThresholdEditBox_textEdited(const QString &arg1);

  void on_applyButton_clicked();

  void on_runStepButton_clicked();

  void on_bfcButton_clicked();

  void on_previousStepButton_clicked();

  void on_restoreFromPreviousSessionButton_clicked();

private:
  Ui::SkullAndScalpDialog *ui;
  BrainSuiteWindow *brainSuiteWindow;
};

#endif // SKULLANDSCALPDIALOG_H
