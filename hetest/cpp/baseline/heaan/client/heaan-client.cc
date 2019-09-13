#include "heaan-client.h"
#include "../heaan-serialiser.h"
#include <string>
#include "common/check.h"
#include <memory>


using namespace std;
using namespace NTL;

void HEAANClient::Setup(){
    string line = "";
    string delimiter = "=";
    vector<unsigned long> params;
    getline(cin, line);
    
    while(line != "ENDKEY"){
        size_t pos = line.find(delimiter);
        params.push_back(stoi(line.substr(pos + 1)));
        getline(cin, line);
    }

    k = params.at(0);
    logq = params.at(1);
    logp = params.at(2);
}

void HEAANClient::GenerateKeys(){
    Setup();
	srand(time(NULL));
	SetNumThreads(1); //Not a fair comparison to use multiple threads
	ring = std::make_shared<Ring>();
	secret_key = boost::make_unique<SecretKey>(*ring);
	scheme = std::make_shared<Scheme>(*secret_key, *ring);

    cout << "KEY" << endl;
    cout << logp << endl;
    cout << *scheme << endl;
    cout << "ENDKEY" << endl;

}

vector<int> HEAANClient::ReadInput(){
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

void HEAANClient::Encrypt(){
    vector<int> plaintxts = ReadInput();

    cout << "EDATA" << endl;
    cout << plaintxts.size() << endl;

    for (auto i : plaintxts){
        Plaintext ptxt(logp, logq, 1);
        double val = (double)i;
        scheme->encodeSingle(ptxt, val, logp, logq);

        Ciphertext c(logp, logq, 1);
        scheme->encryptMsg(c, ptxt);
        cout << c << endl;
    }

    cout << "ENDEDATA" << endl;

}

void HEAANClient::Decrypt(){
    Ciphertext result;
    cin >> result;

    complex<double> result_decrypted = scheme->decryptSingle(*secret_key, result);

    cout << "PDATA" << endl;
    cout << result_decrypted << endl;
    cout << "ENDPDATA" << endl;
}