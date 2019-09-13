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
// Description:        Implementation of KeyMessageHandler 
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 26 Sep 2012  yang            Original Version
//*****************************************************************

#include "key-message-handler.h"
#include "common/check.h"

using namespace std;

KeyMessageHandler::KeyMessageHandler(ostream* log) : MessageHandler(log) {
}

void KeyMessageHandler::Send(istream* is) {

  client_stdin()->Write("KEY");
  string line;
  while (is->good()) {
    getline(*is, line);
    if (line != "") {
      client_stdin()->Write(line);
    }
  }
  CHECK(is->eof() == true);
  client_stdin()->Write("ENDKEY");
  timer().Start();


  client_stdout()->Read(&line);
  CHECK(line == "KEY") << "Unexpected key message header: " << line;

  double elapsed_time = timer().Elapsed(); //The timer should stop once the client begins sending the key, indicating it has fully computed it
  *log() << "KEYGEN " << elapsed_time << endl;
  

  server_stdin()->Write("KEY");
  while(line != "ENDKEY") {;
    client_stdout()->Read(&line);
    server_stdin()->Write(line);
  }
  CHECK(line == "ENDKEY") << "Unexpected key message footer: " << line;

}

