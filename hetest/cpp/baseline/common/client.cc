#include "client.h"
#include "common/logging.h"
#include "common/check.h"
#include <iostream>


void Client::Start() {
  std::string line;
  while (std::getline(std::cin, line)) {
    if (line == "KEY") {
      GenerateKeys();
    } else if (line == "PDATA") {
      Encrypt();
    } else if (line == "EDATA") {
      Decrypt();
    } else {
      LOG(FATAL) << "Unexpected input on client's stdin: " << line;
    }
  }
}
