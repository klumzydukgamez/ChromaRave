@echo off

cls

cmake -S . -B Build -G Ninja
cmake --build Build
cmake --install Build

cls

ChromaRave

pause
cls
