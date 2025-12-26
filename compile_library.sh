#!/bin/bash

# Exit immediately if a command fails
set -e

for file in src/*.c; do
    obj_file="${file%.c}.o"
    gcc -c "$file" -o "${file%.c}.o"
done

ar rcs libmylib.a src/*.o

rm src/*.o
	
echo "Build complete!"
