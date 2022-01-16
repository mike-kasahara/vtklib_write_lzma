#include <vtkSmartPointer.h>
#include <vtkTetra.h>
#include <vtkCellArray.h>
#include <vtkUnstructuredGrid.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkFloatArray.h>
#include <vtkLZMADataCompressor.h>
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

  // PointData2 ////
  auto PointData2 =
    vtkSmartPointer<vtkFloatArray>::New();
  PointData2->SetNumberOfComponents(3);
  PointData2->SetNumberOfTuples(4);
  PointData2->SetName("Point Vector Data");
  PointData2->SetComponent(0,0, 0.0);
  PointData2->SetComponent(0,1, 0.1);
  PointData2->SetComponent(0,2, -0.2);
  PointData2->SetComponent(1,0, 0.1);
  PointData2->SetComponent(1,1, 0.2);
  PointData2->SetComponent(1,2, 0.3);
  PointData2->SetComponent(2,0, 0.2);
  PointData2->SetComponent(2,1, 0.3);
  PointData2->SetComponent(2,2, 0.4);
  PointData2->SetComponent(3,0, 0.3);
  PointData2->SetComponent(3,1, 0.4);
  PointData2->SetComponent(3,2, 0.5);
  Grid->GetPointData()->AddArray(PointData2);

  //// CellData2 ////
  auto CellData2 =
    vtkSmartPointer<vtkFloatArray>::New();
  CellData2->SetNumberOfComponents(3);
  CellData2->SetNumberOfTuples(1);
  CellData2->SetName("Cell Vector Data");
  CellData2->SetComponent(0,0, 1.2);
  CellData2->SetComponent(0,1, -2.3);
  CellData2->SetComponent(0,2, -3.4);
  Grid->GetCellData()->AddArray(CellData2);

  //// FieldData ////
  auto FieldData =
    vtkSmartPointer<vtkFloatArray>::New();
  FieldData->SetName("Time (s)");
  FieldData->SetNumberOfTuples(1);
  FieldData->SetComponent(0,0, 3.14);
  Grid->GetFieldData()->AddArray(FieldData);

  //// Writer ////
  auto Writer =
    vtkSmartPointer<vtkXMLUnstructuredGridWriter>
    ::New();
  Writer->SetFileName("sample-e.vtu");
  Writer->SetInputData(Grid);
  //Writer->SetCompressorTypeToNone();
  //Writer->SetDataModeToAscii();
  Writer->SetCompressorTypeToLZMA();
  //Writer->SetCompressionLevel(5);

  Writer->Write();

  return 0;
}
