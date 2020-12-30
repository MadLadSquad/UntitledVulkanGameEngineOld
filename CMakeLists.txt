cmake_minimum_required(VERSION 3.17)
project(UVKGame)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
#find_package(OpenAL REQUIRED)
#find_package(GLEW REQUIRED)

add_subdirectory(Engine/ThirdParty/glm/)
add_subdirectory(Engine/ThirdParty/glfw/)
if(MINGW)
else()
    add_subdirectory(Engine/ThirdParty/openal/)
endif()
add_subdirectory(Engine/ThirdParty/yaml/)
add_subdirectory(Engine/ThirdParty/entt/)

link_directories(Engine/ThirdParty/glew/lib)

include_directories(Engine/ThirdParty/entt/src/entt)
include_directories(Engine/Core/)
include_directories(Engine/ThirdParty/glm)
include_directories(Engine/ThirdParty/)
include_directories(Engine/ThirdParty/glew/include)
include_directories(Engine/ThirdParty/yaml/include)
include_directories(Engine/ThirdParty/yaml/include/yaml-cpp)
include_directories(Engine/ThirdParty/logger/)


add_executable(UVKGame main.cpp Engine/Audio/AudioRenderer.cpp Engine/Audio/AudioRenderer.hpp Engine/Core/Core.hpp Engine/Core/Assets/Asset.hpp Engine/GameFramework/Actors/APawn.hpp Engine/GameFramework/GameplayClasses/GameMode.hpp Engine/GameFramework/GameplayClasses/GameInstance.hpp Engine/Engine.hpp Engine/GameFramework/Components/Components.hpp Engine/GameFramework/GameplayClasses/Level/Level.hpp Engine/GameFramework/GameplayClasses/GameState.hpp Engine/GameFramework/GameplayClasses/PlayerController.hpp Engine/GameFramework/GameplayClasses/PlayerState.hpp Engine/GameFramework/GameplayClasses/Level/Level.cpp Engine/Renderer/OpenGL/GLRenderer.cpp Engine/Renderer/OpenGL/GLRenderer.hpp Engine/ThirdParty/logger/UVKLog.h main.cpp)
set_target_properties(UVKGame PROPERTIES LINKER_LANGUAGE CXX)

if (WIN32)
    #target_link_libraries(UVKGame pthread glfw opengl32 OpenAL glew32 yaml-cpp)
    if (MINGW)
	    target_link_libraries(UVKGame pthread glfw opengl32 glew32 yaml-cpp)
    else()
        target_link_libraries(UVKGame pthread glfw OpenAL opengl32 glew32 yaml-cpp)
    endif()
else()
    target_link_libraries(UVKGame glfw OpenGL GLEW OpenAL yaml-cpp)
endif ()
