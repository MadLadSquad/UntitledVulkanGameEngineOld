# Install script for directory: /home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE STATIC_LIBRARY FILES "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/cmake-build-relwithdebinfo/Engine/ThirdParty/assimp/lib/libassimp.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/anim.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/aabb.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/ai_assert.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/camera.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/color4.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/color4.inl"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/cmake-build-relwithdebinfo/Engine/ThirdParty/assimp/code/../include/assimp/config.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/ColladaMetaData.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/commonMetaData.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/defs.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/Defines.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/cfileio.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/light.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/material.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/material.inl"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/matrix3x3.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/matrix3x3.inl"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/matrix4x4.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/matrix4x4.inl"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/mesh.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/pbrmaterial.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/postprocess.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/quaternion.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/quaternion.inl"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/scene.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/metadata.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/texture.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/types.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/vector2.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/vector2.inl"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/vector3.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/vector3.inl"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/version.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/cimport.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/importerdesc.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/Importer.hpp"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/DefaultLogger.hpp"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/ProgressHandler.hpp"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/IOStream.hpp"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/IOSystem.hpp"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/Logger.hpp"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/LogStream.hpp"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/NullLogger.hpp"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/cexport.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/Exporter.hpp"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/DefaultIOStream.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/DefaultIOSystem.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/ZipArchiveIOSystem.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/SceneCombiner.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/fast_atof.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/qnan.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/BaseImporter.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/Hash.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/MemoryIOWrapper.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/ParsingUtils.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/StreamReader.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/StreamWriter.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/StringComparison.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/StringUtils.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/SGSpatialSort.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/GenericProperty.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/SpatialSort.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/SkeletonMeshBuilder.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/SmallVector.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/SmoothingGroups.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/SmoothingGroups.inl"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/StandardShapes.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/RemoveComments.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/Subdivision.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/Vertex.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/LineSplitter.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/TinyFormatter.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/Profiler.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/LogAux.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/Bitmap.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/XMLTools.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/IOStreamBuffer.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/CreateAnimMesh.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/XmlParser.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/BlobIOSystem.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/MathFunctions.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/Exceptional.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/ByteSwapper.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/Compiler/poppack1.h"
    "/home/i-use-gentoo-btw/Documents/UntitledVulkanGameEngine/Engine/ThirdParty/assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

