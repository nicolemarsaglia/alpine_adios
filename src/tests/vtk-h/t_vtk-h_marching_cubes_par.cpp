//-----------------------------------------------------------------------------
///
/// file: t_vtk-h_dataset.cpp
///
//-----------------------------------------------------------------------------

#include "gtest/gtest.h"

#include <mpi.h>
#include <vtkh.hpp>
#include <vtkh_data_set.hpp>
#include <vtkh_marching_cubes.hpp>
#include <rendering/vtkh_renderer_ray_tracer.hpp>
#include "t_test_utils.hpp"

#include <iostream>



//----------------------------------------------------------------------------
TEST(vtkh_marching_cubes_par, vtkh_parallel_marching_cubes)
{

  MPI_Init(NULL, NULL);
  int comm_size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  vtkh::VTKH vtkh;
  vtkh.Open(MPI_COMM_WORLD);
  vtkh::vtkhDataSet data_set;
 
  const int base_size = 32;
  const int blocks_per_rank = 2;
  const int num_blocks = comm_size * blocks_per_rank; 
  
  for(int i = 0; i < blocks_per_rank; ++i)
  {
    int domain_id = rank * blocks_per_rank + i;
    data_set.AddDomain(CreateTestData(domain_id, num_blocks, base_size), domain_id);
  }
  
  vtkh::vtkhMarchingCubes marcher;
  marcher.SetInput(&data_set);
  marcher.SetField("point_data"); 

  const int num_vals = 2;
  double iso_vals [num_vals];
  iso_vals[0] = -1; // ask for something that does not exist
  iso_vals[1] = (float)base_size * (float)num_blocks * 0.5f;

  marcher.SetIsoValues(iso_vals, num_vals);
  marcher.AddMapField("point_data");
  marcher.AddMapField("cell_data");
  marcher.Update();

  vtkh::vtkhDataSet *iso_output = marcher.GetOutput();

  vtkh::vtkhRayTracer tracer;
  tracer.SetInput(iso_output);
  tracer.SetField("cell_data"); 
  tracer.Update();

  delete iso_output; 
  MPI_Finalize();
}
