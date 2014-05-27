#include <../include/core/TRI_Huffman.h>

TRIMERA::ArchOut::ArchOut(unsigned char *cNom, unsigned char *cAtrib)
{
    mfArch = fopen((char *)cNom, (char *)cAtrib);
    mIndex = 0;
    mByte = 0;
}

TRIMERA::ArchOut::~ArchOut()
{
    if (mIndex)
            fputc(mByte, mfArch);
    fclose(mfArch);
}

void TRIMERA::ArchOut::Bit(unsigned int iVal)
{
    mByte = mByte|(iVal<<mIndex++);
    if (mIndex==8)
    {
        fputc(mByte, mfArch);
        mByte = NULL;
        mIndex = 0;
    }
}

void TRIMERA::ArchOut::Buffer(unsigned char *cBuf, unsigned int iBits)
{
    unsigned char lcB[35], lcMask = 0xFF;
    unsigned short *lsPunt;
    unsigned short lsTmp1;
    unsigned short lsTmp2;
    unsigned int lnBytes;
    unsigned int lnBitsExt;
    lnBytes = (iBits+mIndex)/8;
    lnBitsExt = (iBits+mIndex)%8;
    memcpy(lcB,cBuf,(iBits/8)+((iBits%8)?1:0));
    lsPunt = (unsigned short*)&lcB[0];
    lsTmp1 = *lsPunt;
    lsTmp1 = lsTmp1 << mIndex;
    lsTmp1 = lsTmp1|(unsigned short) (mByte&(lcMask>>(8-mIndex)));





}

bool TRIMERA::TRI_Huffman::Comprimir(char *cNombreArchivo)
{
    FILE *lfArchIn;
    unsigned char *ulcNomArchOut;


}
