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

#ifndef DSFILEPATHBUTTON_H
#define DSFILEPATHBUTTON_H

#include <QCommandLinkButton>

class DSFilePathButton : public QCommandLinkButton
{
  Q_OBJECT
public:
  explicit DSFilePathButton(QWidget *parent = 0);
  void setFlat(bool flag);
  QString filepath;
protected:
  virtual void paintEvent(QPaintEvent *e);
signals:

public slots:

};

#endif // DSFILEPATHBUTTON_H
