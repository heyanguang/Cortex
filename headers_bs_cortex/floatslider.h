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

#ifndef QFLOATSLIDER_H
#define QFLOATSLIDER_H

#include <QSlider>

class FloatSlider : public QSlider
{
    Q_OBJECT
public:
    explicit FloatSlider(QWidget *parent = 0);
    bool setFloatRange(float min, float max, int nLevels);
    bool setIntRange(int min, int max);
    float valuef();
    float setFloatValue(float f); // returns the value used, which is constrained to the range of the slider
private:
    bool rescale;
    float minf,maxf,scale;
signals:

public slots:

};

#endif // QFLOATSLIDER_H
