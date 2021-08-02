#!/bin/bash
echo "Compiling GLEW ..."

mkdir Source || exit
mkdir Generated || exit
cd Config || exit
touch Engine/GameKeybinds.yaml
echo "\
bindings:
  - key: NewAction0
    val: 65
" > Engine/EditorKeybinds.yaml
cd .. || exit


cd Engine/ThirdParty/glew/auto || exit 
make || exit

cd .. || exit

make || exit

cd ../../../ || exit

echo "Compiled GLEW!"

echo "Creating project file with default settings ..."

touch uvproj.yaml && echo "\
name: Game
startup-level: \"lvl\"
version: 1.0.0
engine-version: 1.0.0" > uvproj.yaml

echo "Compiling build tool and generating files ..."

cd UVKBuildTool/ || exit
mkdir build || exit
cd build || exit
cmake .. -G "Unix Makefiles" || exit
make || exit
./UVKBuildTool --install || exit
cd ../../ || exit
mkdir build || exit
mkdir Exported  || exit
cd build || exit
cmake .. || exit
cd .. || exit

echo "\
name: Game
startup-level: \"lvl\"
version: 1.0.0
engine-version: 1.0.0" > uvproj.yaml

cd build/ || exit
