# SHA-256
SHA-256 (SHA-2) hash function from RFC 4634.

### How to use
It's a header-only library so just put `sha256_c.hpp` into your `.cpp` file.
```cpp
#include "include/sha256_c.hpp"

using namespace std;
using namespace smd::hash;

int main( void ) {
    const string cInput { "Hello, World!" };         // The input string.
    sha256_c::hash_t hash;                           // The variable for 256-bit hash in binary format.
    hash = sha256( cInput );                         // Compute hash.
    const string cHashStr { bytesToHexStr( hash ) }; // Convert the binary hash to the string format.
    cout << cHashStr << endl;                        // Print number to the terminal output.

    return 0;
}
```

### How to build and run sanity-check
Clone the repository.
```bash
git clone https://github.com/sam0delk1n/sha-256.git
```
Create `build/Debug` and `build/Release` folders in the repository root folder.
```bash
cd sha-256
mkdir build
cd build
mkdir Debug Release
```
Build Debug version. You need CMake 3.10.2 and GCC-7/g++-7.
```bash
cd Debug
cmake -DCMAKE_BUILD_TYPE=Debug ../..
make
```
Run test.
```bash
./hash-check
```
Then do the same for Release.
```bash
cd ../Release
cmake -DCMAKE_BUILD_TYPE=Release ../..
make
./hash-check
```

### How to build and run with Docker
What is Docker please read here: https://docs.docker.com/.  

If you don't have required compilers or tools, you can build and run this project with Docker. Before start, please delete `build` folder if you've already create it.
```bash
cd sha-256
docker build -t sha-256-check .
```
Docker downloads Linux Bionic image with GCC-7/g++-7 and CMake that are already installed. Then Docker builds the project into `/home/app/build/Debug` and `home/app/build/Release` (inside the image) respectively and containerizes into the image with name `sha-256-check`. Now you can run SHA-256 tests.
```bash
docker run sha-256-check /home/app/build/Debug/hash-check
docker run sha-256-check /home/app/build/Release/hash-check
```
