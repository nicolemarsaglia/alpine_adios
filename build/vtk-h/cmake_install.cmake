# Install script for directory: /lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/vtk-h

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvtkh.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvtkh.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvtkh.so"
         RPATH "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/install/lib:/lustre/atlas/scratch/nic8504/csc094/rhea/vtkm/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/ccs/home/nic8504/rhea/alpine/build/vtk-h/libvtkh.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvtkh.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvtkh.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvtkh.so"
         OLD_RPATH "/lustre/atlas/scratch/nic8504/csc094/rhea/vtkm/lib:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
         NEW_RPATH "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/install/lib:/lustre/atlas/scratch/nic8504/csc094/rhea/vtkm/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvtkh.so")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvtkh_par.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvtkh_par.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvtkh_par.so"
         RPATH "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/install/lib:/lustre/atlas/scratch/nic8504/csc094/rhea/conduit/install/lib:/lustre/atlas/scratch/nic8504/csc094/rhea/vtkm/lib:/sw/rhea/openmpi/2.0.1/rhel6.6_gcc6.2.0/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/ccs/home/nic8504/rhea/alpine/build/vtk-h/libvtkh_par.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvtkh_par.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvtkh_par.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvtkh_par.so"
         OLD_RPATH "/lustre/atlas/scratch/nic8504/csc094/rhea/conduit/install/lib:/lustre/atlas/scratch/nic8504/csc094/rhea/vtkm/lib:/sw/rhea/openmpi/2.0.1/rhel6.6_gcc6.2.0/lib:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
         NEW_RPATH "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/install/lib:/lustre/atlas/scratch/nic8504/csc094/rhea/conduit/install/lib:/lustre/atlas/scratch/nic8504/csc094/rhea/vtkm/lib:/sw/rhea/openmpi/2.0.1/rhel6.6_gcc6.2.0/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvtkh_par.so")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtkh" TYPE FILE FILES
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/vtk-h/vtkh.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/vtk-h/vtkh_data_set.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/vtk-h/vtkh_error.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/vtk-h/vtkh_filter.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/vtk-h/utils/vtkm_dataset_info.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/vtk-h/utils/vtkh_png_encoder.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/vtk-h/rendering/compositing/vtkh_compositor.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/vtk-h/rendering/vtkh_image.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/vtk-h/rendering/vtkh_renderer.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/vtk-h/rendering/vtkh_renderer_ray_tracer.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/vtk-h/rendering/vtkh_renderer_volume.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/vtk-h/vtkh_marching_cubes.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/vtk-h/vtkh_clip.hpp"
    )
endif()

