#pragma once
#include <iostream>
#include "HEAAN.h"


ostream & operator << (ostream &out, const Ciphertext &c);
istream& operator >> (std::istream &in, Ciphertext &c);


ostream & operator << (ostream &out, const Key &c);
istream& operator >> (std::istream &in, Key &c);

ostream & operator << (ostream &out, const Scheme &c);
istream& operator >> (std::istream &in, Scheme &c);