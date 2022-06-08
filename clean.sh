#!/bin/bash

for d in */ ; do
    echo "Cleaning $d"
    make clean -C $d
done
rm stack_limit
