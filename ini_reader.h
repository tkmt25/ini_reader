#pragma once

#include <string>

class ini_reader final
{
 public:
  ini_reader(const std::string& filename): filename(filename)
  {}
  ini_reader(const ini_reader&) = delete;
  ini_reader& operator=(const ini_reader&) = delete;
  
  bool read(const std::string& section, const std::string& key, std::string& value);
  bool read(const std::string& section, const std::string& key, int& value);
  
 private:
  std::string filename;
};
