#!/bin/bash
# shellcheck disable=SC2162
prjname="Game"
cpus=$(grep -c processor /proc/cpuinfo) ## get the cpu threads for maximum performance when compiling
echo -e "\x1B[32mCopiling with ${cpus} compute jobs!\033[0m"

# Create folders and files to be used as configs
mkdir Source || exit 
mkdir Generated || exit
cd Config || exit

# We create a Game Keybinds file and fill it with a random action which will later be removed by the user
touch Engine/GameKeybinds.yaml
echo "\
bindings:
  - key: NewAction0
    val: 65
" > Engine/EditorKeybinds.yaml
cd .. || exit

echo -e "\x1B[32mCreating project file with default settings ...\033[0m"

# We create a project file which will be used to configure our generated files
touch uvproj.yaml && echo "\
name: \"${prjname}\"
startup-level: \"lvl\"
version: 1.0.0
engine-version: 1.0.0" > uvproj.yaml

echo -e "\x1B[32mCompiling build tool and generating files ...\033[0m"
echo -e "\x1B[32m--------------------------------------------------------------------------------\033[0m"
echo " "

cd UVKBuildTool/ || exit
mkdir build || exit # Will store our compiled binary
cd build || exit 
cmake .. || exit # Generate the UVKBuildTool project files

# Try to run MSBuild first, if it fails we are either on a non-Windows system or the user doesn't have Visual Studio installed
MSBuild.exe UVKBuildTool.sln -property:Configuration=Release -property:Platform=x64 -property:maxCpuCount=${cpus} || make -j "${cpus}" || exit

# If on Windows copy the UVKBuildTool executable from the Release folder, this will absolutely fail on any non-Windows system in which
# case we will just echo an empty message
cp Release/UVKBuildTool.exe . || echo " " || exit

# Windows uses .exe files so the first instruction will fail on any non-Windows system
./UVKBuildTool.exe --install || ./UVKBuildTool --install || exit
cd ../../ || exit
mkdir build || exit # Build folder used for compilation
mkdir Exported  || exit # Exported folder used for storing production ready games you exported
cd build || exit

echo " "
echo -e "\x1B[32m--------------------------------------------------------------------------------\033[0m"
echo -e "\x1B[32mCompiling ${prjname} ...\033[0m"
echo -e "\x1B[32m--------------------------------------------------------------------------------\033[0m"
echo " "

cmake .. || exit # Generate build files for the project

# Try to run MSBuild first, if it fails we are either on a non-windows system or the user doesn't have Visual Studio installed
MSBuild.exe "${prjname}".sln -property:Configuration=Release -property:Platform=x64 -property:maxCpuCount=${cpus} || make -j "${cpus}" || exit

echo " "
echo -e "\x1B[32m--------------------------------------------------------------------------------\033[0m"
echo -e "\x1B[32mCopying required libraries ...\033[0m"

cp Engine/ThirdParty/openal/Release/OpenAL32.dll . || echo " " || exit # Copy the OpenAL32.dll file (needed for Windows)
cp OpenAL32.dll Release/ || echo " " || exit # Copy the OpenAL32.dll file to the Release directory since this is where we build
cd ../Engine/ThirdParty/vulkan/ || exit # Change into the Vulkan directory which for some reason contains the needeed libraries for Windows
cp glew32.dll ../../../build/ || exit # Copy the glew32.dll file (responsible for OpenGL extension loading)
cp sndfile.dll ../../../build/ || exit # Copy the sndfile.dll file (responsible for loading and operating with sound files)
cp vulkan-1.dll ../../../build/ || exit # Copy the vulkan-1.dll file (responsible for Vulkan, Vulkan extension loading and Validation)
cd ../../../build/ || exit # Go back into the build directory 
cp glew32.dll sndfile.dll vulkan-1.dll Release/ || echo " " || exit # Finally copy the libraries to the Release folder because that is where Visual Studio builds

echo -e "\x1B[32mEngine and project successfully installed! \033[0m" # Print a success message in green