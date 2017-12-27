#include "realfile.h"
#include "filesignatureinfo.hpp"

RealFile::RealFile(const std::string &name, FileSignatureInfo *fsi)
    : AbstractFile(name)
{
    this->fsi = fsi;
    if (this->fsi == nullptr){
        this->fsi = new FileSignatureInfo("inexistantfile");
        fromFileSystem = false;
    } else {
        fromFileSystem = true;
    }
}

RealFile::~RealFile()
{
    if (!fromFileSystem)
        delete fsi;
}

FileSignatureInfo &RealFile::getFileSignatureInfo()
{
    return (*fsi);
}
