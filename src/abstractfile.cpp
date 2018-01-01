#include "abstractfile.h"

AbstractFile::AbstractFile(const std::string &name, AbstractFile *parent)
{
    this->name = name;
    this->parent = parent;
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
    this->name = name;
}
