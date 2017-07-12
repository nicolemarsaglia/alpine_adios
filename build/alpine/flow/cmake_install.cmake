# Install script for directory: /lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/flow

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
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libalpine_flow.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libalpine_flow.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libalpine_flow.so"
         RPATH "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/install/lib:/lustre/atlas/scratch/nic8504/csc094/rhea/conduit/install/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/ccs/home/nic8504/rhea/alpine/build/alpine/flow/libalpine_flow.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libalpine_flow.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libalpine_flow.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libalpine_flow.so"
         OLD_RPATH "/lustre/atlas/scratch/nic8504/csc094/rhea/conduit/install/lib:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
         NEW_RPATH "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/install/lib:/lustre/atlas/scratch/nic8504/csc094/rhea/conduit/install/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libalpine_flow.so")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/alpine" TYPE FILE FILES
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/flow/alpine_flow_data.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/flow/alpine_flow_registry.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/flow/alpine_flow_filter.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/flow/alpine_flow_filters.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/flow/alpine_flow_graph.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/flow/alpine_flow_workspace.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/flow/filters/alpine_flow_registry_filters.hpp"
    "/lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src/alpine/flow/alpine_flow.hpp"
    )
endif()

