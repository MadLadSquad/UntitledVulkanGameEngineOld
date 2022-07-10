#!/bin/bash
cpus=$(grep -c processor /proc/cpuinfo)
echo -e "\x1b[32mCompiling with ${cpus} jobs!\x1b[0m"

git pull
git submodule update --remote --merge

cd UVKShaderCompiler/ || exit
git pull
git submodule update --remote --merge

cd ThirdParty/shaderc/third_party/ || exit
rm -rf effcee glslang googletest re2 spirv-headers spirv-tools &> /dev/null

cd ../utils/ || exit
./git-sync-deps || py git-sync-deps || python git-sync-deps || python3 git-sync-deps || (echo -e "\x1b[31mFailed to run the update deps script under UVKShaderCompiler/ThirdParty/shaderc/utils!\x1b[0m" && exit)

cd ../../../ || exit
cd build || exit
cmake .. || exit
MSBuild.exe UVKShaderCompiler.sln -property:Configuration=Release -property:Platform=x64 -property:maxCpuCount="${cpus}" || make -j "${cpus}" || exit
cd Release || echo " "
cp UVKShaderCompiler.exe ../ 2> /dev/null || echo " " || exit
cp UVKShaderCompilerLib.dll ../ 2> /dev/null || cp libUVKShaderCompilerLib.dll ../ 2> /dev/null || echo " "
cp UVKShaderCompilerLib.lib ../ 2> /dev/null || cp libUVKShaderCompilerLib.lib ../ 2> /dev/null || echo " "
cp *.dll ../ 2> /dev/null || echo " "

cd ../../../UVKBuildTool/ || exit
git pull
git submodule update --remote --merge
cd build/ || exit
MSBuild.exe UVKBuildTool.sln -property:Configuration=Release -property:Platform=x64 -property:maxCpuCount="${cpus}" || make -j "${cpus}" || exit
cp Release/UVKBuildTool.exe . 2> /dev/null || echo " " || exit
cp Release/UVKBuildToolLib.dll . 2> /dev/null || cp Release/libUVKBuildToolLib.dll . 2> /dev/null || echo " "
cp Release/UVKBuildToolLib.lib . 2> /dev/null || cp Release/libUVKBuildToolLib.lib . 2> /dev/null || echo " "
cp yaml-cpp/Release/yaml-cpp.dll . 2> /dev/null || cp yaml-cpp/Release/libyaml-cpp.dll . 2> /dev/null || echo " "

cd ../../ || exit
echo -e "\x1b[32mSuccessfully updated the game engine, you can now run the \"UVKBuildTool --generate\" command on your project to regenerate your files for the new engine version!\x1b[0m"
