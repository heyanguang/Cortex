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

#ifndef CEREBRUMEXTRACTIONDIALOG_H
#define CEREBRUMEXTRACTIONDIALOG_H

#include <QDialog>
class BrainSuiteWindow;
#include <sstream>

namespace Ui {
class CerebrumExtractionDialog;
}

class CerebrumExtractionDialog : public QDialog
{
  Q_OBJECT

public:
  explicit CerebrumExtractionDialog(BrainSuiteWindow *parent = 0);
  ~CerebrumExtractionDialog();
  void updateDialogFromCES();
  void updateCESfromDialog();
  void updateStepName(std::string stepName);
  bool checkStageInputs();
  bool step();
  std::string runningStepName();
  bool isFinished();
  void updateStepName();
  void updateRunningStepName();
  void updateAutosaveInfo(bool valid);
  void setProgress(const int value, const int maxvalue);
private slots:
  void on_applyButton_clicked();

  void on_runStepButton_clicked();

  void on_previousStepButton_clicked();

  void on_nextTool_clicked();

  void on_restoreFromPreviousSessionButton_clicked();

  void on_atlasPushButton_clicked();

  void on_labelsPushButton_clicked();

  void on_tempPathPushButton_clicked();

  void on_linearConvergenceEditBox_textEdited(const QString &arg1);

  void on_warpConvergenceEditBox_textEdited(const QString &arg1);

  void on_costFunctionComboBox_currentIndexChanged(int index);

  void on_verboseCheckBox_clicked();

  void on_showAlignedAtlasAsOverlayCheckBox_clicked();

  void on_warpLevelSpinBox_valueChanged(int arg1);

  void on_useCentroidsCheckBox_clicked();

private:
  Ui::CerebrumExtractionDialog *ui;
  BrainSuiteWindow *brainSuiteWindow;
  std::ostringstream outputStream;
};

#endif // CEREBRUMEXTRACTIONDIALOG_H
