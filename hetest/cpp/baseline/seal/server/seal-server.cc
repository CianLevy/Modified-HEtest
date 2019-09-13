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
#include "seal-circuit.h"
#include "circuit-parser.h"
#include "seal-server.h"
#include "common/check.h"
#include "common/logging.h"
#include "seal-ctxt-container.h"

#include <fstream>

using namespace std;

SEALServer::SEALServer(SEALCircuitParser* p) : Baseline(p) {}

CtxtContainer::ContextContainer CtxtContainer::context_data;

// Read the input into a string and evaluate on the stored circuit.
// Even though the output is unencrypted, we respond with a EDATA message
// to remain consistent with how the SUT server behaves.
void SEALServer::ReadInputAndEvaluate() {
  string line;

  getline(cin, line);
  int size = atoi(line.c_str());
  char input[line.size()];
  strcpy(input, line.c_str());


  CtxtContainer output = circuit_->Evaluate(input);

  getline(cin, line);
  getline(cin, line);
  CHECK(line == "ENDEDATA") << "Unexpected input message footer" << line;

  cout << "EDATA" << endl;
  output.c.save(cout);
  cout << endl;
  cout << "ENDEDATA" << endl;
}

void SEALServer::StorePublicKey(){
  cin >> (CtxtContainer::context_data);
  string line;

  getline(cin, line);
  while(line != "ENDKEY")
    getline(cin, line);
  
  CHECK(line == "ENDKEY") << "Unexpected input message footer" << line;
}


