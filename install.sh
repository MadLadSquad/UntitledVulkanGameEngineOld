#!/bin/bash
if [ "$1" == "" ]; then
	while true; do
    	echo -e "Before we begin, if you're on Windows, check that your Visual Studio instance is installed under \"C:/Program Files (x86)/Microsoft Visual Studio/\"\nand that you have at least Visual Studio 2017 installed!"
    	read -rp "Start installation? Y(Yes)/N(No): " yn
    	case $yn in
        	[Yy]* ) break;;
        	[Nn]* ) exit;;
        	* ) echo "Please answer with Y(Yes) or N(No)!";;
    	esac
	done

	while true; do
    	read -rp "Do you want to download offline documentation Y(Yes)/N(No): " yn
    	case $yn in
        	[Yy]* ) git clone https://github.com/MadLadSquad/UntitledVulkanGameEngine.wiki.git docs/; break;;
        	[Nn]* ) break;;
        	* ) echo "Please answer with Y(Yes) or N(No)!";;
    	esac
	done
fi
cpus=$(grep -c processor /proc/cpuinfo) ## get the cpu threads for maximum performance when compiling
echo -e "\x1B[32mCopiling with ${cpus} compute jobs!\033[0m"

wdir=$(pwd) # get the working dir since we are going to be returning there
cd "C:/Program Files (x86)/Microsoft Visual Studio/" 2> /dev/null || echo " "
VSVer=$(find "2022" -maxdepth 0 2> /dev/null) || VSVer=$(find "2019" -maxdepth 0 2> /dev/null) || VSVer=$(find "2017" -maxdepth 0 2> /dev/null) || echo " " > /dev/null
cd "${VSVer}" 2> /dev/null || echo " " > /dev/null # Go to the Visual Studio Version dir
VSType=$(find "Community" -maxdepth 0 2> /dev/null) || VSType=$(find "Enterprise" -maxdepth 0 2> /dev/null) || VSType=$(find "Professional" -maxdepth 0 2> /dev/null) || echo " " > /dev/null # Set the VS type to one of the 3 types
cd "${wdir}" 2> /dev/null || echo " " > /dev/null # Return to the old directory
setx PATH "C:/Program Files (x86)/Microsoft Visual Studio/${VSVer}/${VSType}/MSBuild/Current/Bin/amd64/;%PATH%" 2> /dev/null || echo " " > /dev/null # Set the path
if [ "$VSVer" == "2022" ]; then VSShortVer="17"
elif [ "$VSVer" == "2019" ]; then VSShortVer="16"
elif [ "$VSVer" == "2017" ]; then VSShortVer="15"
else VSShortVer="1"
fi

mkdir Projects/

cd UVKBuildTool/ || exit
mkdir build || exit # Will store our compiled binary
cd build || exit

if [ "$1" == "ci" ]; then
  cmake .. -DCMAKE_BUILD_TYPE=RELEASE || exit
else
  cmake .. -G "Visual Studio ${VSShortVer} ${VSVer}" -DCMAKE_BUILD_TYPE=RELEASE || cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RELEASE || exit # Generate the UVKBuildTool project files
fi

# Try to run MSBuild first, if it fails we are either on a non-Windows system or the user doesn't have Visual Studio installed
MSBuild.exe UVKBuildTool.sln -property:Configuration=Release -property:Platform=x64 -property:maxCpuCount="${cpus}" || make -j "${cpus}" || exit

# If on Windows copy the UVKBuildTool executable from the Release folder, this will absolutely fail on any non-Windows system in which
# case we will just echo an empty message
cp Release/UVKBuildTool.exe . 2> /dev/null || echo " " || exit
cp Release/UVKBuildToolLib.dll . 2> /dev/null || cp Release/libUVKBuildToolLib.dll . 2> /dev/null || echo " "
cp Release/UVKBuildToolLib.lib . 2> /dev/null || cp Release/libUVKBuildToolLib.lib . 2> /dev/null || echo " "
cp yaml-cpp/Release/yaml-cpp.dll . 2> /dev/null || cp yaml-cpp/Release/libyaml-cpp.dll . 2> /dev/null || echo " "
cd ../../ || exit

cd UVKShaderCompiler/ || exit
cd ThirdParty/shaderc/utils/ || exit
./git-sync-deps || python3 git-sync-deps || py git-sync-deps || (echo -e "\x1b[31mCouldn't sync dependencies!\x1b[0m" && exit)
cd ../../../ || exit
mkdir build
cd build || exit

if [ "$1" == "ci" ]; then
  cmake .. -DCMAKE_BUILD_TYPE=RELEASE || exit
else
  cmake .. -G "Visual Studio ${VSShortVer} ${VSVer}" -DCMAKE_BUILD_TYPE=RELEASE || cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RELEASE || exit
fi

echo " "
echo -e "\x1B[32m--------------------------------------------------------------------------------\033[0m"
echo -e "\x1b[32mCompiling the ShaderCompiler ...\x1b[0m"
echo -e "\x1b[32m--------------------------------------------------------------------------------\x1b[0m"
echo " "

# Compiler the Shader Compiler
MSBuild.exe UVKShaderCompiler.sln -property:Configuration=Release -property:Platform=x64 -property:maxCpuCount="${cpus}" || make -j "${cpus}" || exit
cp Release/UVKShaderCompiler.exe . 2> /dev/null || echo " " || exit
cp Release/UVKShaderCompilerLib.dll . 2> /dev/null || cp Release/libUVKShaderCompilerLib.dll . 2> /dev/null || echo " "
cp Release/UVKShaderCompilerLib.lib . 2> /dev/null || cp Release/libUVKShaderCompilerLib.lib . 2> /dev/null || echo " "
cp Release/*.dll . 2> /dev/null || echo " "
cd ../../
