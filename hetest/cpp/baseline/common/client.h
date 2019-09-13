#ifndef client
#define client

class Client{

    public:
        void Start();
        Client(){}

    private:
        virtual void GenerateKeys() = 0; //Generate public and private keys. Store private. Send public key to server
        virtual void Encrypt() = 0; //Encrypt the provided input and send the ciphertext to the server
        virtual void Decrypt() = 0; //Decrypt the result and send the plaintext to the test harness
};

#endif