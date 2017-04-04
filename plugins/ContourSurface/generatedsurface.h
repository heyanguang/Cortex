/*=========================================================================
Ibis Neuronav
Copyright (c) Simon Drouin, Anna Kochanowska, Louis Collins.
All rights reserved.
See Copyright.txt or http://ibisneuronav.org/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.
=========================================================================*/
#ifndef TAG_GENERATEDSURFACE_H_
#define TAG_GENERATEDSURFACE_H_

#include <QVector>
#include <qstring.h>
#include <vtkPolyData.h>

class vtkPolyData;
class ImageObject;
class vtkImageData;
class vtkScalarsToColors;
class vtkImageAccumulate;
class SurfaceSettingsWidget;
class ContourSurfacePluginInterface;

#define DEFAULT_RADIUS 1.0
#define DEFAULT_STANDARD_DEVIATION 1.0

class GeneratedSurface : vtkObject
{
public:
    
    static GeneratedSurface *New() { return new GeneratedSurface; }
	GeneratedSurface();
	~GeneratedSurface();
	vtkPolyData *GenerateSurface();

    void SetImageObject(vtkImageData *obj);
    void SetContourValue(double cv){m_contourValue = cv;}
	void SetPolyData(vtkPolyData * polydata);
    
    //Gaussian smoothing of the generated surface
    bool GetGaussianSmoothingFlag() {return m_gaussianSmoothing;}
    double GetRadiusFactor() {return m_radius;}
    double GetStandardDeviation() {return m_standardDeviation;}
    void SetGaussianSmoothingFlag(bool flag) {m_gaussianSmoothing = flag;}
    void SetRadiusFactor(double radiusFactor){m_radius = radiusFactor;}
    void SetStandardDeviation(double deviation){m_standardDeviation = deviation;}

protected:
    ContourSurfacePluginInterface * m_pluginInterface;
	vtkImageData *m_imageObject;
    double m_contourValue;

    //Gaussian smoothing of the surface
    bool m_gaussianSmoothing;
    double m_radius;
    double m_standardDeviation;
    int m_reductionPercent;
	vtkPolyData *polyData;
};

#endif //TAG_GENERATEDSURFACE_H_
