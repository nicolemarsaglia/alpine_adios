# CMake generated Testfile for 
# Source directory: /lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/tests/vtk-h
# Build directory: /ccs/home/nic8504/rhea/alpine/build/tests/vtk-h
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(t_vtk-h_smoke "t_vtk-h_smoke")
add_test(t_vtk-h_dataset "t_vtk-h_dataset")
add_test(t_vtk-h_clip "t_vtk-h_clip")
add_test(t_vtk-h_marching_cubes "t_vtk-h_marching_cubes")
add_test(t_vtk-h_raytracer "t_vtk-h_raytracer")
add_test(t_vtk-h_volume_renderer "t_vtk-h_volume_renderer")
add_test(t_vtk-h_smoke_par "/sw/rhea/openmpi/2.0.1/rhel6.6_gcc6.2.0/bin/mpiexec" "-np" "2" "./t_vtk-h_smoke_par")
add_test(t_vtk-h_dataset_par "/sw/rhea/openmpi/2.0.1/rhel6.6_gcc6.2.0/bin/mpiexec" "-np" "2" "./t_vtk-h_dataset_par")
add_test(t_vtk-h_marching_cubes_par "/sw/rhea/openmpi/2.0.1/rhel6.6_gcc6.2.0/bin/mpiexec" "-np" "2" "./t_vtk-h_marching_cubes_par")
add_test(t_vtk-h_raytracer_par "/sw/rhea/openmpi/2.0.1/rhel6.6_gcc6.2.0/bin/mpiexec" "-np" "2" "./t_vtk-h_raytracer_par")
add_test(t_vtk-h_volume_renderer_par "/sw/rhea/openmpi/2.0.1/rhel6.6_gcc6.2.0/bin/mpiexec" "-np" "2" "./t_vtk-h_volume_renderer_par")
