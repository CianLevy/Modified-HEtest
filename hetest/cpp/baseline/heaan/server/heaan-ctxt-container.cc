#include "heaan-ctxt-container.h"
#include "../heaan-serialiser.h"

using namespace std;

CtxtContainer CtxtContainer::operator+ (const CtxtContainer& rhs){
    shared_ptr<CtxtContainer> result = make_shared<CtxtContainer>();
    //CtxtContainer* result = new CtxtContainer();
    Ciphertext r(rhs.c);
    context_data.scheme->add(result->c, c,r);

    return *result;
}

CtxtContainer CtxtContainer::operator* (const CtxtContainer& rhs){
    shared_ptr<CtxtContainer> result = make_shared<CtxtContainer>();
    Ciphertext r(rhs.c);
    context_data.scheme->mult(result->c, c, r);

    return *result;
}


CtxtContainer CtxtContainer::operator+ (const ConstantVal& rhs) {
    shared_ptr<CtxtContainer> result = make_shared<CtxtContainer>();
    context_data.scheme->addConst(result->c, c, (double)rhs, context_data.logp);

    return *result;
}

CtxtContainer CtxtContainer::operator* (const ConstantVal& rhs) {
    shared_ptr<CtxtContainer> result = make_shared<CtxtContainer>();
    context_data.scheme->multByConst(result->c, c, (double)rhs, context_data.logp);

    return *result;
}


std::istream& operator >> (std::istream &in, CtxtContainer::ContextContainer &c){
    c.logp = 0;
    in >> c.logp;

    Ring ring; 
    SecretKey sk(ring);
    c.scheme = make_shared<Scheme>(sk, ring); //scheme has no null constructor. Without modifying the library this the only way to ensure construction
    in >> *(c.scheme);

    return in;
}

std::istream& operator >> (std::istream &in, CtxtContainer &c){
    in >> c.c;

    return in;
}