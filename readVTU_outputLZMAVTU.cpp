#include <vtkAppendFilter.h>
#include <vtkSphereSource.h>
#include <vtkUnstructuredGrid.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkXMLUnstructuredGridWriter.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

#include <algorithm>
#include <array>
#include <string>
#include <iostream>

int main (void) {

  vtkNew<vtkXMLUnstructuredGridReader> reader;
  const std::string filename = "filename.vtu";
  reader->SetFileName(filename.c_str());
  reader->Update();   
  auto output = reader->GetOutput();

  //// Writer ////
  auto Writer =
    vtkSmartPointer<vtkXMLUnstructuredGridWriter>
    ::New();
  Writer->SetFileName("converted-filename.vtu");
  Writer->SetInputData(output);
  //Writer->SetCompressorTypeToNone();
  //Writer->SetDataModeToAscii();
  Writer->SetCompressorTypeToLZMA();
  //Writer->SetCompressionLevel(5);
  Writer->Write();

  return 0;
}
