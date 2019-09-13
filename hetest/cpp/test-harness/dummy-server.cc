
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include "common/logging.h"
#include "common/statics.h"
#include "common/check.h"
#include "common/string-algo.h"

using namespace std;

// This is a really dumb baseline client. It simply outputs a public key of 0,
// echos the unencrypted input as encrypted output, and echos the encrypted
// result as unencrypted result.
int main(int argc, const char* argv[]) {
  Initialize();
  string line;

  ofstream file("log.txt");
  while( getline(cin, line) ) {
      file << line;
  }
  return 0;
}
