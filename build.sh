#!/bin/bash

sudo apt install libxrandr-dev libxcursor-dev libxi-dev libudev-dev libflac-dev libvorbis-dev libgl1-mesa-dev libegl1-mesa-dev libdrm-dev libgbm-dev libfreetype-dev
cmake -S . -B build
cmake --build build --config Release --parallel 4

if [[ ! -d __release ]]; then
  mkdir __release
fi

cp build/main/MainApp __release/