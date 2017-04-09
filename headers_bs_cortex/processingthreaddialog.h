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

#ifndef PROCESSINGTHREADDIALOG_H
#define PROCESSINGTHREADDIALOG_H

#include <QDialog>
#include <threaddialogstatus.h>
#include <DS/timer.h>
#include <qthread.h>
#include <qmutex.h>

class ProcessingThreadDialog;
class ProcessingThread : public QThread {
  Q_OBJECT
public:
  explicit ProcessingThread(ProcessingThreadDialog *parent, std::string processTitleStr);
  virtual ~ProcessingThread();
  virtual std::string processTitle() { return processTitleStr; }
  virtual std::string status();
  virtual int progressPosition()=0;
  virtual int progressMaximum()=0;
  virtual bool stop() { return false; }
  void connectSlots();
protected:
  virtual void run()=0;
signals:
  void notifyParentFinished(ProcessingThread *sender);
public slots:
  void whenFinished();
protected:
  ProcessingThreadDialog *parent;
  std::string processTitleStr;
};

namespace Ui {
class ProcessingThreadDialog;
}

class ProcessingThread;

class ProcessingThreadDialog : public QDialog
{
  Q_OBJECT

public:
  explicit ProcessingThreadDialog(QWidget *parent = 0);
  ~ProcessingThreadDialog();
  void setStatus(std::string status);
  ThreadDialogStatus::StatusCode status() const { return statusCode; }
  std::string errorMessage();
  int launch(ProcessingThread *processingThread);
protected:
  void closeEvent(QCloseEvent * event);
  bool killThread();
  bool deleteThread();
public slots:
  void updateRuntime();
  void notifyFinished(ProcessingThread *sender);
  void onTimer();
private slots:
  void on_cancelPushButton_clicked();

private:
  Ui::ProcessingThreadDialog *ui;
  ThreadDialogStatus::StatusCode statusCode;
  ProcessingThread *processingThread;
  QTimer* processTimer;
  Timer runtime;
  QMutex cleanupMutex;
};

#endif // PROCESSINGTHREADDIALOG_H
