#include "../include/abstractfile.h"

AbstractFile::AbstractFile(const std::string &path, AbstractFile *parent)
{
    this->path = path;
    this->parent = parent;
}

AbstractFile::~AbstractFile()
{

}

std::string AbstractFile::getPath()
{
    return this->path;
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
