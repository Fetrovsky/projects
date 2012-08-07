// Copyright (C) 2012 Fetrovsky (Daniel Valencia)
//
// This module provides functions to manipulate
// and serialize bits and bytes within types.
//

#ifndef BASE__MARSHALLING_H_
#define BASE__MARSHALLING_H_

#include <stdint.h>

#include <algorithm>
#include <stdexcept>
#include <string>

#include <base/endianness.h>


namespace marshalling {
// Isolates eight contiguous bits and turns them into an unsigned integer.
//
// Parameters:
//      value: the original value.
//      i: the index in octets of the starting bit.
//         Indexing starts at the LSB.
template<typename T>
inline uint8_t byte_at(T value, int i) {
  return uint8_t( value >> (i<<3) );
}

// Splits a value into octets.  The byte ordering is selected
// by using the argument little_endian.
template<typename T>
inline void serialize(T value,
                      Endianness endianness,
                      uint8_t* buffer) {
  int start = sizeof(T) - 1, end = -1, delta = -1;

  if (endianness == kLittleEndian) {
    swap(++start, ++end);
    delta = -delta;
  } else if (endianness != kBigEndian) {
       // Only support Little- and Big- endian for now.
       throw new std::runtime_error("Unsupprted endianness.");
  }

  for (int i = start, j = 0; i != end; i+= delta, ++j)
    buffer[j] = (byte_at(value, i));
}

// Builds an int16 from a buffer using the specified byte ordering.
inline
int16_t build_int16(uint8_t const* buf, bool little_endian = false) {
  return little_endian?
    (int16_t(buf[1]) << 8) | uint16_t(buf[0]):
    (int16_t(buf[0]) << 8) | uint16_t(buf[1]);
}

// Builds a uint16 from a buffer using the specified byte ordering.
inline
uint16_t build_uint16(uint8_t const* buf, bool little_endian = false) {
  return little_endian?
    (uint16_t(buf[1]) << 8) | uint16_t(buf[0]):
    (uint16_t(buf[0]) << 8) | uint16_t(buf[1]);
}

// Builds an int32 from a buffer using the specified byte ordering.
inline
int32_t build_int32(uint8_t const* buf, bool little_endian = false) {
  return little_endian?
    (int32_t(build_int16(&buf[2], little_endian)) << 16) |
        build_uint16(&buf[0], little_endian):
    (int32_t(build_int16(&buf[0], little_endian)) << 16) |
        build_uint16(&buf[2], little_endian);
}

// Builds a uint32 from a buffer using the specified byte ordering.
inline
uint32_t build_uint32(uint8_t const* buf, bool little_endian = false) {
  return little_endian?
    (uint32_t(build_uint16(&buf[2], little_endian)) << 16) |
        build_uint16(&buf[0], little_endian):
    (uint32_t(build_uint16(&buf[0], little_endian)) << 16) |
        build_uint16(&buf[2], little_endian);
}

}  // namespace marshalling

#endif  // BASE__MARSHALLING_H_

