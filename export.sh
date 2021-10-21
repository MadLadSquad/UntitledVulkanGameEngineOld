#!/bin/bash
function help()
{
  echo "The following script helps you export your project for production"
  echo "It's recommended that you don't run this script alone and use the UVKBuildTool"
  echo "Commands:"
  echo "  --help/help/-H/-h - displays this help message"
  echo "  <anything else> - would treat the argument as the name of a project and compile"
}

if $1 == ""
then
  echo -e "\x1B[31mError: You cannot run the script without an additional argument!\033[0m"
  help
  exit
elif $1 == "help" || $1 == "--help" || $1 == "-H" || $1 == "-h"
then
  help
  exit
fi

jobs=$(grep -c processor /proc/cpuinfo) ## get the cpu threads for maximum performance when compiling
echo -e "\x1B[32mCopiling with ${jobs} compute jobs!\033[0m"
echo -e "\x1B[32m-----------------------------------\033[0m"
cd ../Exported/ || exit
cmake .. -G "Visual Studio 16 2019" || cmake .. -G "Unix Makefiles" || exit
MSBuild.exe "$1".sln -property:Configuration=Release -property:Platform=x64 -property:maxCpuCount="${jobs}" || make -j "${jobs}" || exit
rm -rf "CMake*" "Makefile" "*.cmake"
find . -name '*.cmake' -delete && find . -type d -name "CMakeFiles" -exec rm -rf {} \;
find Engine/ -name "Makefile" -exec rm -rf {} \; && find Engine/ -name "*.h" -exec rm -rf {} \;
find Engine/ -name "*.pc" -exec rm -rf {} \; && find . -type d -empty -exec rmdir {} \;
find . -type d -name "docs" -exec rm -rf {} \; && find . -type d -empty -exec rmdir {} \;
cd .. || exit
echo -e "\x1B[32m-----------------------------------\033[0m"
echo -e "\x1B[32mBuild Done!\033[0m"