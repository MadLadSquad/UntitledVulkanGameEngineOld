#!/bin/bash
download_vswhere() {
  # Get the raw JSON code for the releases from Github, get the lines that have the browser download URL and truncate the string in the front and back
  # to get the URL, then we use the URL to download the application, this only happens if we cannot find
  line=$(curl https://api.github.com/repos/microsoft/vswhere/releases 2> /dev/null | grep "https://github.com/microsoft/vswhere/releases/download/")
  line="${line:33}"
  line="${line%\"*}"
  
  # Set a fake user agent string here so that we evade being blocked by GitHub
  curl "${line}" -L -A "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:106.0) Gecko/20100101 Firefox/106.0" -o vswhere.exe
}

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

windows=false
env | grep "OS=Windows" > /dev/null && windows=true

if [ "${windows}" = true ]; then
  wd=$(pwd)
  cd "C:/Program Files (x86)/Microsoft Visual Studio/Installer/"
  find "vswhere.exe" -maxdepth 0 &> /dev/null || (cd "${wd}" && download_vswhere)
  vs_path=$(./vswhere.exe | grep "installationPath")
  vs_path="${vs_path:18}"

  VSShortVer=$(./vswhere.exe | grep "catalog_productLine: Dev17")
  VSShortVer="${VSShortVer:24}"

  VSVer=$(./vswhere.exe | grep "catalog_productLineVersion:")
  VSVer="${VSVer:28}"

  setx PATH "${vs_path}/MSBuild/Current/Bin/amd64/;%PATH%" 2> /dev/null
  cd "${wd}"
fi

mkdir Projects/

cd UVKBuildTool/ || exit
mkdir build || exit # Will store our compiled binary
cd build || exit

if [ "${windows}" == true ]; then
  cmake .. -G "Visual Studio ${VSShortVer} ${VSVer}" -DCMAKE_BUILD_TYPE=RELEASE || exit
  MSBuild.exe UVKBuildTool.sln -property:Configuration=Release -property:Platform=x64 -property:maxCpuCount="${cpus}" || exit

  # Copy the files from the Release directory so that we're compatible with the multiplatform CMakeLists.txt file
  cp Release/UVKBuildTool.exe . 2> /dev/null || echo -n " " || exit
  cp Release/UVKBuildToolLib.dll . 2> /dev/null || cp Release/libUVKBuildToolLib.dll . 2> /dev/null || exit
  cp Release/UVKBuildToolLib.lib . 2> /dev/null || cp Release/libUVKBuildToolLib.lib . 2> /dev/null || exit
  cp yaml-cpp/Release/yaml-cpp.dll . 2> /dev/null || cp yaml-cpp/Release/libyaml-cpp.dll . 2> /dev/null || exit
else
  cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RELEASE || exit
  make -j "${cpus}"
fi

cd ../../ || exit

cd UVKShaderCompiler/ || exit
cd ThirdParty/shaderc/utils/ || exit
./git-sync-deps 2> /dev/null || python3 git-sync-deps 2> /dev/null || py git-sync-deps 2> /dev/null || (echo -e "\x1b[31mCouldn't sync dependencies!\x1b[0m" && exit)
cd ../../../ || exit
mkdir build
cd build || exit

echo " "
echo -e "\x1B[32m--------------------------------------------------------------------------------------------------\033[0m"
echo -e "\x1b[32mCompiling the ShaderCompiler ...\x1b[0m"
echo -e "\x1b[32m--------------------------------------------------------------------------------------------------\x1b[0m"
echo " "

if [ "${windows}" == true ]; then
  cmake .. -G "Visual Studio ${VSShortVer} ${VSVer}" -DCMAKE_BUILD_TYPE=RELEASE || exit
  MSBuild.exe UVKShaderCompiler.sln -property:Configuration=Release -property:Platform=x64 -property:maxCpuCount="${cpus}" || exit

  # Copy the files from the Release directory so that we're compatible with the multiplatform CMakeLists.txt file
  cp Release/UVKShaderCompiler.exe . 2> /dev/null || exit
  cp Release/UVKShaderCompilerLib.dll . 2> /dev/null || cp Release/libUVKShaderCompilerLib.dll . 2> /dev/null || exit
  cp Release/UVKShaderCompilerLib.lib . 2> /dev/null || cp Release/libUVKShaderCompilerLib.lib . 2> /dev/null || exit
  cp Release/*.dll . 2> /dev/null || exit
else
  cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RELEASE || exit
  make -j "${cpus}" || exit
fi

cd ../../

echo ""
echo -e "\x1b[32m--------------------------------------------------------------------------------------------------\x1b[0m"
echo -e "\x1b[32mSuccessfully installed the engine tools, now create a project using the create-project.sh script!"
echo -e "\x1b[32m--------------------------------------------------------------------------------------------------\x1b[0m"
