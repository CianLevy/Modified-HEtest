#include "seal-client.h"
#include <string>
#include "common/check.h"
#include <memory>

#include <fstream>

using namespace std;
using namespace seal;

void SEALClient::Setup(){
    string line = "";
    string delimiter = "=";
    vector<unsigned long> params;
    getline(cin, line);
    
    while(line != "ENDKEY"){
        size_t pos = line.find(delimiter);
        params.push_back(stoi(line.substr(pos + 1)));
        getline(cin, line);
    }

    unsigned long k = params.at(0);

    sec_level_type sec_level = sec_level_type::none;

    switch (k){
        case 128:
            sec_level = sec_level_type::tc128;
            break;

        case 192:
            sec_level = sec_level_type::tc192;
            break;

        case 256:
            sec_level = sec_level_type::tc256;
            break;
    }

    poly_modulus_degree = params.at(1);
    plain_modulus = params.at(2);

    EncryptionParameters parms(scheme_type::BFV);
    parms.set_poly_modulus_degree(poly_modulus_degree);
    parms.set_coeff_modulus(CoeffModulus::BFVDefault(poly_modulus_degree));
    parms.set_plain_modulus(plain_modulus);
    
    context = SEALContext::Create(parms, true, sec_level);
}

void SEALClient::GenerateKeys(){
    Setup();

    KeyGenerator keygen(context);

    public_key = boost::make_unique<PublicKey>(keygen.public_key());

    secret_key = boost::make_unique<SecretKey>(keygen.secret_key());

    cout << "KEY" << endl;
    cout << poly_modulus_degree << endl;
    cout << plain_modulus << endl;


    stringstream pkey_buf(ios::in|ios::out);

    public_key->save(cout);


    cout << endl;
    cout << "ENDKEY" << endl;

}

vector<int> SEALClient::ReadInput(){
    string line;
    vector<int> inputV;

    getline(cin, line);

    if (line[0] == '['){
        int previous = 1;

        for (size_t i = 1; i < line.size(); i++){
            if (line[i] == ',' || line[i] == ']'){
                inputV.push_back(stoi(line.substr(previous, i - previous)));
                previous  = i + 1;
            }
        }
    }
    getline(cin, line);
    CHECK(line == "ENDPDATA") << "Unexpected PDATA footer" << line;
    return inputV;
}

void SEALClient::Encrypt(){
    vector<int> plaintxts = ReadInput();
    Encryptor encryptor(context, *public_key);

    cout << "EDATA" << endl;
    cout << plaintxts.size() << endl;

    for (auto i : plaintxts){
        Plaintext plain(to_string(i));
        Ciphertext ctxt;
        encryptor.encrypt(plain, ctxt);

        ctxt.save(cout);
    }

    cout <<  endl;
    cout << "ENDEDATA" << endl;  

}

void SEALClient::Decrypt(){
    string line;

    Ciphertext result;

    result.load(context, cin);

    getline(cin, line);
    getline(cin, line);
    CHECK(line != "" && line == "ENDEDATA") << "Unexpected EDATA footer" << line;

    Plaintext decrypted;

    Decryptor decryptor(context, *secret_key);

    decryptor.decrypt(result, decrypted);


    long decimal_decryption;   
    stringstream ss;
    ss << std::hex << decrypted.to_string(); //to_string returns the hex representation of the result
    ss >> decimal_decryption;

    cout << "PDATA" << endl;
    cout << decimal_decryption << endl;
    cout << "ENDPDATA" << endl;
}