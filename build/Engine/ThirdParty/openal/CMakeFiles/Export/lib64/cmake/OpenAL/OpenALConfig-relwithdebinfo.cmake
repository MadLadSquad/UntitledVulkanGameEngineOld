#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "OpenAL::OpenAL" for configuration "RelWithDebInfo"
set_property(TARGET OpenAL::OpenAL APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(OpenAL::OpenAL PROPERTIES
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib64/libopenal.so.1.21.0"
  IMPORTED_SONAME_RELWITHDEBINFO "libopenal.so.1"
  )

list(APPEND _IMPORT_CHECK_TARGETS OpenAL::OpenAL )
list(APPEND _IMPORT_CHECK_FILES_FOR_OpenAL::OpenAL "${_IMPORT_PREFIX}/lib64/libopenal.so.1.21.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
