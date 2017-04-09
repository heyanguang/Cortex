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

#ifndef TISSUECLASSIFICATIONDIALOG_H
#define TISSUECLASSIFICATIONDIALOG_H

#include <QDialog>
class BrainSuiteWindow;

namespace Ui {
class TissueClassificationDialog;
}

class TissueClassificationDialog : public QDialog
{
  Q_OBJECT

public:
  explicit TissueClassificationDialog(BrainSuiteWindow *parent = 0);
  ~TissueClassificationDialog();
  void setProgress(const int value, const int maxValue);
  void updateStepText(std::string s);
  bool step();
  std::string runningStepName();
  bool isFinished();
  void updateProgressBar();
  void updateAutosaveInfo(bool valid);
  void updateDialogFromCES();
  void updateCESfromDialog();
private slots:
  void on_applyButton_clicked();

  void on_runStepButton_clicked();

  void on_previousStepButton_clicked();

  void on_nextTool_clicked();

  void on_spatialPriorWeightingEditBox_textEdited(const QString &arg1);

  void on_restoreFromPreviousSessionButton_clicked();

private:
  Ui::TissueClassificationDialog *ui;
  BrainSuiteWindow *brainSuiteWindow;
};

#endif // TISSUECLASSIFICATIONDIALOG_H
