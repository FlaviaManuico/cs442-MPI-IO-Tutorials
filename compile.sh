#!/bin/bash

mkdir -p build
cd build

cmake ..
cmake -DUSE_PY=OFF ..

make -j 4

cd ..
