#!/bin/bash
rm -rf Source || echo "Message: Folder with name \"Source\" doesn't exist!"
rm -rf Generated || echo "Message: Folder with name \"Generated\" doesn't exist!"
rm -rf Exported || echo "Message: Folder with name \"Exported\" doesn't exist!"
rm -rf build || echo "Message: Folder with name \"build\" doesn't exist!"
rm -rf docs || echo "Message: Folder with name \"docs\" doesn't exist!"
rm uvproj.yaml || echo "Message: File with name \"uvproj.yaml\" doesn't exist!"
rm CMakeLists.txt || echo "Message: File with name \"CMakeLists.txt\" doesn't exist!"

cd UVKBuildTool/ || exit
rm -rf build || echo "Message: Folder with name \"build\" doesn't exist!"
cd ../ || exit

echo -e "\x1B[32mSuccessfully cleaned up!\033[0m"