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

#ifndef PIALSURFACETHREADDIALOG_H
#define PIALSURFACETHREADDIALOG_H

#include <QDialog>
#include <sstream>
#include <pialsurfacethread.h>
#include <DS/timer.h>
#include <threaddialogstatus.h>

class PialSurfaceTool;
class BrainSuiteWindow;
class QWidget;

namespace Ui {
class PialSurfaceThreadDialog;
}

class PialSurfaceThreadDialog : public QDialog
{
  Q_OBJECT

public:	
  explicit PialSurfaceThreadDialog(BrainSuiteWindow *brainSuiteWindow, QWidget *caller);
  ~PialSurfaceThreadDialog();
  int launch(PialSurfaceTool *pialSurfaceTool);
  std::string errorMessage();
  ThreadDialogStatus::StatusCode status() const { return statusCode; }
protected:
  ThreadDialogStatus::StatusCode statusCode;
  void closeEvent(QCloseEvent * event);
  bool killThread();
private slots:
  void on_cancel_clicked();
public slots:
  void updateRuntime();
  void notifyFinished(PialSurfaceThread *sender);
  void notifyThreadStartingIteration(int iterationNumber);
  void onTimer();
private:
  Ui::PialSurfaceThreadDialog *ui;
  BrainSuiteWindow *brainSuiteWindow;
  PialSurfaceTool *pialSurfaceTool;
  PialSurfaceThread *pialSurfaceThread;
  QTimer* processTimer;
  std::ostringstream errorStream;
  Timer runtime;
};

#endif // PIALSURFACETHREADDIALOG_H
