#include <sstream>
#include <fstream>
#include <string>
#include <regex>
#include "ini_reader.h"

// for debug
#include <iostream>

using namespace std;

const string SECTION_PATTERN = R"(^\s*\[\s*(\S+)\s*\]\s*$)";
const string KEY_PATTERN     = R"(^\s*(\S+)\s*=\s*\"*(\S+?)\"*\s*$)";

static inline void remove_comment(string& line)
{
  string::size_type i = line.find(";");
  if ( i != string::npos ) {
    line.erase(i, line.length() - i);
  }
}

bool ini_reader::read(const string& section, const string& key, string& value)
{
  regex match_section(SECTION_PATTERN);
  regex match_key(KEY_PATTERN);
  string line;
  ifstream stream(this->filename);


  while ( getline(stream, line) ) {
    remove_comment(line);
    smatch results;
    
    if ( regex_match(line, results, match_section) &&
	 section.compare(results[1]) == 0 ) {
      
      while ( getline(stream, line) ) {
	remove_comment(line);
	
	if ( regex_match(line, results, match_key) &&
	     key.compare(results[1]) == 0 ) {
	  value = results[2];
	  return true;
	}
	
      }
    }
  }
  return false;
}

bool ini_reader::read(const string& section, const string& key, int& value)
{
  string _value;
  
  if( !read(section, key, _value) ) {
    return false;
  }
  
  try {
    value = stoi(_value);
  } catch ( ... ) {
    return false;
  }
  return true;
}
