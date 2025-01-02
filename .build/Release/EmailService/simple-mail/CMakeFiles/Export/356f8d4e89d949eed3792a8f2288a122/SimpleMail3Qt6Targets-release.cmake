#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SimpleMail::Core" for configuration "Release"
set_property(TARGET SimpleMail::Core APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SimpleMail::Core PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/libSimpleMail3Qt6.dll.a"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/libSimpleMail3Qt6.dll"
  )

list(APPEND _cmake_import_check_targets SimpleMail::Core )
list(APPEND _cmake_import_check_files_for_SimpleMail::Core "${_IMPORT_PREFIX}/lib/libSimpleMail3Qt6.dll.a" "${_IMPORT_PREFIX}/bin/libSimpleMail3Qt6.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
