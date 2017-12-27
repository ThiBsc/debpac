#include "folder.h"
#include "realfile.h"

Folder::Folder(const std::string &path)
    : AbstractFile(path)
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

void Folder::renameFolder(const std::string &name, bool recursive)
{
    const std::string old_path = path;
    path = name;
    if (recursive){
        /*for (AbstractFile *af : tree){
            if(Folder* f = dynamic_cast<Folder*>(af)) {
               if (old_path == f->getPath()){
                   f->renameFolder(name, recursive);
               }
            }
        }*/
    }
}

AbstractFile *Folder::child(int row)
{
    return tree.at(row);
}

