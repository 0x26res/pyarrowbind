set -e

python -c 'import pyarrow as pa; pa.create_library_symlinks()'

rm -rf build
mkdir build
cd build
/usr/bin/cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=/usr/bin/g++ -G "CodeBlocks - Unix Makefiles" ../
cd ..
