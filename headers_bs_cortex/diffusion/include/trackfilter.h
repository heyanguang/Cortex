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

#ifndef TractFilter_H
#define TractFilter_H

#include <fibertrackset.h>
#include <vol3d.h>

class TrackFilter {
public:
  template <class T>
  static float fiberLength(const T &points)
  {
    float length=0;
    if (points.size())
    {
      typename T::const_iterator point=points.begin();
      DSPoint lastPoint = *point++;
      for (; point != points.end(); point++)
      {
        length += (*point-lastPoint).mag();
        lastPoint = *point;
      }
    }
    return length;
  }
  template <class T>
  static int getLabel(const Vol3D<T> &vLabel, const DSPoint point)
  {
    const int cx = vLabel.cx;
    const int cy = vLabel.cy;
    const int cz = vLabel.cz;
    const float rx = vLabel.rx;
    const float ry = vLabel.ry;
    const float rz = vLabel.rz;
    const int x = int(point.x/rx+0.5f);
    const int y = int(point.y/ry+0.5f);
    const int z = int(point.z/rz+0.5f);
    if ((x<0)||(y<0)||(z<0)||(x>=cx)||(y>=cy)||(z>=cz)) return 0; // or -1?
    return vLabel(x,y,z);
  }
  template <class T, class VT>
  static size_t labelCount(const Vol3D<T> &vLabel, const VT &points, const int label)
  {
    size_t count=0;
    for (typename VT::const_iterator point=points.begin(); point != points.end(); point++)
    {
      count+=(getLabel(vLabel,*point)==label);
    }
    return count;
  }
  template <class T>
  static FiberTrackSet *filterTractsByLabelAndLength(Vol3D<T> &vLabel, FiberTrackSet *tractSet, const int label, const float lengthThreshold)
  {
    FiberTrackSet *subset = new FiberTrackSet;
    for (std::vector<FiberTrack>::iterator curve=tractSet->curves.begin(); curve!=tractSet->curves.end(); curve++)
    {
      if (curve->points.size()>0)
      {
        if (lengthThreshold>0)
        {
          if (fiberLength(curve->points)<lengthThreshold) continue;
        }
        size_t n = labelCount(vLabel,curve->points,label);
        if (n>0)
          subset->curves.push_back(*curve);
      }
    }
    return subset;
  }
  template <class T>
  static size_t filterTractsByLabelAndLengthCountOnly(Vol3D<T> &vLabel, FiberTrackSet *tractSet, const int label, const float lengthThreshold)
  {
    size_t count=0;
    for (std::vector<FiberTrack>::iterator curve=tractSet->curves.begin(); curve!=tractSet->curves.end(); curve++)
    {
      if (curve->points.size()>0)
      {
        if (lengthThreshold>0)
        {
          if (fiberLength(curve->points)<lengthThreshold) continue;
        }
        size_t n = labelCount(vLabel,curve->points,label);
        if (n>0) count++;
      }
    }
    return count;
  }
  template <class T>
  static FiberTrackSet *filterTractsByLabelAndLength(const Vol3D<T> &vLabel, const FiberTrackSet *tractSet, const std::vector<int> &includeList,
                                                     const std::vector<int> &excludeList,
                                                     const float lengthThreshold, bool opAnd)
  {
    FiberTrackSet *subset = new FiberTrackSet;
    for (std::vector<FiberTrack>::const_iterator curve=tractSet->curves.begin(); curve!=tractSet->curves.end(); curve++)
    {
      if (curve->points.size()>0)
      {
        if (lengthThreshold>0)
        {
          if (fiberLength(curve->points)<lengthThreshold) continue;
        }
        if (includeList.size())
        {
          if (opAnd)
          {
            bool hasAll=true;
            for (size_t i=0;i<includeList.size();i++)
            {
              size_t n = labelCount(vLabel,curve->points,includeList[i]);
              if (n==0) { hasAll=false; break; }
            }
            if (!hasAll) continue;
          }
          else
          {
            bool hasSome=false;
            for (size_t i=0;i<includeList.size();i++)
            {
              size_t n = labelCount(vLabel,curve->points,includeList[i]);
              if (n>0) { hasSome=true; break; }
            }
            if (!hasSome) continue;
          }
        }
        bool keepCurve=true;
        for (size_t i=0;i<excludeList.size();i++)
        {
          size_t n = labelCount(vLabel,curve->points,excludeList[i]);
          if (n>0) { keepCurve=false; break; }
        }
        if (keepCurve)
        {
          subset->curves.push_back(*curve);
        }
      }
    }
    return subset;
  }
  static bool hasPointInSphere(const std::vector<DSPoint>  &points,  const DSPoint center, const float radius);
  static FiberTrackSet *filterTracksByLength(const FiberTrackSet *tractSet, const float lengthThreshold);
  static FiberTrackSet *sphericalFilter(const FiberTrackSet *trackSet, const DSPoint center, const float radius);
  static FiberTrackSet *reduceTrackSet(const FiberTrackSet *trackSet, const std::vector<bool> &keepList);
  static FiberTrackSet *sphericalFilterExclude(const FiberTrackSet *tractSet, const DSPoint center, const float radius);
  static bool sphericalFilterIndex(std::vector<bool> &keep, const FiberTrackSet *trackSet, const DSPoint center, const float radius);
  template <class T>
  static int findTrackIntersections(std::vector<bool> &matchList, const FiberTrackSet *trackSet, const Vol3D<T> &vLabel, const std::vector<int> &labelList);
  static FiberTrackSet *filterExcludedLabels(const FiberTrackSet *fiberTrackSet, const Vol3DBase *labelVolume, std::vector<int> excludeLabels);
};

#endif
