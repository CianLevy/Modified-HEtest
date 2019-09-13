#include "heaan-serialiser.h"


using namespace std;

ostream& operator << (ostream &out, const Ciphertext &c){
    out << c.logp << endl;
    out << c.logq << endl;
    out << c.n << endl;

    for (int i = 0; i < N; i++){
        out << c.ax[i] << endl;
        out << c.bx[i] << ((i != N - 1) ? "\n" : "");
    }
    return out;
}

istream& operator >> (istream &in, Ciphertext &c){
    in >> c.logp;
    in >> c.logq;
    in >> c.n;

    for (int i = 0; i < N; i++){
        in >> c.ax[i];
        in >> c.bx[i];
    }
    return in;
}

ostream & operator << (ostream &out, const Key &c){
    for (int i = 0; i < Nnprimes; i++){
        out << c.rax[i] << endl; //Buffering is done line by line. Without endlines then the entire key would have to be stored in one line
        out << c.rbx[i] << ((i != Nnprimes - 1) ? "\n" : "");     
    }

    return out;
}

istream& operator >> (istream &in, Key &c){
    for (int i = 0; i < Nnprimes; i++){
        in >> c.rax[i];
        in >> c.rbx[i]; 
    }
    return in;
}

ostream & operator << (ostream &out, const Scheme &c){
    Key* multkey = c.keyMap.at(MULTIPLICATION);
    out << *multkey;
    return out;
}

istream& operator >> (std::istream &in, Scheme &c){
    Key* multkey = new Key();
    in >> *multkey;

    c.keyMap.insert(pair<long, Key*>(MULTIPLICATION, multkey));

    return in;
}