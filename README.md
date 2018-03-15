# SHA-256
SHA-256 (SHA-2) hash function from RFC 4634.

## How to use
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

## How to build and run sanity-check
### Linux
Clone the repo.
```bash
git clone https://github.com/sam0delk1n/sha-256.git
```
Create `build/Debug/` and `build/Release/` in the repo root folder.
```bash
cd sha-256
mkdir build
cd build
mkdir Debug Release
```
Generate `Makefile` with Debug options and build it. You need CMake 3.10.2 and GCC-7/g++-7.
```bash
cd Debug
cmake -DCMAKE_BUILD_TYPE=Debug ../..
make
```
Run the test.
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

### Linux and Docker
What is Docker please read here: https://docs.docker.com/.  

If you don't have required compilers or tools, you can build and run this project with Docker. Before start, please delete `build` folder if you've already create it.
```bash
cd sha-256
docker build -t sha-256-check .
```
Docker downloads Linux Bionic image with GCC-7/g++-7 and CMake that are already installed. Then Docker builds the project into `/home/app/build/Debug/` and `home/app/build/Release/` (inside the image) respectively and containerizes into the image named `sha-256-check`. Now you can run SHA-256 tests.
```bash
docker run sha-256-check /home/app/build/Debug/hash-check
docker run sha-256-check /home/app/build/Release/hash-check
```

### Windows and MS Visual Studio 2017
Clone the repo.
```bat
git clone https://github.com/sam0delk1n/sha-256.git
```
Create `build\msvs\` in the repo root folder.
```bat
cd sha-256
mkdir build\msvs
```
Generate `Project.sln`. You need CMake 3.10.2 and MSVS 2017.
```bat
cd build\msvs
cmake -G"Visual Studio 15 2017 Win64" ..\..
```
Now you can open `Project.sln` in MSVS and build Debug, Relese, etc.  
The project named `hash-check` set as StartUp Project to run in Studio. Or run `hash-check.exe` in the terminal window and you can see the program's output.

### Windows and MinGW-W64
Clone the repo.
```bat
git clone https://github.com/sam0delk1n/sha-256.git
```
Create `build\mingw\Debug\` and `build\mingw\Release\` in the repo root folder.
```bat
cd sha-256
mkdir build\mingw\Debug build\mingw\Release
```
Generate `Makefile` with Debug options and build it. You need CMake 3.10.2 and MinGW-W64 with GCC-7/g++-7.
```bat
cd build\mingw\Debug
cmake -G"MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug ..\..\..
mingw32-make
```
Run the test.
```bat
hash-check
```
Then do the same for Release.
```bat
cd ..\Release
cmake -G"MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..\..\..
mingw32-make
hash-check
```
