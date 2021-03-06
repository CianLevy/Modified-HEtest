//*****************************************************************
// Copyright (c) 2013 Massachusetts Institute of Technology
//
// Developed exclusively at US Government expense under US Air Force contract
// FA8721-05-C-002. The rights of the United States Government to use, modify,
// reproduce, release, perform, display or disclose this computer software and
// computer software documentation in whole or in part, in any manner and for
// any purpose whatsoever, and to have or authorize others to do so, are
// Unrestricted and Unlimited.
//
// Licensed for use under the BSD License as described in the BSD-LICENSE.txt
// file in the root directory of this release.
//  
// Project:            SPAR
// Authors:            Yang
// Description:        A dummy client for harness testing 
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 26 Sep 2012  yang            Original Version
//*****************************************************************

#include <cstdlib>
#include <string>
#include <iostream>
#include "common/logging.h"
#include "common/statics.h"
#include "common/check.h"
#include "common/string-algo.h"

#include <vector>

using namespace std;

vector<int> ReadInput();

// This is a really dumb baseline client. It simply outputs a public key of 0,
// echos the unencrypted input as encrypted output, and echos the encrypted
// result as unencrypted result.
int main(int argc, const char* argv[]) {
  Initialize();
  string line;
  while( getline(cin, line) ) {
    if (line == "KEY") {
      // consume the security param
      getline(cin, line);
      while (line != "ENDKEY") {
        getline(cin, line);
      }
      CHECK(line == "ENDKEY") << "Unexpected key message footer" << line;
      // return the public key
      cout << "KEY\n0\nENDKEY" << endl;
    } else if (line == "PDATA") {
     
      vector<int> input = ReadInput();

      cout << "EDATA\n" << input.size() << "\n";
      for (auto i : input)
        cout << i << endl;
        
      cout << "ENDEDATA" << endl;
    } else if (line == "EDATA") {
      string temp;
      // consume encrypted-data
      getline(cin, temp);
      CHECK(temp.size() > 0) << "Did not receive an encrypted output";
      int size = SafeAtoi(temp);
      char output[size];
      cin.read(output, size);
      // consume the message footer
      getline(cin, line);
      getline(cin, line);
      CHECK(line == "ENDEDATA") << "Unexpected EDATA footer" << line;
      cout << "PDATA\n";
      cout.write(output, size);
      cout << "\nENDPDATA" << endl;
    } 
  }
  return 0;
}

vector<int> ReadInput(){
    string line;
    vector<int> inputV;

    getline(cin, line);

    if (line[0] == '['){
        int previous = 1;

        for (size_t i = 1; i < line.size(); i++){
            if (line[i] == ',' || line[i] == ']'){
                inputV.push_back(stoi(line.substr(previous, i - previous)));
                previous  = i + 1;
            }
        }
    }
    getline(cin, line);
    CHECK(line == "ENDPDATA") << "Unexpected PDATA footer" << line;
    return inputV;
}