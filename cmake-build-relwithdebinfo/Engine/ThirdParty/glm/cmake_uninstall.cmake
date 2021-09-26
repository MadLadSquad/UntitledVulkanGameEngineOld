if(NOT EXISTS "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/cmake-build-relwithdebinfo/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: /home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/cmake-build-relwithdebinfo/install_manifest.txt")
endif()

file(READ "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/cmake-build-relwithdebinfo/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach(file ${files})
  message(STATUS "Uninstalling $ENV{DESTDIR}${file}")
  if(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
    exec_program(
      "/opt/clion/bin/cmake/linux/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
      OUTPUT_VARIABLE rm_out
      RETURN_VALUE rm_retval
      )
    if(NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing $ENV{DESTDIR}${file}")
    endif()
  else(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
    message(STATUS "File $ENV{DESTDIR}${file} does not exist.")
  endif()
endforeach()
