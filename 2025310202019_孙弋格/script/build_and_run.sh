#!/bin/sh
set -eu
course_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
cmake -S "$course_root" -B "$course_root/build" -DCMAKE_BUILD_TYPE=Debug
cmake --build "$course_root/build" --parallel
(cd "$course_root/build" && ctest --output-on-failure)
