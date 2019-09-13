#pragma once

#include "baseline/common/client.h"
#include "seal/seal.h"
#include <memory>
#include <vector>
#include <boost/make_unique.hpp>

class SEALClient : public Client {

public:
    SEALClient() {}
private:
    virtual void GenerateKeys() override;
    virtual void Encrypt() override;
    virtual void Decrypt() override;

    void Setup();
    std::vector<int> ReadInput();

    std::shared_ptr<seal::SEALContext> context;
    std::unique_ptr<seal::PublicKey> public_key;
    std::unique_ptr<seal::SecretKey> secret_key;
    unsigned long poly_modulus_degree;
    unsigned long plain_modulus;
};
