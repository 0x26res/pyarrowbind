set -e

/usr/bin/cmake --build ./build --target bindings -- -j 3
PYTHONPATH='./build' python -c 'import pyarrow; import bindings; bindings.test_import()'
PYTHONPATH='./build' python -c 'import bindings; bindings.test_import()'
PYTHONPATH='./build' python -c 'import bindings; print(bindings.create_table().to_pandas())'