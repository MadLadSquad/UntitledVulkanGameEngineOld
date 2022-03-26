#!/bin/bash
if [ "$1" != "" ]; then
  prjname="$1"
else
  read -rp "Enter Your Application Name: " prjname # read the project name
fi

wdir=$(pwd) # get the working dir since we are going to be returning there
cd "C:/Program Files (x86)/Microsoft Visual Studio/" 2> /dev/null || echo " "
VSVer=$(find "2022" -maxdepth 0 2> /dev/null) || VSVer=$(find "2019" -maxdepth 0 2> /dev/null) || VSVer=$(find "2017" -maxdepth 0 2> /dev/null) || echo " " > /dev/null
cd "${wdir}" 2> /dev/null || echo " " > /dev/null # Return to the old directory
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

# We symlink the Engine source folder so that 
ln -rs "../../Engine/" Engine 2> /dev/null || cp ../../Engine/ . -r
ln -rs "../../UVKBuildTool/" UVKBuildTool 2> /dev/null || cp ../../UVKBuildTool/ . -r
ln -rs "../../UVKShaderCompiler/" UVKShaderCompiler 2> /dev/null || cp ../../UVKShaderCompiler/ . -r
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

cp Engine/ThirdParty/openal/Release/OpenAL32.dll . &> /dev/null || echo " " # Copy the OpenAl dll or do nothing
cp OpenAL32.dll Release/ &> /dev/null || echo " " # Copy into release
cd ../Engine/ThirdParty/vulkan/ || exit # Go to the vulkan folder because there are a lot of libraries there
cp sndfile.dll ../../../build/ &> /dev/null || echo " " # Copy the sndfile dll
cd ../../../build/ || exit # Go back to the build folder
cp sndfile.dll Release/ &> /dev/null || echo " " # Copy into release
cp Release/"${prjname}".exe . &> /dev/null || echo " " # Copy the executable

echo -e "\x1B[32mEngine and project successfully installed! \033[0m" # Print a success message in green
