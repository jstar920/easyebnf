#! /bin/bash

if [ -d "linux_output" ]; then
    rm -rf linux_output
fi

mkdir linux_output
cd linux_output

cmake ../CMakeLists.txt

cd ..
