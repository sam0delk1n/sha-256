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
#include "except_c.hpp"

#include <iostream>
#include <string>
#include <exception>

using namespace std;
using namespace smd::hash;

//==============================================================================================================================
int main( void ) try {
    {
        const string cInput   { "" };
        const string cCorrect { "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855" };

        SMD_HASSERT( cCorrect == bytesToHexStr( sha256( cInput ) ) );
        cout << "SHA-256 (empty):         PASSED" << endl;
    } {
        const string cInput   { "Hello, World !" };
        const string cCorrect { "7d486915b914332bb5730fd772223e8b276919e51edca2de0f82c5fc1bce7eb5" };

        SMD_HASSERT( cCorrect == bytesToHexStr( sha256( cInput ) ) );
        cout << "SHA-256 (short):         PASSED" << endl;
    } {
        const string cInput {
            "This software is provided 'as-is', without any express or implied "
            "warranty. In no event will the authors be held liable for any damages "
            "arising from the use of this software."
        };
        const string cCorrect { "0dd5fcbf368e3f5842d38b14403fd5f4ea41f67765e13a9740ce132f6b1ab3c0" };

        SMD_HASSERT( cCorrect == bytesToHexStr( sha256( cInput ) ) );
        cout << "SHA-256 (long):          PASSED" << endl;
    } {
        const string cInput   { "This software is provided 'as-is', without any express or impl" };
        const string cCorrect { "8ccaf1ba699477be80c2f631b4b3129ce0055da1e6b5577c18b36d1f5c6ff0be" };

        SMD_HASSERT( cCorrect == bytesToHexStr( sha256( cInput ) ) );
        cout << "SHA-256 (62 bytes):      PASSED" << endl;
    } {
        const string cInput   { "This software is provided 'as-is', without any express or implie" };
        const string cCorrect { "73e34de3c6979b399213882e8636c3b468c28f6c9cdde2673d81a9a7839af415" };

        SMD_HASSERT( cCorrect == bytesToHexStr( sha256( cInput ) ) );
        cout << "SHA-256 (block aligned): PASSED" << endl;
    }

    return 0;

} catch ( const exception& cEx ) {
    cerr << cEx.what() << endl;
    return 1;

} catch ( ... ) {
    cerr << "FATAL ERROR !!!" << endl;
    return 2;
}
