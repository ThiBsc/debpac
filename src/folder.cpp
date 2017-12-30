#include "folder.h"
#include "realfile.h"

Folder::Folder(const std::string &name)
    : AbstractFile(name)
{

}

Folder::~Folder()
{
    for (AbstractFile *af : tree)
        delete af;
    tree.clear();
}

Folder& Folder::add(Folder *file)
{
    file->setParent(this);
    tree.push_back(file);
    return (*file);
}

void Folder::add(RealFile *file)
{
    file->setParent(this);
    tree.push_back(file);
}

int Folder::count(bool recursive)
{
    int ret = tree.size();
    if (recursive){
        for (AbstractFile *af : tree){
            if(Folder* f = dynamic_cast<Folder*>(af)) {
               ret += f->count(recursive);
            }
        }
    }
    return ret;
}

bool Folder::containFolder(const std::string &name, bool recursive)
{
    bool ret = false;
    for (AbstractFile *af : tree){
        if(Folder* f = dynamic_cast<Folder*>(af)) {
           if (name == f->getName())
               ret = true;
           if (!ret && recursive)
               ret = f->containFolder(name, recursive);
        }
        if (ret)
            break;
    }
    return ret;
}

bool Folder::containFile(const std::string &name)
{
    bool ret = false;
    for (AbstractFile *af : tree){
        if(RealFile* f = dynamic_cast<RealFile*>(af)) {
           if (name == f->getName())
               ret = true;
        }
        if (ret)
            break;
    }
    return ret;
}

void Folder::renameFolder(const std::string &oldname, const std::string &name, bool recursive)
{
    if (oldname == getName())
        this->name = name;
    if (recursive){
        for (AbstractFile *af : tree){
            if(Folder* f = dynamic_cast<Folder*>(af)) {
               if (f->containFolder(oldname, recursive))
                   f->renameFolder(oldname, name, recursive);
               else if (oldname == f->getName())
                   f->renameFolder(oldname, name, false);
            }
        }
    }
}

AbstractFile *Folder::child(int row)
{
    return tree.at(row);
}

