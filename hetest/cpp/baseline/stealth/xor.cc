//****************************************************************
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
// Project:        SPAR
// Authors:        Yang
// Description:    Implementation of XOR gate
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 07 Aug 2012   Yang           Original Version
//****************************************************************

#include "xor.h"
#include "common/check.h"

bool Xor::EvaluateImpl(bool short_circuit) {
  CHECK(NumInputs() >= 2) << "Not enough inputs";
  unsigned int sum = 0;
  for (int i = 0; i < NumInputs(); ++i) {
    if (GetInput(i)->Evaluate(short_circuit)) {
      ++sum;
    }
  }
  return sum % 2;
}


