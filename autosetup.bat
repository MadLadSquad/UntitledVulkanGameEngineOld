@ECHO OFF

echo Compiling GLEW ...

cd Engine/ThirdParty/glew/auto && mingw32-make
cd ../
mingw32-make install
cd ../../../

echo Compiled GLEW!

echo Creating project file with default settings ...

echo name: Game > "uvproj.yaml"
echo startup-level: "lvl" >> "uvproj.yaml"
echo version: 1.0.0 >> "uvproj.yaml"
echo engine-version: 1.0.0 >> "uvproj.yaml"

echo Compiling build tool and generating files ...
mkdir Source && mkdir Generated && mkdir Exported && cd Config && mkdir Settings && cd ../
cd UVKBuildTool/ && mkdir build && cd build
cmake .. -G "Unix Makefiles" && mingw32-make 
UVKBuildTool --install
cd ../../ && mkdir build && cd build && cmake .. && cd ..
