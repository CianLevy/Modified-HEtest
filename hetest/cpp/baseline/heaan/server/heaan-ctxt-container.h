#pragma once

#include <vector>
#include <iostream>
#include "common/check.h"
#include "HEAAN.h"



typedef long ConstantVal;
class CtxtContainer{
    public:

        class ContextContainer{
        public: 

            ContextContainer(){}
            friend std::istream& operator >> (std::istream &in, CtxtContainer::ContextContainer &c);
            std::shared_ptr<Scheme> scheme;
            long int logp;

        };

        static ContextContainer context_data;
        Ciphertext c;

        CtxtContainer() : c(){}

        CtxtContainer(const CtxtContainer& c_) : c(c_.c) {};


        CtxtContainer operator+ (const CtxtContainer& rhs);
        CtxtContainer operator* (const CtxtContainer& rhs);
        CtxtContainer operator+ (const ConstantVal& rhs);
        CtxtContainer operator* (const ConstantVal& rhs);
        friend std::istream& operator >> (std::istream &in, CtxtContainer &c);
};