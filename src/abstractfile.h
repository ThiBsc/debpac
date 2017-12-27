#ifndef ABSTRACTFILE_H
#define ABSTRACTFILE_H

#include <string>

class AbstractFile
{

public:
    AbstractFile(const std::string& name, AbstractFile *parent = nullptr);
    virtual ~AbstractFile() = 0;
    std::string getName();
    bool hasParent();
    AbstractFile *getParent();
    void setParent(AbstractFile *parent);

protected:
    AbstractFile *parent;
    std::string name;
};

#endif // ABSTRACTFILE_H
