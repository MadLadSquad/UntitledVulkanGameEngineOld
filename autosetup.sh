#!/bin/bash
while true; do
    echo -e "Before we begin, if you're on Windows, check that your Visual Studio instance is installed under \"C:/Program Files (x86)/Microsoft Visual Studio/\"!"
    read -rp "Start installation? Y(Yes)/N(No): " yn
    case $yn in
        [Yy]* ) break;;
        [Nn]* ) exit;;
        * ) echo "Please answer with Y(Yes) or N(No)!";;
    esac
done

read -rp "Enter Your Application Name: " prjname # read the project name
while true; do
    read -rp "Do you want to download offline documentation Y(Yes)/N(No): " yn
    case $yn in
        [Yy]* ) git clone https://github.com/MadLadSquad/UntitledVulkanGameEngine.wiki.git docs/; break;;
        [Nn]* ) break;;
        * ) echo "Please answer with Y(Yes) or N(No)!";;
    esac
done

prjname=${prjname/ /} # Remove any spaces if the name contains them

#if MSBuild.exe -help; then
    # Add VS compiler to path in VS
    wdir=$(pwd) # get the working dir since we are going to be returning there
    cd "C:/Program Files (x86)/Microsoft Visual Studio/" || (echo "cannot enter" && exit) # Go to the Visual Studio dir
    VSVer=$(find "2022" -maxdepth 0 2> /dev/null) || VSVer=$(find "2019" -maxdepth 0 2> /dev/null) || VSVer=$(find "2017" -maxdepth 0 2> /dev/null) || echo " " > /dev/null
    cd "${VSVer}" || echo " " > /dev/null # Go to the Visual Studio Version dir
    VSType=$(find "Community" -maxdepth 0 2> /dev/null) || VSType=$(find "Enterprise" -maxdepth 0 2> /dev/null) || VSType=$(find "Professional" -maxdepth 0 2> /dev/null) || echo " " > /dev/null # Set the VS type to one of the 3 types
    cd "${wdir}" || echo " " > /dev/null # Return to the old directory
    setx PATH "C:/Program Files (x86)/Microsoft Visual Studio/${VSVer}/${VSType}/MSBuild/Current/Bin/amd64/;%PATH%" || echo " " > /dev/null # Set the path

    if [ "$VSVer" == "2022" ]; then VSShortVer="17"
    elif [ "$VSVer" == "2019" ]; then VSShortVer="16"
    elif [ "$VSVer" == "2017" ]; then VSShortVer="15"
    else VSShortVer="1"
    fi
#fi

cpus=$(grep -c processor /proc/cpuinfo) ## get the cpu threads for maximum performance when compiling
echo -e "\x1B[32mCopiling with ${cpus} compute jobs!\033[0m"

# Create folders and files to be used as configs
mkdir Source || exit
mkdir Generated || exit
mkdir WrapperSource || exit
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
cmake .. -G "Visual Studio ${VSShortVer} ${VSVer}" || cmake .. -G "Unix Makefiles" || exit # Generate the UVKBuildTool project files

# Try to run MSBuild first, if it fails we are either on a non-Windows system or the user doesn't have Visual Studio installed
MSBuild.exe UVKBuildToolLib.sln -property:Configuration=Release -property:Platform=x64 -property:maxCpuCount="${cpus}" || make -j "${cpus}" || exit

# If on Windows copy the UVKBuildTool executable from the Release folder, this will absolutely fail on any non-Windows system in which
# case we will just echo an empty message
cp Release/UVKBuildTool.exe . || echo " " || exit
cp Release/UVKBuildToolLib.dll . || cp Release/libUVKBuildToolLib.dll . || echo " "

# Windows uses .exe files so the first instruction will fail on any non-Windows system
./UVKBuildTool.exe --install || ./UVKBuildTool --install || exit
cd ../../ || exit
mkdir build || exit # Build folder used for compilation
mkdir Exported  || exit # Exported folder used for storing production ready games you exported

echo " "
echo -e "\x1B[32m--------------------------------------------------------------------------------\033[0m"
echo -e "\x1b[32mCompiling the ShaderCompiler ...\x1b[0m"
echo -e "\x1b[32m--------------------------------------------------------------------------------\x1b[0m"
echo " "

cd UVKShaderCompiler/ || exit
cd ThirdParty/shaderc/utils/ || exit
./git-sync-deps
cd ../../../ || exit
mkdir build
cd build || exit
cmake .. -G "Visual Studio ${VSShortVer} ${VSVer}" || cmake .. -G "Unix Makefiles" || exit

# Compiler the Shader Compiler
MSBuild.exe UVKShaderCompilerLib.sln -property:Configuration=Release -property:Platform=x64 -property:maxCpuCount="${cpus}" || make -j "${cpus}" || exit
cp Release/UVKShaderCompiler.exe . || echo " " || exit
cp Release/UVKShaderCompilerLib.dll . || cp Release/libUVKShaderCompilerLib.dll . || echo " "
cd ../../

cd build || exit

echo " "
echo -e "\x1B[32m--------------------------------------------------------------------------------\033[0m"
echo -e "\x1B[32mCompiling ${prjname} ...\033[0m"
echo -e "\x1B[32m--------------------------------------------------------------------------------\033[0m"
echo " "

cmake .. -G "Visual Studio ${VSShortVer} ${VSVer}" || cmake .. -G "Unix Makefiles" || exit # Generate build files for the project

# Try to run MSBuild first, if it fails we are either on a non-windows system or the user doesn't have Visual Studio installed
MSBuild.exe "${prjname}".sln -property:Configuration=Release -property:Platform=x64 -property:maxCpuCount="${cpus}" || make -j "${cpus}" || exit

echo " "
echo -e "\x1B[32m--------------------------------------------------------------------------------\033[0m"
echo -e "\x1B[32mCopying required libraries ...\033[0m"
echo -e "\x1B[32m--------------------------------------------------------------------------------\033[0m"
echo " "

(echo -e "\x1B[32mOpenAL32.dll required for this system!\033[0m" && cp Engine/ThirdParty/openal/Release/OpenAL32.dll . &> /dev/null) || echo -e "\x1B[32mOpenAL32.dll not required for this system!\033[0m"
(cp OpenAL32.dll Release/ &> /dev/null && echo -e "\x1B[32mSuccessfully installed OpenAL!\033[0m") || echo -e "\x1B[32mNo need to install OpenAL32!\033[0m"
cd ../Engine/ThirdParty/vulkan/ || exit # Change into the Vulkan directory which for some reason contains the needed libraries for Windows
(cp sndfile.dll ../../../build/ &> /dev/null && echo -e "\x1B[32msndfile.dll required for this system!\033[0m") || echo -e "\x1B[32msndfile.dll not required for this system!\033[0m" # Copy the sndfile.dll file (responsible for loading and operating with sound files)
cd ../../../build/ || exit # Go back into the build directory
(cp sndfile.dll Release/ &> /dev/null && echo -e "\x1B[32mInstalled sndfile.dll!\033[0m") || echo -e "\x1B[32mNo need to install sndfile.dll!\033[0m" || exit # Finally copy the libraries to the Release folder because that is where Visual Studio builds
(cp Release/"${prjname}".exe . &> /dev/null && cp Release/UntitledVulkanGameEngine.dll . &> /dev/null && cp Release/"${prjname}Modded.dll" . &> /dev/null && cp Release/"${prjname}Lib.dll" . &> /dev/null && cp Release/Modlib.dll . &> /dev/null) || echo -e "\x1B[32mProject Installed!\033[0m"

echo -e "\x1B[32mEngine and project successfully installed! \033[0m" # Print a success message in green
