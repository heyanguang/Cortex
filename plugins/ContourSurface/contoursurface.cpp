#include "mainwindow.h"

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkRendererCollection.h>
#include <vtkImageData.h>
#include <vtkProperty.h>
#include "generatedsurface.h"

bool MainWindow::contourSurface()
{
	GeneratedSurface *generatedSurface = GeneratedSurface::New();

	double imageRange[2];
	localVTKImage->GetVTKImage()->GetScalarRange(imageRange);
	double contourValue = imageRange[0] + (imageRange[1] - imageRange[0]) / 5.0; //the best seems to be 20% of max, tested on Colin27
	generatedSurface->SetImageObject(localVTKImage->GetVTKImage());
	generatedSurface->SetContourValue(contourValue);
	generatedSurface->SetGaussianSmoothingFlag(true);
	vtkPolyData *surface = generatedSurface->GenerateSurface();
	//vtkSmartPointer<vtkPolyDataReader> reader =
	//	vtkSmartPointer<vtkPolyDataReader>::New();
	//reader->SetInputDataObject(surface);
	//reader->Update();

	// Visualize
	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	//mapper->SetInputConnection(reader->GetOutputPort());
	mapper->SetInputData(surface);
	mapper->ScalarVisibilityOff();

	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetDiffuseColor(1, 1, 1);

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderer->AddActor(actor);
	renderer->SetBackground(.2, .3, .4);

	// clean previous renderers and then add the current renderer
	auto window = widgetCortex->GetRenderWindow();
	auto collection = window->GetRenderers();
	auto item = collection->GetNumberOfItems();
	while (item)
	{
		window->RemoveRenderer(collection->GetFirstRenderer());
		item = collection->GetNumberOfItems();
	}
	window->AddRenderer(renderer);
	window->Render();

	// initialize the interactor
	interactor->Initialize();
	interactor->Start();
	return true;
}
