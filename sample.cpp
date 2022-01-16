#include <vtkSmartPointer.h>
#include <vtkTetra.h>
#include <vtkCellArray.h>
#include <vtkUnstructuredGrid.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkFloatArray.h>
int main(void)
{
  // Points ////
  auto Points = vtkSmartPointer<vtkPoints>::New();
  Points->SetDataTypeToFloat();
  Points->SetNumberOfPoints(4);
  Points->SetPoint(0, 0., 0., 0.);
  Points->SetPoint(1, 1., 0., 0.);
  Points->SetPoint(2, 0., 1., 0.);
  Points->SetPoint(3, 0., 0., 1.);

  //// Connectivity ////
  auto Connectivity = vtkSmartPointer<vtkIdTypeArray>::New();
  Connectivity->SetNumberOfTuples(5);
  Connectivity->SetComponent(0,0, 4);
  Connectivity->SetComponent(1,0, 0);
  Connectivity->SetComponent(2,0, 1);
  Connectivity->SetComponent(3,0, 2);
  Connectivity->SetComponent(4,0, 3);

  //// CellArray ////
  auto CellArray =
    vtkSmartPointer<vtkCellArray>::New();
  CellArray->SetCells(1, Connectivity);

  //// Grid ////
  auto Grid =
    vtkSmartPointer<vtkUnstructuredGrid>::New();
  Grid->SetPoints(Points);
  Grid->SetCells(VTK_TETRA, CellArray);

  //// Writer ////
  auto Writer =
    vtkSmartPointer<vtkXMLUnstructuredGridWriter>
    ::New();
  Writer->SetInputData(Grid);
  Writer->SetFileName("sample-a.vtu");
  Writer->SetCompressorTypeToNone();
  Writer->SetDataModeToAscii();
  Writer->Write();

  return 0;
}
