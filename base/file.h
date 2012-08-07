// Copyright (C) 2011 Fetrovsky (Daniel Valencia)

#ifndef FILE_H_INCLUDED_
#define FILE_H_INCLUDED_

#include <stdint.h>

#include <fstream>
#include <iostream>
#include <string>


namespace file {
     size_t size_of(std::istream& stream) {
          uint64_t pos = stream.tellg();
          stream.seekg(0, std::ios::end);
          uint64_t size = stream.tellg();
          stream.seekg(pos, std::ios::beg);
          return size;
     }

     size_t size_of(std::string const& name) {
          std::ifstream stream(name.c_str(), std::ios::binary);
          return size_of(stream);
     }

     std::string read(std::string const& name) {
          std::ifstream stream(name.c_str(), std::ios::binary);
          std::string result(size_of(stream), '\0');
          for (size_t i = 0; i < result.size(); ++i)
               result[i] = stream.get();
          return result;
     }
}

#endif  // FILE_H_INCLUDED_
