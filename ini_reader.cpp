#include <sstream>
#include <fstream>
#include <string>
#include <regex>
#include "ini_reader.h"

// for debug
#include <iostream>

using namespace std;

const string SECTION_PATTERN = R"(^\s*\[\s*(\S+)\s*\]\s*$)";
const string KEY_PATTERN     = R"(^\s*(\S+)\s*=\s*\"*(.+?)\"*\s*$)";

/**
 * �R�����g(�u;�v�ȍ~)���폜���܂�
 * @param [in,out] line 1�s�̕�����
 * @return �Ȃ�
 */
static inline void remove_comment(string& line)
{
  string::size_type i = line.find(";");
  if ( i != string::npos ) {
    line.erase(i, line.length() - i);
  }
}

/**
 * �w�肵���Z�N�V����,�L�[���當����l��ǂݍ��݂܂�
 * @param [in]  section �Z�N�V������
 * @param [in]  key     �L�[��
 * @param [out] value   ������l
 * @return ���������A���s
 */
bool ini_reader::read(const string& section, const string& key, string& value)
{
  regex match_section(SECTION_PATTERN);
  regex match_key(KEY_PATTERN);
  string line;
  ifstream stream(this->filename, std::ios::in);


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

template <>
int ini_reader::parse(const string& text)
{
  return stoi(text);;
}

template <>
bool ini_reader::parse(const string& text)
{
  if (text == "true") {
    return true;
  }
  else if (text == "false") {
    return false;
  }
  throw exception();
}

template <>
uint8_t ini_reader::parse(const string& text)
{
  return stoi(text, nullptr, 16);
}
