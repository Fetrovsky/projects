// Copyright (C) 2011, Fetrovsky(Daniel Valencia)

#ifndef INT_BASE_H_INCLUDED
#define INT_BASE_H_INCLUDED

#include <stdint.h>
#include <stdexcept>
#include <string>

template<bool> struct StaticAssert;

template<> struct StaticAssert<true> {};

// Digits: Values  Digit Count  Total Digits
//          0..9      <10>          <10>
//          A..Z      <26>          <36>
//          _          <1>          <37>
//          a..z      <26>          <63>
//          ~          <1>          <64>
template<uint8_t kBase>
class IntBase {
     public:
          IntBase(std::string s): _n(0L) {
               for (uint64_t i = 0; i < s.length(); ++i) {
                    _n*= kBase;
                    _n+= ToValue(s[i]);
               }
          }

          IntBase(uint64_t n): _n(n) {}
          operator uint64_t() { return _n; }

          operator std::string() {
               if (_n == 0) return "0";
               std::string value;
               uint64_t v = _n;

               while (v > 0) {
                     push_front(value, ToChar(v % kBase));
                    v/= kBase;
               }

               return value;
          }

     private:
          uint64_t ToValue(char digit) {
               uint64_t value;

               if (digit == '~') {
                    value = 63;
               } else if (digit == '_') {
                    value = 36;
               } else if (digit >= 'a' && digit <= 'z') {
                    value = digit - 'a' + 37;
               } else if (digit >= 'A' && digit <= 'Z') {
                    value = digit - 'A' + 10;
               } else if (digit >= '0' && digit <= '9') {
                    value = digit - '0';
               }

               if (value < kBase) return value;

               throw std::runtime_error(std::string("Invalid digit '") +
                                        digit +
                                        std::string("' for base ") +
                                        std::string(IntBase<10>(kBase)));
               }

          char ToChar(uint64_t digit) {
               if (digit == 63) {
                    return '~';
               } else if (digit >= 37) {
                    digit-= 37;
                    return char('a' + digit);
               } else if (digit == 36) {
                    return '_';
               } else if (digit >= 10) {
                    digit -= 10;
                    return char('A' + digit);
               }

               return char('0' + digit);
          }

          void push_front(std::string& str, char c) {
               str.insert(str.begin(), c);
          }

          // Limit kBase to 64.
          typedef StaticAssert<(kBase >= 1) && (kBase <= 64)> Is_kBase_Valid;

          uint64_t _n;
};

#endif  // INT_BASE_H_INCLUDED

