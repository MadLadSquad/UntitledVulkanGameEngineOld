#!/bin/bash
echo "Compiling GLEW ..."

cd Engine/ThirdParty/glew/auto

cd ..

make 

cd ../../../

echo "Compiled GLEW!"

echo "Creating project file with default settings ..."

touch uvproj.yaml && echo "\
name: Game
startup-level: \"lvl.yaml\"
startup-level-exists: false
version: 1.0.0
engine-version: 1.0.0" > uvproj.yaml

echo "Compiling build tool and generating files ..."

cd UVKBuildTool/ && mkdir build && mkdir Source && cd build && cmake .. -G "Unix Makefiles" && make && ./UVKBuildTool --generate && cd ../../ && mkdir build && cd build && cmake .. && cd ..

echo "\
name: Game
startup-level: \"lvl.yaml\"
startup-level-exists: true
version: 1.0.0
engine-version: 1.0.0" > uvproj.yaml

cd build/
