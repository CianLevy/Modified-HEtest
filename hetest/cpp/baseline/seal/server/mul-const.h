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
// Description:        An IBM constant multiplication gate 
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 17 Sep 2012  yang            Original Version
//*****************************************************************


#ifndef CPP_BASELINE_TA2_IBM_MUL_CONST_H_
#define CPP_BASELINE_TA2_IBM_MUL_CONST_H_

#include "unary-gate.h"

class MulConst : public UnaryGate {
 public:
  // Returns the bit-wise AND operation of the constant and input
  virtual CtxtContainer EvaluateImpl() {
    return input()->Evaluate() * constant();
  }
};

#endif
