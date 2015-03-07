#include "bitHelpers.h"
///////////////////////////////////////////////////
//
// This file as a 32 and a 64 bit set of basic bit functions
// 
//


///////////////////////////////////////////////////
//
// basic fast 32 bit helper functions
//

int bitCount(Bit32 w)
{
   w = (0x55555555UL & w) + (0x55555555UL & (w>> 1));
   w = (0x33333333UL & w) + (0x33333333UL & (w>> 2));
   w += (w>> 4);
   w &= 0x0f0f0f0fUL;
   w += (w>> 8);
   return (int)((w + (w>>16)) & 0x1f);
}

// Binary Reflected Gray Code
Bit32 bitGray(Bit32 n)
{
    return n ^ (n>>1);
}


// Inverse Binary Reflected Gray Code
Bit32 bitDeGray(Bit32 n)
{
    n ^= (n>>1);
    n ^= (n>>2);
    n ^= (n>>4);
    n ^= (n>>8);
    return n ^ (n>>16);
}


// the Hamming distance between two strings
Bit32 hamming(Bit32 a, Bit32 b)
{
    return bitCount(a ^ b);
}


// Are there at least 5 bits set?
Bit32 are5BitsSet(Bit32 i)
{
    i &= (i-1);
    i &= (i-1);
    i &= (i-1);
    return i & (i-1);
}

// Are there at least 4 bits set?
Bit32 are4BitsSet(Bit32 i)
{
    i &= (i-1);
    i &= (i-1);
    return i & (i-1);
}

// Are there at least 3 bits set?
Bit32 are3BitsSet(Bit32 i)
{
    i &= (i-1);
    return i & (i-1);
}

// Are there at least 2 bits set?
Bit32 are2BitsSet(Bit32 i)
{
    return i & (i-1);
}


// rotate left (amount must be 31 or smaller)
Bit32 bitRotateLeft(Bit32 n, int amount)
{
    return (n<<amount) | (n>>(32 - amount));
}


// rotate right (amount must be 31 or smaller)
Bit32 bitRotateRight(Bit32 n, int amount)
{
    return (n>>amount) | (n<<(32 - amount));
}


// returns the parity of the bitstring.
// this works well for larger numbers of bits set (>3 bits?)
Bit32 bitParity(Bit32 n)
{
   n ^= n>>1;
   n ^= n>>2;
   n ^= n>>4;
   n ^= n>>8;
   return (n ^ n>>16) & 0x1;
}


// produce a right justified mask of bits that contains the
// bits in the given string
Bit32 rightMask(Bit32 n)
{
   n |= n>>1;
   n |= n>>2;
   n |= n>>4;
   n |= n>>8;
   return n | (n>>16);
}


///////////////////////////////////////////////////
//
// basic fast 64 bit helper functions
//

int bitCount(Bit64 w)
{
   w = (0x5555555555555555ULL & w) + (0x5555555555555555ULL & (w>> 1));
   w = (0x3333333333333333ULL & w) + (0x3333333333333333ULL & (w>> 2));
   w += (w>> 4);
   w &= 0x0f0f0f0f0f0f0f0fULL;
   w += (w>> 8);
   w += (w>>16);
   w &= 0x000000ff000000ffULL;
   return (int)(w + (w>>32));
}


// Binary Reflected Gray Code
Bit64 bitGray(Bit64 n)
{
    return n ^ (n>>1);
}


// Inverse Binary Reflected Gray Code
Bit64 bitDeGray(Bit64 n)
{
    n ^= (n>>1);
    n ^= (n>>2);
    n ^= (n>>4);
    n ^= (n>>8);
    n ^= (n>>16);
    return n ^ (n>>32);
}

// the Hamming distance between two strings
Bit64 hamming(Bit64 a, Bit64 b)
{
    return bitCount(a ^ b);
}


// Are there at least 5 bits set?
Bit64 are5BitsSet(Bit64 i)
{
    i &= (i-1);
    i &= (i-1);
    i &= (i-1);
    return i & (i-1);
}

// Are there at least 4 bits set?
Bit64 are4BitsSet(Bit64 i)
{
    i &= (i-1);
    i &= (i-1);
    return i & (i-1);
}

// Are there at least 3 bits set?
Bit64 are3BitsSet(Bit64 i)
{
    i &= (i-1);
    return i & (i-1);
}

// Are there at least 2 bits set?
Bit64 are2BitsSet(Bit64 i)
{
    return i & (i-1);
}


// rotate left (amount must be 63 or smaller)
Bit64 bitRotateLeft(Bit64 n, int amount)
{
    return (n<<amount) | (n>>(64 - amount));
}


// rotate right (amount must be 31 or smaller)
Bit64 bitRotateRight(Bit64 n, int amount)
{
    return (n>>amount) | (n<<(64 - amount));
}


// returns the parity of the bitstring.
// this works well for larger numbers of bits set (>3 bits?)
Bit64 bitParity(Bit64 n)
{
   n ^= n>>1;
   n ^= n>>2;
   n ^= n>>4;
   n ^= n>>8;
   n ^= n>>16;
   return (n ^ n>>32) & 0x1;
}

// produce a right justified mask of bits that contains the
// bits in the given string
Bit64 rightMask(Bit64 n)
{
   n |= n>>1;
   n |= n>>2;
   n |= n>>4;
   n |= n>>8;
   n |= n>>16;
   return n | n>>32;
}