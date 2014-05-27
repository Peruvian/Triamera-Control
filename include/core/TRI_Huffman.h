#ifndef TRI_HUFFMAN_H
#define TRI_HUFFMAN_H

#include <stdio.h>
#include <string.h>

namespace TRIMERA
{
    struct msCodigo
    {
        unsigned char *cCod;
        unsigned int iTam;
    };

    class ArchOut
    {
        FILE *mfArch;
        unsigned char mIndex;
        unsigned char mByte;
    public:
        ArchOut(unsigned char *cNom,unsigned char*cAtrib);
        ~ArchOut();
        bool Error(){return !mfArch;}
        void Bit(unsigned int iVal);
        void Buffer(unsigned char*cBuf, unsigned int iBits);
    };

    class TRI_Huffman
    {

    public:
        TRI_Huffman();
        ~TRI_Huffman();
        bool Comprimir(char *cNombreArchivo);
    };
}
#endif // TRI_HUFFMAN_H
