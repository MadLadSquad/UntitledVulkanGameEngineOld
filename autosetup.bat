@ECHO OFF

echo "Compiling GLEW ..."

cd Engine/ThirdParty/glew/auto && mingw32-make && cd .. && mingw32-make && cd ../../../

echo "Compiled GLEW!"

echo "Creating project file with default settings ..."

echo "\
name: Game 
renderer-subsystem: Legacy
version: 1.0.0
engine-version: 1.0.0
production: false" > "uvproj.yaml"

echo "Compiling build tool and generating files ..."

cd UVKBuildTool/ && mkdir build && cd build && cmake .. -G "Unix Makefiles" && mingw32-make && ./UVKBuildTool --generate && cd ../../ && mkdir build && cd build && cmake ..
