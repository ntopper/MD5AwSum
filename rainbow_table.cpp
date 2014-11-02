#include "rainbow_table.h"
#include <iostream>
#include <string>
using namespace std;

RainbowTable::RainbowTable() {
    //initalize file_path using config class
    string f = "tests/tst.xml";
    this->file_path = f;
}

const int RainbowTable::ERROR_READING_FILE = 0;

void RainbowTable::parse() throw(int) {

    const char * c = this->file_path.c_str();
    if(!this->tree.load_file(c)) {
        throw(ERROR_READING_FILE);
    }
}

void RainbowTable::search(string &hash) {
    pugi::xml_node root = this->tree.child("RainbowTable");

    //search through child nodes
    for (pugi::xml_node entry = root.first_child();
            entry;
            entry = entry.next_sibling()) {

        const char * entry_hash = entry.attribute("hash").value();

        //is this a match?
        if(strcmp(entry_hash, hash.c_str()) == 0) {
            RainbowTable::print_entry(entry);
        }
    }
}

void RainbowTable::print_entry(pugi::xml_node &entry) {
    //prints all data associated with node entry

    cout << endl;//redability

    //print attributes of entry node
    for (pugi::xml_attribute attr = entry.first_attribute();
            attr;
            attr = attr.next_attribute()) {

        if (strcmp("key" , attr.name()) != 0 ) { //ignore key
            cout << attr.name() << ": " << attr.value() << endl;
        }
    }

    //search through child nodes
    for (pugi::xml_node child = entry.first_child();
            child;
            child = child.next_sibling()) {

        cout  << child.name() << endl;

        //is there text outside of the attrubutes?
        if (child.text()) {
            cout << '\t'  << child.first_child().value() << endl;
        }

        //print attributes of child
        for (pugi::xml_attribute attr = child.first_attribute();
                attr;
                attr = attr.next_attribute()) {
            cout << '\t' << attr.name() << ": " << attr.value() << endl;
        }
    }
}
