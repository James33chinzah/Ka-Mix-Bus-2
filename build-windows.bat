@echo off
setlocal
where cmake >nul 2>nul || (echo ERROR: CMake not found. Install CMake 3.22+ and add it to PATH.& pause & exit /b 1)
where git >nul 2>nul || (echo ERROR: Git not found. Install Git and add it to PATH.& pause & exit /b 1)
if not exist build mkdir build
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
if errorlevel 1 (echo CMake configure failed. Check Visual Studio C++ workload and internet connection.& pause & exit /b 1)
cmake --build build --config Release --target BlackSaltBusMixClone_VST3
if errorlevel 1 (echo Build failed. See compiler output above.& pause & exit /b 1)
echo.
echo Build complete. Find the VST3 bundle under build\BlackSaltBusMixClone_artefacts\Release\VST3\
pause
