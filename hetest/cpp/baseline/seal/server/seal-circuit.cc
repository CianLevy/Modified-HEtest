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
// Description:        Implementation of CircuitParser 
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 23 Sep 2012  yang            Original Version
//*****************************************************************

#include "seal-circuit.h"
#include "common/check.h"
#include "common/string-algo.h"

using namespace std;

CtxtContainer Circuit::Evaluate(char* input) {
  output_gate_->Reset();
  Parse(input);
  return output_gate_->Evaluate();
}

void Circuit::Parse(char* input) {
  int previous_index = 0;
  unsigned int wire_index = 0;

  int size = atoi(input);

  for (int i = 0; i < size; i++) {
    CtxtContainer ctxt;
    cin >> ctxt;
    wires_->at(i)->SetInput(ctxt);
  }
}

