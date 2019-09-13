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
// Description:        Implementation of InputMessageHandler 
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 26 Sep 2012  yang            Original Version
//*****************************************************************

#include "input-message-handler.h"
#include "common/check.h"
#include "common/string-algo.h"

using namespace std;

InputMessageHandler::InputMessageHandler(ostream* log)
: MessageHandler(log) {
}

void InputMessageHandler::Send(std::istream* input_stream) {
    string line; 

    client_stdin()->Write("PDATA");
    while (input_stream->good()) {
        getline(*input_stream, line);
        if (line != "") {
            client_stdin()->Write(line);
        }
    }
    CHECK(input_stream->eof() == true);
    client_stdin()->Write("ENDPDATA");
    timer().Start(); // Start the timer when the client has recieved all the data to encrypt

    // We expect an EDATA message from the client.
    client_stdout()->Read(&line);
    CHECK(line == "EDATA") 
        << " Received unexpected input message header from client: " << line;


    server_stdin()->Write("EDATA");
    while(line != "ENDEDATA") {
        client_stdout()->Read(&line);
        server_stdin()->Write(line);
    }
    double encrypt_time = timer().Elapsed(); // Stop the timer when the client returns 'ENDEDATA' indicating it has encrypted the data
    *log() << "ENCRYPT " << encrypt_time << endl;

    timer().Start(); // Start the timer and wait for the server to return the encrypted result of circuit evaluation

    // We expect an EDATA message from the server
    server_stdout()->Read(&line);
    CHECK(line == "EDATA") 
        << "Received unexpected input message header from server: " << line;

    double eval_time = timer().Elapsed(); // Stop the timer when the server begins to return the result
    *log() << "EVALUATION " << eval_time << endl;

  
    client_stdin()->Write("EDATA");
    while(line != "ENDEDATA") {
        server_stdout()->Read(&line);
        client_stdin()->Write(line);
    }
    timer().Start(); // Start the decryption timer when all the encrypted data has been sent


    CHECK(line == "ENDEDATA") 
        << "Received unexpected input message footer from server: " << line;

    stringstream result_msg_stream;

    // We expect a PDATA message from the client.
    client_stdout()->Read(&line);
    CHECK(line == "PDATA") << "Unexpected input message header: " << line;
    client_stdout()->Read(&line);
    *log() << "RESULT " << line << endl;
    client_stdout()->Read(&line);
    CHECK(line == "ENDPDATA") << "Unexpected input message footer " << line;
    double decrypt_time = timer().Elapsed();
    *log() << "DECRYPT " << decrypt_time << endl;
}
