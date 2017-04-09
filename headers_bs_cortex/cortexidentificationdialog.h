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

#ifndef CortexIdentificationDialog_H
#define CortexIdentificationDialog_H

#include <QDialog>
#include <string>

class BrainSuiteWindow;

namespace Ui {
class CortexIdentificationDialog;
}

class CortexIdentificationDialog : public QDialog
{
  Q_OBJECT

public:
  enum States { Computing=0, Finished=1 };
  explicit CortexIdentificationDialog(BrainSuiteWindow *parent = 0);
  ~CortexIdentificationDialog();
  void setProgress(const int value, const int maxValue);
  void updateDialogFromCES();
  void updateCESfromDialog();
  void setStatusText(std::string status);
  bool checkStageInputs();
  bool computeInnerCortexMask();
  bool step();
  std::string runningStepName();
  bool isFinished();
  void updateAutosaveInfo(bool valid);
private slots:
  void on_applyButton_clicked();

  void on_nextTool_clicked();

  void on_restoreFromPreviousSessionButton_clicked();

  void on_tissueThresholdEditBox_textEdited(const QString &arg1);

  void on_includeAllSubcorticalLabelsCheckBox_clicked();

private:
  Ui::CortexIdentificationDialog *ui;
  BrainSuiteWindow *brainSuiteWindow;
  States state;
};

#endif // CortexIdentificationDialog_H
