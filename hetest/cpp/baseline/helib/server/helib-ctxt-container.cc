#include "helib-ctxt-container.h"

CtxtContainer CtxtContainer::operator+ (const CtxtContainer& rhs) const{

    CtxtContainer c_new(*this);
    c_new.c += rhs.c;
    
    return c_new;
}

CtxtContainer CtxtContainer::operator* (const CtxtContainer& rhs) const{

    CtxtContainer c_new(*this);
    c_new.c *= rhs.c;

    return c_new;
}


CtxtContainer CtxtContainer::operator+ (const constant_value& rhs) {
    const EncryptedArray& ea = *(context_data.context->ea);
    CtxtContainer c_new(*this);
    PlaintextArray rhs_ptxt(ea);
    encode(ea, rhs_ptxt, rhs);

    NTL::ZZX rhs_poly;
    ea.encode(rhs_poly, rhs_ptxt);

    c_new.c.addConstant(rhs_poly);

    return c_new;
}

CtxtContainer CtxtContainer::operator* (const constant_value& rhs) {
    const EncryptedArray& ea = *(context_data.context->ea);
    CtxtContainer c_new(*this);
    PlaintextArray rhs_ptxt(ea);
    encode(ea, rhs_ptxt, rhs);

    NTL::ZZX rhs_poly;
    ea.encode(rhs_poly, rhs_ptxt);

    c_new.c.multByConstant(rhs_poly);
    
    return c_new;
}


std::istream& operator >> (std::istream &in, ContextContainer &c){
    //std::cout << "Attempting to read HElib context\n";

    unsigned long m, p, r;
    std::vector<long> gen, ords;

    readContextBase(in, m, p, r, gen, ords);

    c.context = std::make_shared<FHEcontext>(m, p, r, gen, ords);
    in >> (*(c.context));

    c.public_key = std::make_shared<FHEPubKey>(*(c.context));
    in >> *(c.public_key);

    //c.ea = std::make_shared<EncryptedArray>(EncryptedArray(*(c.context->ea)));

    return in;
}