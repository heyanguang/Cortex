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

#ifndef REGISTRATIONPROCESSDIALOG_H
#define REGISTRATIONPROCESSDIALOG_H

#include <QDialog>
#include <sstream>
#include <DS/timer.h>

class SurfaceLabelProcess;

namespace Ui {
class RegistrationProcessDialog;
}

class RegistrationProcessDialog : public QDialog
{
  Q_OBJECT

public:
  enum ReturnState { NotRun=-1, Success=0, Error=1, CanceledByUser=2 };
  explicit RegistrationProcessDialog(QWidget *parent = 0);
  ~RegistrationProcessDialog();
  int run(QString program, QString directory, QStringList arguments);
  QString processName;
  QString tag;
  SurfaceLabelProcess *process;
  void parseOutput(QString msg);
  std::string errorMessage() { return errorStream.str(); }
  std::string processLog() { return processStream.str(); }
  ReturnState state() { return returnState; }
protected:
  ReturnState returnState;
  Timer runtime;
  virtual void	closeEvent ( QCloseEvent * event );
private:
  Ui::RegistrationProcessDialog *ui;
  std::ostringstream statusStream;
  std::ostringstream errorStream;
  std::ostringstream processStream;
  QTimer* processTimer;
  void killThread();
public slots:
  void notifyFinished(SurfaceLabelProcess *sender);
  void onTimer();
private slots:
  void on_cancel_clicked();
};

#endif // REGISTRATIONPROCESSDIALOG_H
