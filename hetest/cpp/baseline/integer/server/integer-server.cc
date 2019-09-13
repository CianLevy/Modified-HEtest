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
// Description:        IBM baseline 
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 25 Sep 2012  yang            Original Version
//*****************************************************************

#include <iostream>
#include "gates.h"
#include "integer-circuit.h"
#include "circuit-parser.h"
#include "integer-server.h"
#include "common/check.h"
#include "common/logging.h"

using namespace std;

IntegerServer::IntegerServer(IntegerCircuitParser* p) : Baseline(p) {}

// Read the input into a string and evaluate on the stored circuit.
// Even though the output is unencrypted, we respond with a EDATA message
// to remain consistent with how the SUT server behaves.
void IntegerServer::ReadInputAndEvaluate() {
  string line;
  // This is the size line
  getline(cin, line);
  int size = atoi(line.c_str());
  char input[line.size()];
  strcpy(input, line.c_str());

  CtxtContainer output = circuit_->Evaluate(input);


  // This should be the ENDEDATA footer
  getline(cin, line);
  getline(cin, line);
  CHECK(line == "ENDEDATA") << "Unexpected input message footer" << line;


  std::stringstream result;
  result << output;
  cout << "EDATA\n" << result.str().length() << "\n" << result.str() << "\nENDEDATA" << endl; //Test harness probably expects to be told number of chars not bytes
}