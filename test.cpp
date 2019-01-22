#include <iostream>
#include <string>
#include "ini_reader.h"

using namespace std;

int main(int argc, char **argv)
{
  ini_reader reader("test.ini");
  string value;
  int value2;

  bool result = reader.read("Test2", "AllowWin", value);
  
  cout << "result " << result << endl;
  if ( result ) {
    cout << "read value = " << value << endl;
  }
}
