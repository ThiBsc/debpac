#ifndef REALFILE_H
#define REALFILE_H

#include "abstractfile.h"

class FileSignatureInfo;

/**
 * @brief The RealFile class
 * Sepcialization of the AbstractFile to manage file
 */

class RealFile : public AbstractFile
{
public:
    RealFile(const std::string& name, bool canRename, FileSignatureInfo *fsi = nullptr);
    ~RealFile();
    FileSignatureInfo& getFileSignatureInfo();

private:
    bool fromFileSystem;
    FileSignatureInfo *fsi;
};

#endif // REALFILE_H
