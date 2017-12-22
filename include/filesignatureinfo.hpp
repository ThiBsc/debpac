#ifndef _FILE_SIGNATURE_INFO_HPP
#define _FILE_SIGNATURE_INFO_HPP

#include <iostream>
#include <string>
#include <tuple>
#include <map>

/**
 * @brief The FileSignatureInfo class
 * @author thibaut
 * Class that deducts the extension of a file from its hex signature
 * https://en.wikipedia.org/wiki/List_of_file_signatures
 */

class FileSignatureInfo
{

public:
  FileSignatureInfo (std::string path);
  virtual ~FileSignatureInfo ();
  enum Category { UNKNOW=0, BINARY, IMAGE, TEXT, AUDIO, PACKAGE, ARCHIVE };

  void set_file(std::string path);

  std::string getPath();
  std::string getExtension();
  std::string getHex_signature();
  std::string getDescription();
  std::string getIso_8859_1();
  Category getCategory();
  std::string to_string();
  friend std::ostream& operator<<(std::ostream& os, FileSignatureInfo& obj);

  static std::map<std::string, std::tuple<Category, std::string, std::string, std::string> > tab_info;

private:
  std::string path;
  std::string extension;
  std::string hex_signature;
  std::string description;
  std::string iso_8859_1;
  Category category;

  void find_info();

};

#endif
