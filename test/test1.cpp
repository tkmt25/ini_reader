#include "gtest\gtest.h"
#include <string>
#include <iostream>
#include <fstream>
#include "..\ini_reader.h"

using namespace std;

void CreateTestIni(char *text)
{
  ofstream out("tmp.ini");
  out << text;
}

// 1-1
TEST(ini_reader_test, test1_1)
{
  CreateTestIni(R"(
[test]
val=1
)");
  
  ini_reader ini("tmp.ini");
  int val;
  
  ini.read("test", "val", val);

  ASSERT_EQ(val, 1);
}

// 1-2
TEST(ini_reader_test, test1_2)
{
  CreateTestIni(R"(
[test]
val="hello"
)");
  
  ini_reader ini("tmp.ini");
  string val;
  
  ini.read("test", "val", val);

  ASSERT_EQ(val, "hello");
}

// 1-3
TEST(ini_reader_test, test1_3)
{
  CreateTestIni(R"(
[test]
val=   true
)");
  
  ini_reader ini("tmp.ini");
  bool val;
  
  ini.read("test", "val", val);

  ASSERT_EQ(val, true);
}

// 1-4
TEST(ini_reader_test, test1_4)
{
  CreateTestIni(R"(
[test\test]
val="hello"
)");
  
  ini_reader ini("tmp.ini");
  string val;
  
  ini.read("test\\test", "val", val);

  ASSERT_EQ(val, "hello");
}


// 2-1
TEST(ini_reader_test, test2_1)
{
  CreateTestIni(R"(
[test]
val=1,2,3
)");
  
  ini_reader ini("tmp.ini");
  vector<int> val{3,2,1};
  
  ini.read("test", "val", val);

  ASSERT_EQ(val[0], 1);
  ASSERT_EQ(val[1], 2);
  ASSERT_EQ(val[2], 3);
}

// 2-2
TEST(ini_reader_test, test2_2)
{
  CreateTestIni(R"(
[test]
val=0x11,0x22
)");
  
  ini_reader ini("tmp.ini");
  vector<uint8_t> val;
  
  ini.read("test", "val", val);

  ASSERT_EQ(val[0], 0x11);
  ASSERT_EQ(val[1], 0x22);
}

// 3-1
TEST(ini_reader_test, test3_1)
{
  CreateTestIni(R"(
[test]
val=0x11,X
)");
  
  ini_reader ini("tmp.ini");
  vector<uint8_t> val;
  

  ASSERT_EQ(ini.read("test", "val", val), false);
}

// 3-2
TEST(ini_reader_test, test3_2)
{
  CreateTestIni(R"(
 [test]
;val = "bb"
 val = ".* " ; aaa
 val = "cc"
)");
  
  ini_reader ini("tmp.ini");
  string val;

  ini.read("test", "val", val);

  ASSERT_EQ(val, ".* ");
}

// 3-3
TEST(ini_reader_test, test3_3)
{
  stringstream ss;

  for (int i = 0; i < 1000; i++) {
    ss << "[test" << i << "]" << endl;
    ss << "val"<< i << "=1" <<endl;
  }

  string& s = ss.str();
  char *c = s.c_str();
  CreateTestIni(c);
  
  ini_reader ini("tmp.ini");
  string val;

  ini.read("test999", "val999", val);

  ASSERT_EQ(val, 1);
}

