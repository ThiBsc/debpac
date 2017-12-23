#ifndef FOLDER_H
#define FOLDER_H

#include "abstractfile.h"
#include <vector>

class RealFile;

class Folder : public AbstractFile
{

public:
    Folder(const std::string& path);
    ~Folder();
    Folder& add(Folder* file);
    void add(RealFile* file);
    int count(bool recursive);
    AbstractFile *child(int row);
    template<class T>
    T getChild(std::string name)
    {
        T ret;
        for (AbstractFile *af : tree){
            if(T f = dynamic_cast<T>(af)) {
               if (af->getPath() == name){
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
