// Copyright (C) 2011 Fetrovsky (Daniel Valencia)

#ifndef BOUNDED_VALUE_H_INCLUDED_
#define BOUNDED_VALUE_H_INCLUDED_

#include <stdint.h>
#include <limits>

template<typename T>
class BoundedValue {
     private:
          T _min;
          T _max;
          T _value;

     public:
          typedef std::pair<T, T> RawPair;

          static T bound(T const& value, T const& min, T const& max)
          { return std::min(std::max(value, min), max); }

          BoundedValue(T const& value = T(),
                       T const& min = T(0),
                       T const& max = std::numeric_limits<T>::max()):
              _min(min),
              _max(max),
              _value(value) {}

          T bound(T const& value) { return bound(value, _min, _max); }
          operator const T&() const { return _value; }

          T bound() { return _value = bound(_value); }

          T const& min() const { return _min; }
          T const& max() const { return _max; }

          void set_limits(RawPair const& limits)
          { set_limits(limits.first, limits.second); }

          void set_limits(T const& min, T const& max) {
               _min = min;
               _max = max;
               bound();
          }

          void set_min(T const& min) {
               _min = min;
               bound();
          }

          void set_max(T const& max) {
               _max = max;
               bound();
          }

          BoundedValue& operator=(BoundedValue const& other) {
               _min = other.min();
               _max = other.max();
               return ((*this) = other._value);
          }

          BoundedValue& operator=(T const& value) {
               _value = bound(value);
               return *this;
          }

          BoundedValue operator+(T const& amount) {
               BoundedValue result = *this;
               result+= amount;
               return result;
          }

          BoundedValue operator-(T const& amount) {
               BoundedValue result = *this;
               result-= amount;
               return result;
          }

          BoundedValue& operator+=(T const& amount) {
               _value = bound(_value + amount);
               return *this;
          }

          BoundedValue& operator-=(T const& amount) {
               _value = bound(_value - amount);
               return *this;
          }
};

typedef BoundedValue<int>          BoundedInt;
typedef BoundedValue<char>         BoundedChar;
typedef BoundedValue<long>         BoundedLong;
typedef BoundedValue<float>        BoundedFloat;
typedef BoundedValue<double>       BoundedDouble;
typedef BoundedValue<long double>  BoundedLongDouble;
typedef BoundedValue<int8_t>       BoundedInt8;
typedef BoundedValue<int16_t>      BoundedInt16;
typedef BoundedValue<int32_t>      BoundedInt32;
typedef BoundedValue<int64_t>      BoundedInt64;

#endif  // BOUNDED_VALUE_H_INCLUDED_
