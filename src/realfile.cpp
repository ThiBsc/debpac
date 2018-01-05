#include "realfile.h"
#include "filesignatureinfo.hpp"

RealFile::RealFile(const std::string &name, bool canRename, FileSignatureInfo *fsi)
    : AbstractFile(name, canRename)
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
    delete fsi;
}

FileSignatureInfo &RealFile::getFileSignatureInfo()
{
    return (*fsi);
}
