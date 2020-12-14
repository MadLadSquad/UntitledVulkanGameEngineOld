cmake_minimum_required(VERSION 3.17)
project(UVKGame)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
#find_package(GLEW REQUIRED)

add_subdirectory(Engine/ThirdParty/glm/)
add_subdirectory(Engine/ThirdParty/glfw/)
add_subdirectory(Engine/ThirdParty/openal/)
add_subdirectory(Engine/ThirdParty/yaml/)

link_directories(Engine/ThirdParty/glew/lib)

include_directories(Engine/ThirdParty/EnTT)
include_directories(Engine/Core/)
include_directories(Engine/ThirdParty/glm)
include_directories(Engine/ThirdParty/)
include_directories(Engine/ThirdParty/glew/include)
include_directories(Engine/ThirdParty/yaml/include)
include_directories(Engine/ThirdParty/yaml/include/yaml-cpp)

add_executable(UVKGame main.cpp Engine/Audio/AudioRenderer.cpp Engine/Audio/AudioRenderer.hpp Engine/Core/Core.hpp Engine/ThirdParty/EnTT/entt.hpp Engine/Core/Assets/Asset.hpp Engine/GameFramework/Actors/AActor.hpp Engine/GameFramework/Actors/APawn.hpp Engine/GameFramework/GameplayClasses/GameMode.hpp Engine/GameFramework/GameplayClasses/GameInstance.hpp Engine/Engine.hpp Engine/GameFramework/Components/Components.hpp Engine/GameFramework/GameplayClasses/Level/Level.hpp Engine/GameFramework/GameplayClasses/GameState.hpp Engine/GameFramework/GameplayClasses/PlayerController.hpp Engine/GameFramework/GameplayClasses/PlayerState.hpp Engine/GameFramework/GameplayClasses/Level/Level.cpp Engine/Renderer/OpenGL/GLRenderer.cpp Engine/Renderer/OpenGL/GLRenderer.hpp)
set_target_properties(UVKGame PROPERTIES LINKER_LANGUAGE CXX)

if (WIN32)
    target_link_libraries(UVKGame glfw opengl32 OpenAL32 GLEW yaml-cpp)
else()
    target_link_libraries(UVKGame glfw OpenGL GLEW OpenAL yaml-cpp)
endif ()
