#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "alpine_flow" for configuration ""
set_property(TARGET alpine_flow APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(alpine_flow PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libalpine_flow.so"
  IMPORTED_SONAME_NOCONFIG "libalpine_flow.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS alpine_flow )
list(APPEND _IMPORT_CHECK_FILES_FOR_alpine_flow "${_IMPORT_PREFIX}/lib/libalpine_flow.so" )

# Import target "alpine" for configuration ""
set_property(TARGET alpine APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(alpine PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libalpine.so"
  IMPORTED_SONAME_NOCONFIG "libalpine.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS alpine )
list(APPEND _IMPORT_CHECK_FILES_FOR_alpine "${_IMPORT_PREFIX}/lib/libalpine.so" )

# Import target "alpine_par" for configuration ""
set_property(TARGET alpine_par APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(alpine_par PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libalpine_par.so"
  IMPORTED_SONAME_NOCONFIG "libalpine_par.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS alpine_par )
list(APPEND _IMPORT_CHECK_FILES_FOR_alpine_par "${_IMPORT_PREFIX}/lib/libalpine_par.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
