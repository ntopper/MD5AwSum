#include "headers/RainbowTable.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <fstream>
#include <sys/stat.h>
#include <cstring>
#include <stack>
#include <map>

RainbowTable::RainbowTable() {

    //get home dir from env variable or from uid
    const char *homedir;
    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }

	this->file_path = homedir;
    this->file_path += "/.md5awsum";
    mkdir(this->file_path.c_str(), 0777);
    this->file_path += "/hashes.xml";
    
    //create ~/.md5sum/hashes.xml if it does not exist
    struct stat buffer;   
    if(!(stat (this->file_path.c_str(), &buffer) == 0))
    {
        this->tree.load("<RainbowTable />");
        this->write();
    }
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
	
	string temp_file = this->file_path + ".tmp";
	//wget command to download file at URL to ~/.md5awsum.temp
	string wget_command = "wget -O " + temp_file + " " + url;

	//command to remove temp file
	string rm = "rm " + temp_file;
	
	//make system call to download temp file
	system(wget_command.c_str());
	
	//attempt to parse and add to repo
	this->add(temp_file, key);
	
    //add the repository sourse as an entry
    pugi::xml_node root = this->tree.child("RainbowTable");
    pugi::xml_node entry = root.append_child();
    entry.set_name("entry");
    entry.append_attribute("key") = key.c_str();
    entry.append_attribute("name") = url.c_str();
    entry.append_attribute("hash") = "repository";

    //write new tree to file
	this->write();

	//remove the temp file and return
	system(rm.c_str());
	return;
}

void RainbowTable::update_all() {
    stack<string> urls;
    map<string, string> keys;
    string hash = "repository";
    pugi::xml_node root = this->tree.child("RainbowTable");

    //search through child nodes
    for (pugi::xml_node entry = root.first_child();
            entry;
            entry = entry.next_sibling()) {

        const char * entry_hash = entry.attribute("hash").value();

        //push each "repository" entry onto the stack
        if(strcmp(entry_hash, hash.c_str()) == 0) {
            string url = entry.attribute("name").value();
            keys[url] = entry.attribute("key").value();
            urls.push(url);
        }
    }

    //remove and add each URL on the stack
    while (!urls.empty()) {

        this->remove(keys[urls.top()]);
        try { 
            this->add_url(urls.top(), keys[urls.top()]);
        } catch (int e) {cout << "Omitting broken repository " << urls.top() << endl;}
        urls.pop();
    }

}

bool RainbowTable::find_repo(string url) {
    //search for all 'repository' entrys, and return true if any URL matches the url paramater

    string hash = "repository";
    pugi::xml_node root = this->tree.child("RainbowTable");

    //search through child nodes
    for (pugi::xml_node entry = root.first_child();
            entry;
            entry = entry.next_sibling()) {

        const char * name = entry.attribute("name").value();

        //push each "repository" entry onto the stack
        if(strcmp(name, url.c_str()) == 0) {
            return true;
        }
    }

    return false;
}

string RainbowTable::getPath() {
	return this->file_path;
}