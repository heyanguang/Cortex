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

#ifndef DewispDialog_H
#define DewispDialog_H

#include <QDialog>
class BrainSuiteWindow;

namespace Ui {
class DewispDialog;
}

class DewispDialog : public QDialog
{
  Q_OBJECT

public:
  explicit DewispDialog(BrainSuiteWindow *parent = 0);
  ~DewispDialog();
  void setProgress(const int value, const int maxValue);
  void updateStepText(std::string status);
  void updateDialogFromCES();
  void updateCESfromDialog();
  void setStatusText(std::string status);
  bool checkStageInputs();
  bool applyDewispFilter();
  bool step();
  std::string runningStepName();
  bool isFinished();
  void updateAutosaveInfo(bool valid);
private slots:
  void on_applyButton_clicked();

  void on_nextTool_clicked();

  void on_restoreFromPreviousSessionButton_clicked();

  void on_dewispThresholdEditBox_textEdited(const QString &arg1);

  void on_dewispMaximumIterationsEditBox_textEdited(const QString &arg1);

private:
  Ui::DewispDialog *ui;
  BrainSuiteWindow *brainSuiteWindow;
};

#endif // DewispDialog_H
