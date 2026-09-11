@echo off

cls

cmake -S . -B Build -G Ninja -D CR_RELEASE=ON
cmake --build Build
cmake --install Build

pause
cls

ChromaRave

pause
cls
