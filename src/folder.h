#ifndef FOLDER_H
#define FOLDER_H

#include "abstractfile.h"
#include <vector>

class RealFile;

/**
 * @brief The Folder class
 * Sepcialization of the AbstractFile to manage folder
 */

class Folder : public AbstractFile
{

public:
    Folder(const std::string& name, bool canRename = true);
    ~Folder();
    Folder& add(Folder* file);
    void add(RealFile* file);
    int count(bool recursive);
    Folder *containFolder(const std::string& name, bool recursive);
    RealFile *containFile(const std::string& name);
    void renameFolder(const std::string& oldname, const std::string& name, bool recursive);
    AbstractFile *child(int row);
    int child(AbstractFile *af);
    bool remove(AbstractFile *afile, bool recursive);
    template<class T>
    T getChild(std::string name)
    {
        T ret = nullptr;
        for (AbstractFile *af : tree){
            if(T f = dynamic_cast<T>(af)) {
               if (af->getName() == name){
                   ret = f;
                   break;
               }
            }
        }
        return ret;
    }

private:
    std::vector<AbstractFile *> tree;

};

#endif // FOLDER_H
