#include "abstractfile.h"

AbstractFile::AbstractFile(const std::string &name, bool canRename, AbstractFile *parent)
{
    this->name = name;
    this->parent = parent;
    this->canRename = canRename;
}

AbstractFile::~AbstractFile()
{

}

std::string AbstractFile::getName()
{
    return this->name;
}

bool AbstractFile::hasParent()
{
    return parent != nullptr;
}

AbstractFile *AbstractFile::getParent()
{
    return parent;
}

void AbstractFile::setParent(AbstractFile *parent)
{
    this->parent = parent;
}

void AbstractFile::setName(const std::string &name)
{
    if (canRename)
        this->name = name;
}

void AbstractFile::setCanRename(bool canRename)
{
    this->canRename = canRename;
}
