// Copyright (C) 2011, Daniel Valencia (Fetrovsky)

#ifndef DEBUGGING_H_INCLUDED
#define DEBUGGING_H_INCLUDED

#include <iostream>
#include <sstream>
#include <typeinfo>

#define PREFIX_LOG(prefix, x) \
             (x << '[' << __FILE__ << ':' << prefix << ':' << __LINE__ << "] ")

#define LOG(x) (x << '[' << __FILE__ << ':' << __LINE__ << "] ")
#define OUT LOG(std::cout)
#define ERROR (LOG(std::cerr) << " ERROR: ")
#define PREFIX_ERROR(prefix) (PREFIX_LOG(prefix, std::cerr) << " ERROR: ")

#define SHOW(v) (OUT << #v << ": " << (v) << std::endl)
#define SHOW_IN_HEX(s) OUT << #s << ": "; show_in_hex(s);
#define INVOKE(_) OUT << "Invoking " << #_ << "." << std::endl;_()

template<typename T>
inline void show_in_hex(T const& s) {
     typedef typename T::const_iterator Iter;
     for (Iter i = s.begin(); i != s.end(); ++i)
          std::cout << std::hex << uint64_t(*i) << ' ';
     std::cout << std::dec << std::endl;
}

template<typename T>
inline std::string PrepareRow(std::string const& name, T const& value) {
     std::stringstream ss;
     ss << std::string("     ") 
        << name <<  std::string(": ") 
        << value << '\n';
     return ss.str();
}

template<typename T>
inline std::string PrepareValue(std::string const& name,
                         T const& value) {
      return PrepareRow("name", name) +
             PrepareRow("type", typeid(value).name()) +
             PrepareRow("value", value);
}

#endif  // DEBUGGING_H_INCLUDED

