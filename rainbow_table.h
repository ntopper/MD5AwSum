#ifndef RAINBOW_TABLE_H
#define RAINBOW_TABLE_H

#define PUGIXML_HEADER_ONLY
#include "pugixml.cpp"
#include "pugixml.hpp"

#include <string>
using namespace std;

class RainbowTable {

public:
    RainbowTable();
    RainbowTable(const string &path) : file_path(path) {}

    void parse() throw(int);
    void search(string &hash);
    void add(string &file_path, string &key);
    void remove(string &file_path, string &key);
    void write();

    //errors
    const static int ERROR_READING_FILE;

private:
    string file_path;
    pugi::xml_document tree;

    static void print_entry(pugi::xml_node &entry);
};

#endif