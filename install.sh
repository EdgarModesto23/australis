#!/bin/bash

seastar_dir=~/seastar/

cmake -G Ninja -DCMAKE_PREFIX_PATH="$seastar_dir/build/release;$seastar_dir/build/release/_cooking/installed" -DCMAKE_MODULE_PATH=$seastar_dir/cmake -B build -S .
