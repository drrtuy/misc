#ifndef HBITSTRING

class BitString
{
    private: 
        char *_bits;
        int _length;
    public:
        void init(int _length, const char *bitString);
        void create(int _length);
        char *outPut(const char *msg);
        void stdoutPut(const char *msg);
        BitString And(const BitString &bitString);
        BitString Or(const BitString &bitString);
        BitString Xor(const BitString &bitString);
        BitString Not();
};

#endif
