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

#pragma once

#include <cstdint>
#include <cstring>
#include <array>
#include <vector>
#include <string>
#include <sstream>
#include <ios>
#include <iomanip>

namespace smd::hash {

//==============================================================================================================================
class sha256_c final {
public:
    using hash_t = std::array< uint8_t, 32 >; // The digest size for SHA-256 is 256 bit.

    inline hash_t operator()( const uint8_t* cpMessage, uint64_t msgSize );
    inline hash_t mDo( const uint8_t* cpMessage, uint64_t msgSize );

    sha256_c& operator=( const sha256_c& ) = delete;
    sha256_c& operator=( sha256_c&& )      noexcept = delete;
              sha256_c( void )             = default;
              sha256_c( const sha256_c& )  = delete;
              sha256_c( sha256_c&& )       noexcept = delete;
              ~sha256_c( void )            = default;

protected:
    using block_t = std::array< uint8_t, 64 >; // The block size for SHA-256 and SHA-224 is 512 bit.

    static constexpr std::array< uint32_t, 64 > scCubeRoots {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
        0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
        0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
        0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
        0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
        0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    // Initialize with the initial hash value.
    std::array< uint32_t, 8 > mHashVals {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

    inline void mTransform( const uint8_t* cpMsg, uint64_t blockNum );

    static constexpr uint32_t sOp_rotr( uint32_t x, int n ) noexcept;

    static constexpr uint32_t sOp_ch( uint32_t x, uint32_t y, uint32_t z )  noexcept;
    static constexpr uint32_t sOp_maj( uint32_t x, uint32_t y, uint32_t z ) noexcept;
    static constexpr uint32_t sOp_bsig0( uint32_t x )                       noexcept;
    static constexpr uint32_t sOp_bsig1( uint32_t x )                       noexcept;
    static constexpr uint32_t sOp_ssig0( uint32_t x )                       noexcept;
    static constexpr uint32_t sOp_ssig1( uint32_t x )                       noexcept;

    static constexpr void     sUnpack32( uint8_t out[ 4 ], uint32_t in ) noexcept;
    static constexpr void     sUnpack64( uint8_t out[ 8 ], uint64_t in ) noexcept;
    static constexpr uint32_t sPack32( const uint8_t cIn[ 4 ] )          noexcept;
};

//==============================================================================================================================
constexpr uint32_t sha256_c::sOp_rotr( uint32_t x, int n ) noexcept {
    return x >> n | x << ( 32 - n );
}

//==============================================================================================================================
constexpr uint32_t sha256_c::sOp_ch( uint32_t x, uint32_t y, uint32_t z ) noexcept {
    return ( x & y ) ^ ( ~x & z );
}

//==============================================================================================================================
constexpr uint32_t sha256_c::sOp_maj( uint32_t x, uint32_t y, uint32_t z ) noexcept {
    return ( x & y ) ^ ( x & z ) ^ ( y & z );
}

//==============================================================================================================================
constexpr uint32_t sha256_c::sOp_bsig0( uint32_t x ) noexcept {
    return sOp_rotr( x, 2 ) ^ sOp_rotr( x, 13 ) ^ sOp_rotr( x, 22 );
}

//==============================================================================================================================
constexpr uint32_t sha256_c::sOp_bsig1( uint32_t x ) noexcept {
    return sOp_rotr( x, 6 ) ^ sOp_rotr( x, 11 ) ^ sOp_rotr( x, 25 );
}

//==============================================================================================================================
constexpr uint32_t sha256_c::sOp_ssig0( uint32_t x ) noexcept {
    return sOp_rotr( x, 7 ) ^ sOp_rotr( x, 18 ) ^ ( x >> 3 );
}

//==============================================================================================================================
constexpr uint32_t sha256_c::sOp_ssig1( uint32_t x ) noexcept {
    return sOp_rotr( x, 17 ) ^ sOp_rotr( x, 19 ) ^ ( x >> 10 );
}

//==============================================================================================================================
constexpr void sha256_c::sUnpack32( uint8_t out[ 4 ], uint32_t in ) noexcept {
    out[ 3 ] = static_cast< uint8_t >( in );
    out[ 2 ] = static_cast< uint8_t >( in >> 8  );
    out[ 1 ] = static_cast< uint8_t >( in >> 16 );
    out[ 0 ] = static_cast< uint8_t >( in >> 24 );
}

//==============================================================================================================================
constexpr void sha256_c::sUnpack64( uint8_t out[ 8 ], uint64_t in ) noexcept {
    out[ 7 ] = static_cast< uint8_t >( in );
    out[ 6 ] = static_cast< uint8_t >( in >> 8  );
    out[ 5 ] = static_cast< uint8_t >( in >> 16 );
    out[ 4 ] = static_cast< uint8_t >( in >> 24 );
    out[ 3 ] = static_cast< uint8_t >( in >> 32 );
    out[ 2 ] = static_cast< uint8_t >( in >> 40 );
    out[ 1 ] = static_cast< uint8_t >( in >> 48 );
    out[ 0 ] = static_cast< uint8_t >( in >> 56 );
}

//==============================================================================================================================
constexpr uint32_t sha256_c::sPack32( const uint8_t cIn[ 4 ] ) noexcept {
    return static_cast< uint32_t >( cIn[ 3 ] )
         | static_cast< uint32_t >( cIn[ 2 ] ) << 8
         | static_cast< uint32_t >( cIn[ 1 ] ) << 16
         | static_cast< uint32_t >( cIn[ 0 ] ) << 24;
}

//==============================================================================================================================
inline void sha256_c::mTransform( const uint8_t* cpMsg, uint64_t blockNum ) {
    std::array< uint32_t, 64 > msgSchedule; // The words of the message schedule.
    std::array< uint32_t, 8 >  workingVars; // The working variables.

    for ( uint64_t i { 0 }; i < blockNum; ++i ) {

        // 1. Prepare the message schedule.
        for ( size_t j { 0 }; j < 16; ++j ) {
            msgSchedule[ j ] = sPack32( &cpMsg[ i * sizeof( block_t ) + ( j << 2 ) ] );
        }
        for ( size_t j { 16 }; j < 64; ++j ) {
            msgSchedule[ j ] = sOp_ssig1( msgSchedule[ j - 2  ] ) + msgSchedule[ j - 7  ]
                             + sOp_ssig0( msgSchedule[ j - 15 ] ) + msgSchedule[ j - 16 ];
        }

        // 2. Initialize the working variables.
        memcpy( workingVars.data(), mHashVals.data(), sizeof( workingVars ) );

        // 3. Perform the main hash computation.
        for ( size_t j { 0 }; j < 64; ++j ) {
            const uint32_t temp1 {
                workingVars[ 7 ] + sOp_bsig1( workingVars[ 4 ] )
                + sOp_ch( workingVars[ 4 ], workingVars[ 5 ], workingVars[ 6 ] ) + scCubeRoots[ j ] + msgSchedule[ j ]
            };
            const uint32_t temp2 {
                sOp_bsig0( workingVars[ 0 ] ) + sOp_maj( workingVars[ 0 ], workingVars[ 1 ], workingVars[ 2 ] )
            };

            workingVars[ 7 ] = workingVars[ 6 ];
            workingVars[ 6 ] = workingVars[ 5 ];
            workingVars[ 5 ] = workingVars[ 4 ];
            workingVars[ 4 ] = workingVars[ 3 ] + temp1;
            workingVars[ 3 ] = workingVars[ 2 ];
            workingVars[ 2 ] = workingVars[ 1 ];
            workingVars[ 1 ] = workingVars[ 0 ];
            workingVars[ 0 ] = temp1 + temp2;
        }

        // 4. Compute the intermediate hash value.
        for ( size_t j { 0 }; j < 8; ++j ) {
            mHashVals[ j ] += workingVars[ j ];
        }
    }
}

//==============================================================================================================================
inline sha256_c::hash_t sha256_c::operator()( const uint8_t* cpMessage, uint64_t msgSize ) {
    return mDo( cpMessage, msgSize );
}

//==============================================================================================================================
inline sha256_c::hash_t sha256_c::mDo( const uint8_t* cpMessage, uint64_t msgSize ) {
    constexpr uint64_t cBlockSize { sizeof( block_t ) };

    const uint64_t cFullBlockNum     { msgSize / cBlockSize };
    const uint64_t cRemainingMsgSize { msgSize % cBlockSize };

    std::vector< uint8_t > padding;

    // One byte for 0x80 and eight bytes for the message size value, i.e. add 9 bytes.
    if ( cRemainingMsgSize + 9 > cBlockSize ) {
        padding.resize( 2 * cBlockSize, 0 );
    } else {
        padding.resize( cBlockSize, 0 );
    }

    // If 'cFullBlockNum * cBlockSize == msgSize' then 'cRemainingMsgSize' will be 0, so 'memcpy' won't cause an error.
    memcpy( padding.data(), &cpMessage[ cFullBlockNum * cBlockSize ], cRemainingMsgSize );
    padding.at( cRemainingMsgSize ) = 0x80;
    sUnpack64( &padding.at( padding.size() - 8 ), msgSize << 3 );

    mTransform( cpMessage, cFullBlockNum );
    mTransform( padding.data(), padding.size() / cBlockSize );

    hash_t hash;

    for ( size_t iHashVal { 0 }; iHashVal < 8; ++iHashVal ) {
        sUnpack32( &hash.at( iHashVal << 2 ), mHashVals[ iHashVal ] );
    }

    return hash;
}

//==============================================================================================================================
inline sha256_c::hash_t sha256( const std::string& cInput ) {
    return sha256_c()( reinterpret_cast< const uint8_t* >( cInput.c_str() ), cInput.size() );
}

//==============================================================================================================================
inline std::string bytesToHexStr( const sha256_c::hash_t& cHash ) {
    std::stringstream out;

    for ( unsigned int byte : cHash ) {
        out << std::hex << std::setw( 2 ) << std::setfill( '0' ) << byte;
    }

    return out.str();
}

} // namespace smd::hash
