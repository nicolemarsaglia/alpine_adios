# Install script for directory: /lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine

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
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libalpine.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libalpine.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libalpine.so"
         RPATH "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/install/lib:/lustre/atlas/scratch/nic8504/csc094/rhea/conduit/install/lib:/lustre/atlas/scratch/nic8504/csc094/rhea/vtkm/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/ccs/home/nic8504/rhea/alpine/build/alpine/libalpine.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libalpine.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libalpine.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libalpine.so"
         OLD_RPATH "/lustre/atlas/scratch/nic8504/csc094/rhea/conduit/install/lib:/ccs/home/nic8504/rhea/alpine/build/alpine/flow:/lustre/atlas/scratch/nic8504/csc094/rhea/vtkm/lib:::::::::::::"
         NEW_RPATH "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/install/lib:/lustre/atlas/scratch/nic8504/csc094/rhea/conduit/install/lib:/lustre/atlas/scratch/nic8504/csc094/rhea/vtkm/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libalpine.so")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libalpine_par.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libalpine_par.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libalpine_par.so"
         RPATH "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/install/lib:/lustre/atlas/scratch/nic8504/csc094/rhea/conduit/install/lib:/lustre/atlas/scratch/nic8504/csc094/rhea/vtkm/lib:/sw/rhea/openmpi/2.0.1/rhel6.6_gcc6.2.0/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/ccs/home/nic8504/rhea/alpine/build/alpine/libalpine_par.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libalpine_par.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libalpine_par.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libalpine_par.so"
         OLD_RPATH "/lustre/atlas/scratch/nic8504/csc094/rhea/conduit/install/lib:/ccs/home/nic8504/rhea/alpine/build/alpine/flow:/lustre/atlas/scratch/nic8504/csc094/rhea/vtkm/lib:/sw/rhea/openmpi/2.0.1/rhel6.6_gcc6.2.0/lib:::::::::::::"
         NEW_RPATH "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/install/lib:/lustre/atlas/scratch/nic8504/csc094/rhea/conduit/install/lib:/lustre/atlas/scratch/nic8504/csc094/rhea/vtkm/lib:/sw/rhea/openmpi/2.0.1/rhel6.6_gcc6.2.0/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libalpine_par.so")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/alpine" TYPE FILE FILES
    "/ccs/home/nic8504/rhea/alpine/build/alpine/alpine_config.h"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/alpine_exports.h"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/alpine.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/c/alpine.h"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/alpine_pipeline.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/pipelines/alpine_empty_pipeline.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/pipelines/alpine_flow_pipeline.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/pipelines/flow_filters/alpine_flow_pipeline_filters.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/pipelines/flow_filters/alpine_flow_pipeline_relay_filters.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/pipelines/flow_filters/alpine_flow_pipeline_blueprint_filters.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/utils/alpine_logging.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/utils/alpine_file_system.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/utils/alpine_block_timer.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/utils/alpine_png_encoder.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/utils/alpine_web_interface.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/pipelines/alpine_vtkm_pipeline.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/pipelines/alpine_vtkm_renderer.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/pipelines/alpine_vtkm_renderer.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/pipelines/alpine_blueprint_hdf5_pipeline.hpp"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/ccs/home/nic8504/rhea/alpine/build/alpine/flow/cmake_install.cmake")
  include("/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/utils/lodepng/cmake_install.cmake")

endif()

