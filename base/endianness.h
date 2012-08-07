// Copyright (C) 2011 Fetrovsky (Daniel Valencia)

#ifndef BASE__ENDIANNESS_H_INCLUDED_
#define BASE__ENDIANNESS_H_INCLUDED_

#include <cstring>

enum Endianness { kLittleEndian, kMiddleEndian, kBigEndian, kUnknownEndian };

// TODO(Fetrovsky): This assumes octet-based systems.  Make generic.
static Endianness FigureOutMyEndianness() {
     uint32_t value = 0x0a0b0c0d;
     uint8_t* s = reinterpret_cast<uint8_t*>(&value);
     if (!std::memcmp(s, "\xd\xc\xb\xa", 4)) return kLittleEndian;
     if (!std::memcmp(s, "\xb\xa\xd\xc", 4)) return kMiddleEndian;
     if (!std::memcmp(s, "\xa\xb\xc\xd", 4)) return kBigEndian;
     return kUnknownEndian;
}

#endif  // BASE__ENDIANNESS_H_INCLUDED_
