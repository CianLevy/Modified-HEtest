#pragma once

#include "baseline/common/client.h"
#include <helib/FHE.h>
#include <helib/EncryptedArray.h>
#include <memory>
#include <vector>
#include <boost/make_unique.hpp>

class HelibClient : public Client {

public:
    HelibClient() {}
private:


    virtual void GenerateKeys() override;
    virtual void Encrypt() override;
    virtual void Decrypt() override;

    void Setup();
    std::vector<int> ReadInput();

    std::unique_ptr<FHEcontext> context;
    std::unique_ptr<FHEPubKey> public_key;
    std::unique_ptr<FHESecKey> secret_key;
    //const EncryptedArray& ea;
};
