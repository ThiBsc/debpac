#ifndef ABSTRACTFILE_H
#define ABSTRACTFILE_H

#include <string>

class AbstractFile
{

public:
    AbstractFile(const std::string& path, AbstractFile *parent = nullptr);
    virtual ~AbstractFile() = 0;
    std::string getPath();
    bool hasParent();
    AbstractFile *getParent();
    void setParent(AbstractFile *parent);

protected:
    AbstractFile *parent;
    std::string path;
};

#endif // ABSTRACTFILE_H
