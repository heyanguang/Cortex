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

#ifndef BFCTHREADDIALOG_H
#define BFCTHREADDIALOG_H

#include <QDialog>
#include <sstream>
#include <biasfieldcorrectionthread.h>
#include <DS/timer.h>
#include <threaddialogstatus.h>

class BFCGUITool;
class BrainSuiteWindow;

namespace Ui {
class BFCThreadDialog;
}

class BFCThreadDialog : public QDialog
{
  Q_OBJECT

public:
  explicit BFCThreadDialog(BrainSuiteWindow *brainSuiteWindow, QWidget *caller);
  ~BFCThreadDialog();
  bool setStatus(std::string status);
  int launch(BFCGUITool *bfcGUITool);
  std::string errorMessage();
  ThreadDialogStatus::StatusCode status() const { return statusCode; }
  BrainSuiteWindow *brainSuite() { return brainSuiteWindow; }
  bool copyWorkingVolume(Vol3DBase *vOut);
protected:
  void closeEvent(QCloseEvent * event);
  bool killThread();
  Vol3D<float32> vWorking;
  Vol3D<float32> vSpline;
  Vol3D<uint8> vMask;
private slots:
  void on_cancel_clicked();
public slots:
  void updateRuntime();
  void notifyFinished(BFCThread *sender);
  void notifyThreadStartingIteration(int iterationNumber);
  void onTimer();
private:
  Ui::BFCThreadDialog *ui;
  BrainSuiteWindow *brainSuiteWindow;
  BFCGUITool *tool;
  BFCThread *thread;
  QTimer* processTimer;
  Timer runtime;
  float avgLoopTimeMS;
  std::ostringstream errorStream;
protected:
  ThreadDialogStatus::StatusCode statusCode;
};

#endif // BFCTHREADDIALOG_H
