#!/bin/bash

echo "Compiling the framework"
cd ../
make -B
./ViennaTool/test
