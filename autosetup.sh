#!/bin/bash
# shellcheck disable=SC2162
read -p "Enter Your Application Name: " prjname # read the project name
while true; do
    read -p "Do you want to download offline documentation Y(Yes)/N(No): " yn
    case $yn in
        [Yy]* ) git clone https://github.com/MadLadSquad/UntitledVulkanGameEngine.wiki.git docs/; break;;
        [Nn]* ) break;;
        * ) echo "Please answer with Y(Yes) or N(No)!";;
    esac
done

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
  - key: EmptyAction
    val: 65
" > Engine/GameKeybinds.yaml
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
cmake .. -G "Visual Studio 16 2019" || cmake .. -G "Unix Makefiles" || exit # Generate the UVKBuildTool project files

# Try to run MSBuild first, if it fails we are either on a non-Windows system or the user doesn't have Visual Studio installed
MSBuild.exe UVKBuildTool.sln -property:Configuration=Release -property:Platform=x64 -property:maxCpuCount="${cpus}" || make -j "${cpus}" || exit

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

cmake .. -G "Visual Studio 16 2019" || cmake .. -G "Unix Makefiles" || exit # Generate build files for the project

# Try to run MSBuild first, if it fails we are either on a non-windows system or the user doesn't have Visual Studio installed
MSBuild.exe "${prjname}".sln -property:Configuration=Release -property:Platform=x64 -property:maxCpuCount="${cpus}" || make -j "${cpus}" || exit

echo " "
echo -e "\x1B[32m--------------------------------------------------------------------------------\033[0m"
echo -e "\x1B[32mCopying required libraries ...\033[0m"
echo -e "\x1B[32m--------------------------------------------------------------------------------\033[0m"
echo " "

(echo -e "\x1B[32mOpenAL32.dll required for this system!\033[0m" && cp Engine/ThirdParty/openal/Release/OpenAL32.dll .) || echo -e "\x1B[32mOpenAL32.dll not required for this system!\033[0m"
(cp OpenAL32.dll Release/ && echo -e "\x1B[32mSuccessfully installed OpenAL!\033[0m") || echo -e "\x1B[32mNo need to install OpenAL32!\033[0m"
cd ../Engine/ThirdParty/vulkan/ || exit # Change into the Vulkan directory which for some reason contains the needed libraries for Windows
(cp sndfile.dll ../../../build/ && echo -e "\x1B[32msndfile.dll required for this system!\033[0m") || echo -e "\x1B[32msndfile.dll not required for this system!\033[0m" # Copy the sndfile.dll file (responsible for loading and operating with sound files)
cd ../../../build/ || exit # Go back into the build directory
(cp sndfile.dll Release/ && echo -e "\x1B[32mInstalled sndfile.dll!\033[0m") || echo -e "\x1B[32mNo need to install sndfile.dll!\033[0m" || exit # Finally copy the libraries to the Release folder because that is where Visual Studio builds
cp Release/"${prjname}".exe . || echo -e "\x1B[32mProject Installed!\033[0m"

echo -e "\x1B[32mEngine and project successfully installed! \033[0m" # Print a success message in green
