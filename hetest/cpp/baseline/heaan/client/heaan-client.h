#pragma once

#include "baseline/common/client.h"
#include "HEAAN.h"
#include <memory>
#include <vector>
#include <boost/make_unique.hpp>

class HEAANClient : public Client {

public:
    HEAANClient() {}
private:
    virtual void GenerateKeys() override;
    virtual void Encrypt() override;
    virtual void Decrypt() override;

    void Setup();
    std::vector<int> ReadInput();

    std::unique_ptr<SecretKey> secret_key;
    std::shared_ptr<Ring> ring;
    std::shared_ptr<Scheme> scheme;

    unsigned long k;
    unsigned long logq;
    unsigned long logp; 
};
