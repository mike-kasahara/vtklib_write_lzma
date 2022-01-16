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

  //// PointData ////
  auto PointData =
    vtkSmartPointer<vtkFloatArray>::New();
  PointData->SetNumberOfTuples(4);
  PointData->SetName("Point Scalar Data");
  PointData->SetComponent(0,0, 0.123);
  PointData->SetComponent(1,0, 1.234);
  PointData->SetComponent(2,0, 2.345);
  PointData->SetComponent(3,0, 3.456);
  Grid->GetPointData()->AddArray(PointData);
  //// CellData ////
  auto CellData =
    vtkSmartPointer<vtkFloatArray>::New();
  CellData->SetNumberOfTuples(1);
  CellData->SetName("Cell Scalar Data");
  CellData->SetComponent(0,0, 3.14);
  Grid->GetCellData()->AddArray(CellData);

  //// Writer ////
  auto Writer =
    vtkSmartPointer<vtkXMLUnstructuredGridWriter>
    ::New();
  Writer->SetInputData(Grid);
  Writer->SetFileName("sample-b.vtu");
  Writer->SetCompressorTypeToNone();
  Writer->SetDataModeToAscii();
  Writer->Write();

  return 0;
}
