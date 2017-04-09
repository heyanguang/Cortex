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

#ifndef DUALREGISTRATIONPROCESSDIALOG_H
#define DUALREGISTRATIONPROCESSDIALOG_H

#include <QDialog>
#include <sstream>
#include <DS/timer.h>

class DualRegistrationProcess;

namespace Ui {
class DualRegistrationProcessDialog;
}

class DualRegistrationProcessDialog : public QDialog
{
  Q_OBJECT

public:
  enum ReturnState { NotRun=-1, Success=0, Error=1, CanceledByUser=2 };
  explicit DualRegistrationProcessDialog(QWidget *parent = 0);
  ~DualRegistrationProcessDialog();
  int run(QString program, QString directory, QStringList leftArguments, QStringList rightArguments);
  void parseOutput(DualRegistrationProcess *sender, QString msg);
  std::string errorMessage() { return errorStream.str(); }
  std::string leftProcessLog()  { return leftProcessStream.str(); } // only if error
  std::string rightProcessLog()  { return rightProcessStream.str(); } // only if error

  ReturnState state() { return returnState; }
protected:
  ReturnState returnState;
  Timer runtime;
  virtual void	closeEvent ( QCloseEvent * event );
private:
  Ui::DualRegistrationProcessDialog *ui;
  DualRegistrationProcess *leftProcess;
  DualRegistrationProcess *rightProcess;
  std::ostringstream leftStatusStream;
  std::ostringstream rightStatusStream;
public:
  QString processName;
  QString leftTag;
  QString rightTag;
private:
  std::ostringstream errorStream;
  std::ostringstream leftProcessStream; // only if error
  std::ostringstream rightProcessStream;// only if error
  QTimer* processTimer;
public slots:
  void notifyFinished(DualRegistrationProcess *sender);
  void onTimer();
private slots:
  void on_cancel_clicked();
};

#endif // DUALREGISTRATIONPROCESSDIALOG_H
