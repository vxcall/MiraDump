call npm install
call npx electron-builder --win --x64
copy /y "config.toml" "dist\win-unpacked\config.toml"
mkdir build
cd build
cmake ..
cmake --build .
cd ..
copy /y "build\Debug\MiraDump.exe" "dist\win-unpacked\MiraDump.exe"
pause
