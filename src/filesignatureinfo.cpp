#include "../include/filesignatureinfo.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

/**
* According to:
* https://en.wikipedia.org/wiki/List_of_file_signatures
*/
std::map<std::string, std::tuple<FileSignatureInfo::Category, std::string, std::string, std::string> > FileSignatureInfo::tab_info =
{
  {"edabeedb",          std::tuple<FileSignatureInfo::Category, std::string, std::string, std::string>(FileSignatureInfo::PACKAGE, "rpm", "RedHat Package Manager (RPM) package", "....")},
  {"00000100",          std::tuple<FileSignatureInfo::Category, std::string, std::string, std::string>(FileSignatureInfo::IMAGE, "ico", "Computer icon ecoded in ICO file format", "....")},
  {"425a68",            std::tuple<FileSignatureInfo::Category, std::string, std::string, std::string>(FileSignatureInfo::ARCHIVE, "bz2", "Compressed file using Bzip2 algorithm", "BZh")},
  {"474946383761",      std::tuple<FileSignatureInfo::Category, std::string, std::string, std::string>(FileSignatureInfo::IMAGE, "gif", "Image file encoded in the Graphics Interchange Format (GIF)", "GIF87a")},
  {"474946383961",      std::tuple<FileSignatureInfo::Category, std::string, std::string, std::string>(FileSignatureInfo::IMAGE, "gif", "Image file encoded in the Graphics Interchange Format (GIF)", "GIF89a")},
  {"89504e470d0a1a0a",  std::tuple<FileSignatureInfo::Category, std::string, std::string, std::string>(FileSignatureInfo::IMAGE, "png", "Image encoded in the Protable Network Graphics format", ".PNG....")},
  {"3c3f786d6c20",      std::tuple<FileSignatureInfo::Category, std::string, std::string, std::string>(FileSignatureInfo::TEXT, "xml", "eXtensible Markup Language when using the ASCII character encoding", "<?xml")},
  {"213c617263683e",    std::tuple<FileSignatureInfo::Category, std::string, std::string, std::string>(FileSignatureInfo::PACKAGE, "deb", "linux deb file", "!<arch>.")},
  {"664C6143",          std::tuple<FileSignatureInfo::Category, std::string, std::string, std::string>(FileSignatureInfo::AUDIO, "flac", "Free Lossless Audio Codec", "fLaC")},
  {"7f454c46",          std::tuple<FileSignatureInfo::Category, std::string, std::string, std::string>(FileSignatureInfo::BINARY, "", "Executable and Linkable Format", ".ELF")}
};

FileSignatureInfo::FileSignatureInfo(std::string path)
{
    set_file(path);
}

FileSignatureInfo::~FileSignatureInfo()
{

}

void FileSignatureInfo::set_file(std::string path)
{
    this->path = path;
    this->extension = this->hex_signature = this->description = this->iso_8859_1 = "?";
    std::ifstream file(path, std::ios::binary);
    if (file.is_open()){
        //file >> std::noskipws;
        char c;
        std::ostringstream s;
        int nhex=0;
        while (file.get(c) && nhex<12){
            s << std::setfill('0') << std::setw(2) << std::hex << (int)c;
            nhex++;
        }
        file.close();
        this->hex_signature = s.str();
        find_info();
    } else {
        this->description = "Can't open file";
    }
}

std::string FileSignatureInfo::getPath()
{
    return this->path;
}

std::string FileSignatureInfo::getExtension()
{
    return this->extension;
}

std::string FileSignatureInfo::getHex_signature()
{
    return this->hex_signature;
}

std::string FileSignatureInfo::getDescription()
{
    return this->description;
}

std::string FileSignatureInfo::getIso_8859_1()
{
    return this->iso_8859_1;
}

FileSignatureInfo::Category FileSignatureInfo::getCategory()
{
    return this->category;
}

std::string FileSignatureInfo::to_string()
{
    std::string ret = "File: " + this->path + "\n";
    ret += this->hex_signature + " " + this->extension + " " + this->iso_8859_1 + "\n";
    ret += this->description;
    return ret;
}

std::ostream& operator<<(std::ostream& os, FileSignatureInfo& obj)
{
    os << obj.to_string();
    return os;
}

void FileSignatureInfo::find_info()
{
    bool find = false;
    for (auto it = FileSignatureInfo::tab_info.begin(); it != FileSignatureInfo::tab_info.end() && !find; it++){
        if (this->hex_signature.find(it->first) != std::string::npos){
            this->hex_signature = it->first;
            this->category = std::get<0>(it->second);
            this->extension = std::get<1>(it->second);
            this->description = std::get<2>(it->second);
            this->iso_8859_1 = std::get<3>(it->second);
            find = true;
        }
    }
    if (!find){
        this->description = "Unrecognized signature or plain text file";
    }
}
