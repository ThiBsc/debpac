#include "folder.h"
#include "realfile.h"
#include <algorithm>

Folder::Folder(const std::string &name, bool canRename)
    : AbstractFile(name, canRename)
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

Folder *Folder::containFolder(const std::string &name, bool recursive)
{
    Folder *ret = nullptr;
    for (AbstractFile *af : tree){
        if(Folder* f = dynamic_cast<Folder*>(af)) {
           if (name == f->getName())
               ret = f;
           if (!ret && recursive)
               ret = f->containFolder(name, recursive);
        }
        if (ret)
            break;
    }
    return ret;
}

RealFile *Folder::containFile(const std::string &name)
{
    RealFile *ret = nullptr;
    for (AbstractFile *af : tree){
        if(RealFile* f = dynamic_cast<RealFile*>(af)) {
           if (name == f->getName())
               ret = f;
        }
        if (ret)
            break;
    }
    return ret;
}

void Folder::renameFolder(const std::string &oldname, const std::string &name, bool recursive)
{
    if (oldname == getName())
        setName(name);
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

int Folder::child(AbstractFile *af)
{
    int ret = -1;
    for (ulong i=0; i<tree.size() && ret==-1; i++){
        if (tree[i] == af){
            ret = i;
        }
    }
    return ret;
}

bool Folder::remove(AbstractFile *afile, bool recursive)
{
    bool ret = false;
    auto it = std::find(tree.begin(), tree.end(), afile);
    if (it != tree.end()){
        tree.erase(it);
        ret = true;
    }
    if (recursive && !ret){
        for (AbstractFile *af : tree){
            if(Folder* f = dynamic_cast<Folder*>(af)) {
               ret = f->remove(afile, recursive);
            }
        }
    }
    return ret;
}

