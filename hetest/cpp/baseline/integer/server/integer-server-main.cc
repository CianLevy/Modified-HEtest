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
// Description:        Main executable for IBM baseline 
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 25 Sep 2012  yang            Original Version
//*****************************************************************

#include "circuit-parser.h"
#include "integer-server.h"
#include "common/statics.h"

int main(int argc, char** argv) {
  Initialize();
  IntegerServer baseline(new IntegerCircuitParser());
  baseline.Start();
  return 0;
}

