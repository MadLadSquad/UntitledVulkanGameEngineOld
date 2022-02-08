#!/bin/bash
rm -rf Source &> /dev/null || echo "Message: Folder with name \"Source\" doesn't exist!"
rm -rf Generated &> /dev/null || echo "Message: Folder with name \"Generated\" doesn't exist!"
rm -rf Exported &> /dev/null || echo "Message: Folder with name \"Exported\" doesn't exist!"
rm -rf build &> /dev/null || echo "Message: Folder with name \"build\" doesn't exist!"
rm -rf docs &> /dev/null || echo "Message: Folder with name \"docs\" doesn't exist!"
rm -rf WrapperSource &> /dev/null || echo "Message: Folder with name \"WrapperSource\" doesn't exist!"
rm uvproj.yaml &> /dev/null || echo "Message: File with name \"uvproj.yaml\" doesn't exist!"
rm CMakeLists.txt &> /dev/null || echo "Message: File with name \"CMakeLists.txt\" doesn't exist!"

cd UVKBuildTool/ || exit
rm -rf build &> /dev/null || echo "Message: Folder with name \"build\" doesn't exist!"
cd ../ || exit

echo -e "\x1B[32mSuccessfully cleaned up!\033[0m"