#include "seal-ctxt-container.h"

using namespace seal;
using namespace std;

struct membuf : std::streambuf
{
    membuf(char* begin, char* end) {
        this->setg(begin, begin, end);
    }
};


CtxtContainer CtxtContainer::operator+ (const CtxtContainer& rhs){
    CtxtContainer result;
    context_data.evaluator->add(c, rhs.c, result.c); //Can in place be used?

    return result;
}

CtxtContainer CtxtContainer::operator* (const CtxtContainer& rhs){
    CtxtContainer result;
    context_data.evaluator->multiply(c, rhs.c, result.c);

    return result;
}


CtxtContainer CtxtContainer::operator+ (const ConstantVal& rhs) {
    CtxtContainer result;
    Plaintext plain(to_string(rhs));

    context_data.evaluator->add_plain(c, plain, result.c);

    return result;
}

CtxtContainer CtxtContainer::operator* (const ConstantVal& rhs) {
    CtxtContainer result;
    Plaintext plain(to_string(rhs));

    context_data.evaluator->multiply_plain(c, plain, result.c);

    return result;
}


std::istream& operator >> (std::istream &in, CtxtContainer::ContextContainer &c){

    unsigned long poly_modulus_degree, plain_modulus;
    string line;
    getline(in, line);
    poly_modulus_degree = stoi(line);
    getline(in, line);
    plain_modulus = stoi(line);

    EncryptionParameters parms(scheme_type::BFV);
    parms.set_poly_modulus_degree(poly_modulus_degree);
    parms.set_coeff_modulus(CoeffModulus::BFVDefault(poly_modulus_degree));
    parms.set_plain_modulus(plain_modulus);

    c.context = SEALContext::Create(parms);

    c.public_key = make_shared<PublicKey>();
    c.public_key->load(c.context, in);

    c.evaluator = make_shared<Evaluator>(c.context);

    return in;
}

std::istream& operator >> (std::istream &in, CtxtContainer &c){
    c.c.load(c.context_data.context, in);

    return in;
}