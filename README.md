# SHA-256
SHA-256 (SHA-2) hash function from RFC 4634.

### How to use
Include "include/sha256_c.hpp" into your cpp file.

### How to run sanity-check
```
cd sha-256
mkdir build
cd build
cmake -DCMAKE_C_COMPILER=gcc-7 -DCMAKE_CXX_COMPILER=g++-7 -DCMAKE_BUILD_TYPE=Debug ..
make
./hash-check
```
