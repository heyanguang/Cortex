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

#ifndef COMPUTECONNECTIVITYTHREADDIALOG_H
#define COMPUTECONNECTIVITYTHREADDIALOG_H

#include <QDialog>
#include <brainsuitewindow.h>
#include <DS/timer.h>
#include <threaddialogstatus.h>
#include <connectivityproperties.h>

namespace Ui {
class ComputeConnectivityThreadDialog;
}

class ComputeConnectivityThread;

class ComputeConnectivityThreadDialog : public QDialog
{
  Q_OBJECT
public:
  explicit ComputeConnectivityThreadDialog(BrainSuiteWindow *brainSuiteWindow, QWidget *caller);
  bool setStatus(std::string status);
  int launch();
  ~ComputeConnectivityThreadDialog();
  ThreadDialogStatus::StatusCode status() const { return statusCode; }
  bool mergeCortialROIs;
protected:
  void closeEvent(QCloseEvent * event);
  bool killThread();
private slots:
  void on_cancel_clicked();
public slots:
  void updateRuntime();
  void notifyFinished(ComputeConnectivityThread *sender);
  void notifyThreadStartingIteration(int iterationNumber);
  void onTimer();
private:
  Ui::ComputeConnectivityThreadDialog *ui;
  BrainSuiteWindow *brainSuiteWindow;
  ComputeConnectivityThread *thread;
  QTimer* processTimer;
  Timer runtime;
  float avgLoopTimeMS;
  std::ostringstream errorStream;
  ThreadDialogStatus::StatusCode statusCode;
  int nTracks;
};

#endif // COMPUTECONNECTIVITYTHREADDIALOG_H
