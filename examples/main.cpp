//==============================================================================================================================
//
// This file is part of the sam0delk1n's Conventional Tools (smdCT).
//
// Copyright © 2018 sam0delk1n <skipper05ster@gmail.com>.
// All rights reserved.
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//
//==============================================================================================================================

#include "../include/sha256_c.hpp"

#include <exception>
#include <string>
#include <iostream>

using namespace std;
using namespace smd::hash;

//==============================================================================================================================
int main( void ) try {
    const string cInput { "Hello, World!" };         // The input string.
    sha256_c::hash_t hash;                           // The variable for 256-bit hash in binary format.
    hash = sha256( cInput );                         // Compute hash.
    const string cHashStr { bytesToHexStr( hash ) }; // Convert the binary hash to string format.
    cout << cHashStr << endl;                        // Print the string to the terminal output.

    return 0;

} catch ( const exception& cEx ) {
    cerr << cEx.what() << endl;
    return 1;

} catch ( ... ) {
    cerr << "FATAL ERROR !!!" << endl;
    return 2;
}
