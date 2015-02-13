#ifndef BITHELPERSH
#define BITHELPERSH

#define Bit64 unsigned long long int
#define Bit32 unsigned int

int bitCount(Bit32 w);
Bit32 bitGray(Bit32 n);
Bit32 bitDeGray(Bit32 n);
Bit32 hamming(Bit32 a, Bit32 b);
Bit32 are5BitsSet(Bit32 i);
Bit32 are4BitsSet(Bit32 i);
Bit32 are3BitsSet(Bit32 i);
Bit32 are2BitsSet(Bit32 i);
Bit32 bitRotateLeft(Bit32 n, int amount);
Bit32 bitRotateRight(Bit32 n, int amount);
Bit32 bitParity(Bit32 n);
Bit32 rightMask(Bit32 n);

int bitCount(Bit64 w);
Bit64 bitGray(Bit64 n);
Bit64 bitDeGray(Bit64 n);
Bit64 hamming(Bit64 a, Bit64 b);
Bit64 are5BitsSet(Bit64 i);
Bit64 are4BitsSet(Bit64 i);
Bit64 are3BitsSet(Bit64 i);
Bit64 are2BitsSet(Bit64 i);
Bit64 bitRotateLeft(Bit64 n, int amount);
Bit64 bitRotateRight(Bit64 n, int amount);
Bit64 bitParity(Bit64 n);
Bit64 rightMask(Bit64 n);

#endif