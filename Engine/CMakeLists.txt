cmake_minimum_required(VERSION 3.17)
project(Engine)

# Engine is set to C++17 because of the EnTT header file
set(CMAKE_CXX_STANDARD 17)


# Adds GLFW
add_subdirectory(ThirdParty/GLFW)
include_directories(ThirdParty/GLFW/include)
target_link_libraries(glfw ${GLFW_LIBRARIES})

# Adds OpenAL
#target_link_libraries()


# Adds all engine source code
add_library(Engine SHARED Audio/AudioCore.hpp Audio/AudioRenderer/AudioRenderer.cpp
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
