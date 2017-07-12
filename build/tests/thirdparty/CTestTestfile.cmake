# CMake generated Testfile for 
# Source directory: /lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/tests/thirdparty
# Build directory: /ccs/home/nic8504/rhea/alpine/build/tests/thirdparty
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(t_gtest_smoke "t_gtest_smoke")
add_test(t_vtkm_smoke "t_vtkm_smoke")
add_test(t_mpi_smoke "/sw/rhea/openmpi/2.0.1/rhel6.6_gcc6.2.0/bin/mpiexec" "-np" "2" "./t_mpi_smoke")
add_test(t_diy_smoke "/sw/rhea/openmpi/2.0.1/rhel6.6_gcc6.2.0/bin/mpiexec" "-np" "2" "./t_diy_smoke")
