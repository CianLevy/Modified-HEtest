#pragma once

#include <vector>
#include <iostream>
#include "common/check.h"
#include "seal/seal.h"


typedef long ConstantVal;
class CtxtContainer{
    public:
    class ContextContainer{
    public: 

    ContextContainer(){}
    friend std::istream& operator >> (std::istream &in, ContextContainer &c);
    std::shared_ptr<seal::Evaluator> evaluator;
    std::shared_ptr<seal::SEALContext> context;
    std::shared_ptr<seal::PublicKey> public_key;
    
};

        static ContextContainer context_data;
        seal::Ciphertext c;

        CtxtContainer() : c(){}

        CtxtContainer(const CtxtContainer& c_) :
            c(c_.c) {};


        CtxtContainer operator+ (const CtxtContainer& rhs);
        CtxtContainer operator* (const CtxtContainer& rhs);
        CtxtContainer operator+ (const ConstantVal& rhs);
        CtxtContainer operator* (const ConstantVal& rhs);
        friend std::istream& operator >> (std::istream &in, CtxtContainer &c);
};