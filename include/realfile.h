#ifndef REALFILE_H
#define REALFILE_H

#include "abstractfile.h"

class FileSignatureInfo;

class RealFile : public AbstractFile
{
public:
    RealFile(const std::string& path, FileSignatureInfo *fsi);
    ~RealFile();
    FileSignatureInfo& getFileSignatureInfo();

private:
    FileSignatureInfo *fsi;
};

#endif // REALFILE_H
