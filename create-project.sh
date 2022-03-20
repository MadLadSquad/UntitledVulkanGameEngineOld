#!/bin/bash
if [ "$1" != "" ]; then
  prjname="$1"
else
  read -rp "Enter Your Application Name: " prjname # read the project name
fi

wdir=$(pwd) # get the working dir since we are going to be returning there
cd "C:/Program Files (x86)/Microsoft Visual Studio/" || (echo "cannot enter" && exit) # Go to the Visual Studio dir
VSVer=$(find "2022" -maxdepth 0 2> /dev/null) || VSVer=$(find "2019" -maxdepth 0 2> /dev/null) || VSVer=$(find "2017" -maxdepth 0 2> /dev/null) || echo " " > /dev/null
cd "${wdir}" || echo " " > /dev/null # Return to the old directory
if [ "$VSVer" == "2022" ]; then VSShortVer="17"
elif [ "$VSVer" == "2019" ]; then VSShortVer="16"
elif [ "$VSVer" == "2017" ]; then VSShortVer="15"
else VSShortVer="1"
fi

prjname=${prjname/ /} # Remove any spaces if the name contains them
cpus=$(grep -c processor /proc/cpuinfo) ## get the cpu threads for maximum performance when compiling
echo -e "\x1B[32mCopiling with ${cpus} compute jobs!\033[0m"

cd Projects/ || exit
mkdir "${prjname}" || exit
cd "${prjname}" || exit

# Create folders and files to be used as configs
mkdir Source || exit
mkdir Generated || exit
mkdir WrapperSource || exit
mkdir build || exit
mkdir Exported || exit

# Copy the config template we want
cp ../../Config/ . -r
cp ../../Content/ . -r

cd Config/ || exit
touch Engine/GameKeybinds.yaml
echo "\
bindings:
  - key: EmptyAction
    val: 65
" > Engine/GameKeybinds.yaml
cd .. || exit
echo " "
echo -e "\x1B[32m--------------------------------------------------------------------------------\033[0m"
echo -e "\x1B[32mCreating project file with default settings ...\033[0m"
echo -e "\x1B[32m--------------------------------------------------------------------------------\033[0m"
echo " "

# We create a project file which will be used to configure our generated files
touch uvproj.yaml && echo "\
name: \"${prjname}\"
startup-level: \"lvl\"
version: 1.0.0
engine-version: 1.0.0" > uvproj.yaml

echo " "
echo -e "\x1B[32m--------------------------------------------------------------------------------\033[0m"
echo -e "\x1B[32mCreating symbolic links and generating files ...\033[0m"
echo -e "\x1B[32m--------------------------------------------------------------------------------\033[0m"
echo " "

# We symlink the Engine source folder so that the cmake can work
ln -rs "../../Engine/" Engine || mklink.exe /D Engine ../../Engine/
ln -rs "../../UVKBuildTool/" UVKBuildTool || mklink.exe /D UVKBuildTool ../../UVKBuildTool/
ln -rs "../../UVKShaderCompiler/" UVKShaderCompiler || mklink.exe /D UVKShaderCompiler ../../UVKShaderCompiler/
cp ../../export.sh .

cd ../../UVKBuildTool/build || exit
./UVKBuildTool.exe --install "../../Projects/${prjname}" || ./UVKBuildTool --install "../../Projects/${prjname}" || exit
cd ../../UVKShaderCompiler/build || exit
./UVKShaderCompiler.exe --compile "../../Projects/${prjname}" || ./UVKShaderCompiler --compile "../../Projects/${prjname}" || exit
cd "../../Projects/${prjname}" || exit
cd build || exit

echo " "
echo -e "\x1B[32m--------------------------------------------------------------------------------\033[0m"
echo -e "\x1B[32mCompiling ${prjname} ...\033[0m"
echo -e "\x1B[32m--------------------------------------------------------------------------------\033[0m"
echo " "

if [ "$2" == "ci" ]; then
  cmake .. || exit
else
  cmake .. -G "Visual Studio ${VSShortVer} ${VSVer}" || cmake .. -G "Unix Makefiles" || exit # Generate build files for the project
fi

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
