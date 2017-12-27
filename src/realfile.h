#ifndef REALFILE_H
#define REALFILE_H

#include "abstractfile.h"

class FileSignatureInfo;

class RealFile : public AbstractFile
{
public:
    RealFile(const std::string& name, FileSignatureInfo *fsi = nullptr);
    ~RealFile();
    FileSignatureInfo& getFileSignatureInfo();

private:
    bool fromFileSystem;
    FileSignatureInfo *fsi;
};

#endif // REALFILE_H
