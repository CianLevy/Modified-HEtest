#pragma once
#include <vector>
#include <iostream>
#include "common/check.h"
#include <helib/FHE.h>
#include <helib/EncryptedArray.h>


class ContextContainer{
    public: 

    ContextContainer(){}
    friend std::istream& operator >> (std::istream &in, ContextContainer &c);
    std::shared_ptr<FHEcontext> context;
    std::shared_ptr<FHEPubKey> public_key;
    
};

typedef long constant_value;
class CtxtContainer{
    public:
        static ContextContainer context_data;
        Ctxt c;

        CtxtContainer() :
            c(*(context_data.public_key)) {}

        CtxtContainer(const CtxtContainer& c_) :
            c(c_.c) {};


        CtxtContainer operator+ (const CtxtContainer& rhs) const;
        CtxtContainer operator* (const CtxtContainer& rhs) const;
        CtxtContainer operator+ (const constant_value& rhs);
        CtxtContainer operator* (const constant_value& rhs);

};
