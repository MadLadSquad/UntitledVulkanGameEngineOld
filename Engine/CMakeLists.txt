cmake_minimum_required(VERSION 3.17)
project(UVKEngine)

# Engine is set to C++17 because of the EnTT header file
set(CMAKE_CXX_STANDARD 17)

# Engine needs OpenGL for obvious reasons
find_package(OpenGL REQUIRED)
#find_package(OpenAL REQUIRED)

# Adds all engine source code
add_library(UVKEngine SHARED Audio/AudioCore.hpp Audio/AudioRenderer/AudioRenderer.cpp
Audio/AudioRenderer/AudioRenderer.h Core/Core.hpp
Core/API/Defines.h Core/API/Entity.hpp Core/API/Types.hpp Core/GameFramework/Components.hpp Core/GameFramework/NameComponent.h
Core/GameFramework/Actors/Actor.cpp Core/GameFramework/Actors/Actor.hpp Core/GameFramework/Actors/Pawn.cpp Core/GameFramework/Actors/Pawn.hpp
Core/GameFramework/GameFoundation/GameInstance.cpp Core/GameFramework/GameFoundation/GameInstance.hpp
Core/GameFramework/GameFoundation/GameState.cpp Core/GameFramework/GameFoundation/GameState.hpp
Core/GameFramework/GameFoundation/GameMode.cpp Core/GameFramework/GameFoundation/GameMode.hpp
Core/GameFramework/GameFoundation/PlayerState.cpp Core/GameFramework/GameFoundation/PlayerState.hpp
Core/GameFramework/GameFoundation/PlayerController.cpp Core/GameFramework/GameFoundation/PlayerController.hpp
Core/GameFramework/GameFoundation/Level.cpp Core/GameFramework/GameFoundation/Level.hpp
Editor/DetailsPanel.hpp Editor/FileManager.hpp Editor/Statistics.hpp Renderer/RendererCore.hpp Renderer/OpenGL/GLCamera.cpp
Renderer/OpenGL/GLCamera.hpp Renderer/OpenGL/GLMesh.cpp Renderer/OpenGL/GLMesh.hpp Renderer/OpenGL/GLRenderer.cpp Renderer/OpenGL/GLRenderer.hpp
Renderer/OpenGL/GLShader.cpp Renderer/OpenGL/GLShader.hpp Renderer/OpenGL/GLCamera.hpp Renderer/OpenGL/GLCamera.cpp
Renderer/Vulkan/VkRenderer.cpp Renderer/Vulkan/VkRenderer.hpp)

# Include directories are needed because each library uses configs for different libs and they
# check the lib by checking for include
include_directories(imgui ThirdParty/imgui/)
include_directories(glew ThirdParty/GLEW/include)

# Those specific link directories are needed because the CMake goes kaboom
link_directories(glew ThirdParty/GLEW/lib)
link_directories(glfw ThirdParty/GLFW)
link_directories(openal ThirdParty/OpenAL)

# Subdirectories
add_subdirectory(ThirdParty/GLFW)
add_subdirectory(ThirdParty/OpenAL)

target_link_directories(${PROJECT_NAME} PUBLIC ThirdParty/GLFW PUBLIC ThirdParty/OpenAL PUBLIC ThirdParty/GLEW/lib)
target_link_libraries(${PROJECT_NAME} glfw openal GLEW)