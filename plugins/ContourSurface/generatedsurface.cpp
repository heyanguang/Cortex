/*=========================================================================
Ibis Neuronav
Copyright (c) Simon Drouin, Anna Kochanowska, Louis Collins.
All rights reserved.
See Copyright.txt or http://ibisneuronav.org/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.
=========================================================================*/
#include <iostream>

#include "vtkMarchingContourFilter.h"
#include "vtkImageData.h"
#include "vtkProperty.h"
#include "vtkPolyData.h" 
#include "vtkImageGaussianSmooth.h"
#include "vtkImageAccumulate.h"
#include "vtkScalarsToColors.h"
#include "vtkTriangleFilter.h"
#include "vtkDecimatePro.h"

#include "generatedsurface.h"

GeneratedSurface::GeneratedSurface()
{
    m_imageObject = 0;
	this->polyData = 0;

    m_contourValue = 0.0;
    m_radius = DEFAULT_RADIUS;
    m_standardDeviation = DEFAULT_STANDARD_DEVIATION;
    m_gaussianSmoothing = false;
    m_reductionPercent = 20;
}

GeneratedSurface::~GeneratedSurface()
{
	if (this->polyData)
	{
		this->polyData->UnRegister(this);
	}
}

void GeneratedSurface::SetImageObject(vtkImageData *obj)
{
	m_imageObject = obj;
}

void GeneratedSurface::SetPolyData(vtkPolyData * polydata)
{
	if (polydata == this->polyData)
	{
		return;
	}

	if (this->polyData)
	{
		this->polyData->UnRegister(this);
	}
	this->polyData = polydata;
	if (this->polyData)
	{
		this->polyData->Register(this);
	}
}

vtkPolyData *GeneratedSurface::GenerateSurface()
{
    vtkMarchingContourFilter *contourExtractor = vtkMarchingContourFilter::New();
    if (m_gaussianSmoothing)
    {
        vtkImageGaussianSmooth *GaussianSmooth = vtkImageGaussianSmooth::New();
        GaussianSmooth->SetInputData(m_imageObject);
        GaussianSmooth->SetStandardDeviation(m_standardDeviation);
        GaussianSmooth->SetRadiusFactor(m_radius);
        GaussianSmooth->Update();
        contourExtractor->SetInputData( GaussianSmooth->GetOutput() );
        GaussianSmooth->Delete();
    }
    else
    {
        contourExtractor->SetInputData(m_imageObject);
    }
    contourExtractor->SetValue( 0, m_contourValue );
    contourExtractor->Update();

    vtkTriangleFilter *triangleFilter = vtkTriangleFilter::New();
    triangleFilter->SetInputConnection(contourExtractor->GetOutputPort() );
    triangleFilter->ReleaseDataFlagOn();
    triangleFilter->Update();

    if( m_reductionPercent > 0 )
    {
        vtkDecimatePro *decimate = vtkDecimatePro::New();
        decimate->SetInputConnection(triangleFilter->GetOutputPort());
        decimate->SetTargetReduction(m_reductionPercent/100.0);
        decimate->Update();
        this->SetPolyData(decimate->GetOutput());
        decimate->Delete();
    }
    else
        this->SetPolyData(triangleFilter->GetOutput());
    triangleFilter->Delete();
    contourExtractor->Delete();
    return this->polyData;
}
