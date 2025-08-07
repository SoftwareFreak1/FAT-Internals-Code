#!/bin/bash
set -e
gcc -o main ./src/*.c
./main "$@"
