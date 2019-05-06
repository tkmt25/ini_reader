#pragma once

#include <string>
#include <utility>
#include <vector>
#include <sstream>

using std::string;
using std::vector;

class ini_reader final
{
public:
  ini_reader(const string& filename): filename(filename){}
  ini_reader(const ini_reader&) = delete;
  ini_reader& operator=(const ini_reader&) = delete;

  bool read(const string& section, const string& key, string& value);
  
  template <typename T>
  bool read(const string& section, const string& key, T& value)
  {
    string _value;
    if( !read(section, key, _value) ) {
      return false;
    }

    try {
      value = this->parse<T>(_value);
    } catch ( ... ) {
      return false;
    }
  
    return true;
  }
  
  template <typename T>
  bool read(const string& section, const string& key, vector<T>& value)
  {
    string _value;
    if ( !read(section, key, _value) ) {
      return false;
    }

    value.clear();
    stringstream str(_value);
    string item;
    const char delim = ',';
    while ( getline(str, item, delim) ) {
      if ( !item.empty() ) {
	try {
	  value.push_back( this->parse<T>(item) );
	} catch( ... ){
	  return false;
	}
      }
    }

    return true;
  }
 
  
private:
  string filename;

  template <typename T>
  T parse(const string& text);
};
