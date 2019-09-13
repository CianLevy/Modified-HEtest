#include "helib-client.h"
#include <string>
#include "common/check.h"
#include <memory>


using namespace std;

void HelibClient::Setup(){
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
    unsigned long p = params.at(1); 
    unsigned long r = params.at(2);
    unsigned long L = params.at(3);
    unsigned long c = params.at(4);
    unsigned long w = params.at(5);
    unsigned long d = params.at(6);
    unsigned long s = params.at(7);

    unsigned long m = FindM(k, L, c, p, d, s, 0);


    context = boost::make_unique<FHEcontext>(m, p, r);
    buildModChain(*context, L, c);

  
}

void HelibClient::GenerateKeys(){
    Setup();

    secret_key = boost::make_unique<FHESecKey>(*context);
    secret_key->GenSecKey();

    addSome1DMatrices(*secret_key); //Compute key-switching matrices

    public_key = boost::make_unique<FHEPubKey>(*secret_key);


    //Send the public key to the server
    cout << "KEY\n";
    writeContextBase(cout, *context);
    cout << *context << endl;
    cout << *public_key << endl;
    cout << "ENDKEY\n";
}

vector<int> HelibClient::ReadInput(){
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

void HelibClient::Encrypt(){
    vector<int> plaintxts = ReadInput();

    const EncryptedArray& ea = *(context->ea);

    stringstream ciphertxts;

    Ctxt c(*public_key);
    PlaintextArray p(ea);

    cout << "EDATA" << endl;
    cout << plaintxts.size() << endl;

    for (size_t i = 0; i < plaintxts.size(); i++){
        encode(ea, p, plaintxts.at(i));
        ea.encrypt(c, *public_key, p);
        cout << c << endl;
    }

    cout << "ENDEDATA" << endl;

}

void HelibClient::Decrypt(){
    string line;
    Ctxt result(*public_key);

    cin >> result;

    getline(cin, line);
    getline(cin, line);
    CHECK(line != "" && line == "ENDEDATA") << "Unexpected EDATA footer" << line;

    const EncryptedArray& ea = *(context->ea);
    vector<long> decrypted(ea.size());

    ea.decrypt(result, *secret_key, decrypted);

    cout << "PDATA" << endl;
    stringstream s;
    s << "[";
    
    for (size_t i = 0; i < decrypted.size(); i++)
        s << decrypted.at(i) << ((i != decrypted.size() - 1) ? "," : "]");

    cout << s.str() << endl;
    cout << "ENDPDATA" << endl;
} 