#include "../include/realfile.h"

RealFile::RealFile(const std::string &path, FileSignatureInfo *fsi)
    : AbstractFile(path)
{
    this->fsi = fsi;
}

RealFile::~RealFile()
{

}

FileSignatureInfo &RealFile::getFileSignatureInfo()
{
    return (*fsi);
}
