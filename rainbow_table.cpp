#include "rainbow_table.h"
#include <iostream>
#include <string>
using namespace std;

RainbowTable::RainbowTable() {
    //initalize file_path using config class

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

void RainbowTable::remove(string &key) {
    //remove all entrys with 'key' of key

    pugi::xml_node root = this->tree.child("RainbowTable");

    //search through child nodes
    for (pugi::xml_node entry = root.first_child();
            entry;
            entry = entry.next_sibling()) {

        const char * node_key = entry.attribute("key").value();

        if (strcmp(key.c_str() , node_key ) == 0) {
            //key matches, remove node from parent
            root.remove_child(entry);
        }
    }
}

void RainbowTable::add(string &file_path, string &key) throw(int) {
    //adds all "entry" elements if the document at file_path to the master xml tree

    //try to load in the new document
    pugi::xml_document new_doc;
    if (!new_doc.load_file(file_path.c_str())) {
        throw(ERROR_READING_FILE);
        return;
    }
    pugi::xml_node new_root = new_doc.child("RainbowTable");
    pugi::xml_node old_root = this->tree.child("RainbowTable");

    //for each new entry
    for (pugi::xml_node entry = new_root.child("entry");
            entry;
            entry = entry.next_sibling("entry")) {
        //add key attribute
        entry.append_attribute("key") = key.c_str();

        //append to master tree
        old_root.append_copy(entry);
    }
}

void RainbowTable::write() {
    this->tree.save_file(this->file_path.c_str());
}

void RainbowTable::add_url(string &url, string &key) throw(int) {
	//uses wget to download a temp file from 'url'
	//attemps to parse the downloaded file, and add entries
	//to the master hash table
	
	string temp_file = "/tmp/.md5repo.xml";
	//wget command to download file at URL to ~/.md5awsum.temp
	string wget_command = "wget -O " + temp_file + " " + url;

	//command to remove temp file
	string rm = "rm " + temp_file;
	
	//make system call to download temp file
	system(wget_command.c_str());
	
	//attempt to parse and add to repo
	try {
		this->add(temp_file, key);	
	}
	catch(int e) {
		throw(e);
	}
	this->write();
	//remove the temp file and return
	system(rm.c_str());
	return;
}
