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


if [ "$1" != "" ]; then
  prjname="$1"
else
  read -rp "Enter Your Application Name: " prjname # read the project name
fi

prjname=${prjname/ /} # Remove any spaces if the name contains them
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

cd Projects/ || exit
mkdir "${prjname}" || echo "Project already exists!"
cd "${prjname}" || exit

# Create folders and files to be used as configs
mkdir Source || echo "Project already exists!"
mkdir Generated || echo "Project already exists!"
mkdir WrapperSource || echo "Project already exists!"
mkdir build || echo "Project already exists!"
mkdir Exported || echo "Project already exists!"

# Copy the config template we want
cp ../../Config/ . -r
cp ../../Content/ . -r

cd Config/ || echo "Project already exists!"
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

# We create a project file which will be used to configure our generated files
touch uvproj.yaml && echo "\
name: \"${prjname}\"
startup-level: \"lvl\"
version: 1.0.0
engine-version: 1.0.0" > uvproj.yaml

echo -e "\x1B[32mCreating symbolic links and generating files ...\033[0m"

# We symlink the Engine source folder so that 
ln -rs "../../Engine/" Engine 2> /dev/null || cp ../../Engine/ . -r
ln -rs "../../UVKBuildTool/" UVKBuildTool 2> /dev/null || cp ../../UVKBuildTool/ . -r
ln -rs "../../UVKShaderCompiler/" UVKShaderCompiler 2> /dev/null || cp ../../UVKShaderCompiler/ . -r
cp ../../export.sh .

cd ../../UVKBuildTool/build || exit
if [ "${windows}" == true ]; then
  ./UVKBuildTool.exe --install "../../Projects/${prjname}" || exit
  cd ../../UVKShaderCompiler/build || exit
  ./UVKShaderCompiler.exe --compile "../../Projects/${prjname}" || exit
else
  ./UVKBuildTool --install "../../Projects/${prjname}" || exit
  cd ../../UVKShaderCompiler/build || exit
  ./UVKShaderCompiler --compile "../../Projects/${prjname}" || exit
fi

cd "../../Projects/${prjname}" || exit
cd build || exit

echo -e "\x1B[32m--------------------------------------------------------------------------------\033[0m"
echo -e "\x1B[32mCompiling ${prjname} ...\033[0m"
echo -e "\x1B[32m--------------------------------------------------------------------------------\033[0m"

if [ "${windows}" == true ]; then
  cmake .. -G "Visual Studio ${VSShortVer} ${VSVer}" -DCMAKE_BUILD_TYPE=RELEASE || exit
  MSBuild.exe "${prjname}".sln -property:Configuration=Release -property:Platform=x64 -property:maxCpuCount="${cpus}" || exit

  cp Engine/ThirdParty/openal/Release/OpenAL32.dll . &> /dev/null || exit
  cp OpenAL32.dll Release/ &> /dev/null || exit
  
  cd ../Engine/ThirdParty/vulkan || exit
  cp sndfile.dll ../../../build/ || exit
  
  cd ../../../build/ || exit
  cp sndfile.dll Release || exit

  cp Release/"${prjname}".exe . || exit
  cp Engine/ThirdParty/yaml/Release/yaml-cpp.dll ../UVKShaderCompiler/build/Release/UVKShaderCompilerLib.dll ../UVKBuildTool/build/Release/UVKBuildToolLib.dll . || exit
else
  cmake .. -D "Unix Makefiles" -DCMAKE_BUILD_TYPE=RELEASE || exit
  make -j "${cpus}" || exit
fi
echo -e "\x1b[32m--------------------------------------------------------------------------------\x1b[0m"
echo -e "\x1B[32mEngine and project successfully installed! \033[0m"
