#include "mainwindow.h"

#include <vtkRenderer.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRendererCollection.h>
#include <vtkImageData.h>
#include <vtkMarchingCubes.h>

bool MainWindow::on_action_MarchingCubes_triggered()
{
	//vtkSmartPointer<vtkMetaImageReader> reader =
	//	vtkSmartPointer<vtkMetaImageReader>::New();
	//reader->SetInputData((vtkDataObject *)(localVTKImage->GetVTKImage()->NewInstance()));

	// An isosurface, or contour value of 500 is known to correspond to the
	// skin of the patient.
	vtkSmartPointer<vtkMarchingCubes> skinExtractor =
		vtkSmartPointer<vtkMarchingCubes>::New();
	//skinExtractor->SetInputConnection(reader->GetOutputPort());
	skinExtractor->SetInputData(localVTKImage->GetVTKImage());
	skinExtractor->SetValue(0, 100);

	vtkSmartPointer<vtkPolyDataMapper> skinMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	skinMapper->SetInputConnection(skinExtractor->GetOutputPort());
	skinMapper->ScalarVisibilityOff();

	vtkSmartPointer<vtkActor> skin =
		vtkSmartPointer<vtkActor>::New();
	skin->SetMapper(skinMapper);
	skin->GetProperty()->SetDiffuseColor(1, 1, 1);

	// Create the renderer, the render window, and the interactor. The renderer
	// draws into the render window, the interactor enables mouse- and
	// keyboard-based interaction with the data within the render window.
	vtkSmartPointer<vtkRenderer> aRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	aRenderer->AddActor(skin);
	aRenderer->SetBackground(.2, .3, .4);

	// clean previous renderers and then add the current renderer
	auto window = widgetCortex->GetRenderWindow();
	auto collection = window->GetRenderers();
	auto item = collection->GetNumberOfItems();
	while (item)
	{
		window->RemoveRenderer(collection->GetFirstRenderer());
		item = collection->GetNumberOfItems();
	}
	window->AddRenderer(aRenderer);
	window->Render();

	// Initialize the event loop and then start it.
	interactor->Initialize();
	interactor->Start();
	return true;
}
