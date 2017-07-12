# CMake generated Testfile for 
# Source directory: /lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/tests/alpine
# Build directory: /ccs/home/nic8504/rhea/alpine/build/tests/alpine
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(t_alpine_smoke "t_alpine_smoke")
add_test(t_alpine_empty_pipeline "t_alpine_empty_pipeline")
add_test(t_alpine_render_2d "t_alpine_render_2d")
add_test(t_alpine_render_3d "t_alpine_render_3d")
add_test(t_alpine_web "t_alpine_web")
add_test(t_alpine_save_blueprint_hdf5 "t_alpine_save_blueprint_hdf5")
add_test(t_alpine_flow_data "t_alpine_flow_data")
add_test(t_alpine_flow_registry "t_alpine_flow_registry")
add_test(t_alpine_flow_workspace "t_alpine_flow_workspace")
add_test(t_alpine_flow_pipeline "t_alpine_flow_pipeline")
add_test(t_alpine_mpi_empty_pipeline "/sw/rhea/openmpi/2.0.1/rhel6.6_gcc6.2.0/bin/mpiexec" "-np" "2" "./t_alpine_mpi_empty_pipeline")
add_test(t_alpine_mpi_render_2d "/sw/rhea/openmpi/2.0.1/rhel6.6_gcc6.2.0/bin/mpiexec" "-np" "2" "./t_alpine_mpi_render_2d")
add_test(t_alpine_mpi_render_3d "/sw/rhea/openmpi/2.0.1/rhel6.6_gcc6.2.0/bin/mpiexec" "-np" "2" "./t_alpine_mpi_render_3d")
add_test(t_alpine_mpi_save_blueprint_hdf5 "/sw/rhea/openmpi/2.0.1/rhel6.6_gcc6.2.0/bin/mpiexec" "-np" "2" "./t_alpine_mpi_save_blueprint_hdf5")
