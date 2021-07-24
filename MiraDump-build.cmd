call npm install
call npm i electron -D
call npm i electron-builder -D
call npx electron-builder --win --x64
copy /y "config.toml" "dist\win-unpacked\config.toml"
mkdir build
cd build
cmake ..
cmake --build .
cd ..
copy /y "build\Debug\MiraDump.exe" "dist\win-unpacked\MiraDump.exe"
pause
