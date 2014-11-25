#include "headers/RepositoryManager.h"
#include "headers/RainbowTable.h"
#include "headers/Md5Hash.h"
#include <iostream>
#include <string>
using namespace std;

RepositoryManager::RepositoryManager() {
	//create an instance of RainbowTable stored in master property
	//RainbowTable master;
	try {
		this->master.parse();
	}
	catch(int e) {
		if(e == RainbowTable::ERROR_READING_FILE)
			{cout << "error parsing local repository" << endl;}
	}
}

void RepositoryManager::add(string url) {
	/*downloads hash table, temporarily puts it in same directory as main table,
	adds downloaded table to the RainbowTable 'master'
	if exception thrown, prints error, deletes file, terminates program, otherwise
	calls rainbowtable save method*/
	Md5Hash hash(url, true);
	string url_key = hash.getChecksum(); 
	this->master.add_url(url, url_key);
	this->master.write();
}

void RepositoryManager::remove(string url) {
	/*find key associated to url, tell RainbowTable to remove everything associated with
	key, then save */
	Md5Hash hash(url, true); string url_key = hash.getChecksum(); 
	//master.search(k);
	this->master.remove(url_key);
	this->master.write();
}

void RepositoryManager::update(string url) {
	//calls remove then add on a url
	Md5Hash hash(url, true); string url_key = hash.getChecksum(); 
	this->master.remove(url_key);
	this->master.add_url(url, url_key);
	this->master.write();
}

void RepositoryManager::update() {
	//searches table for all "repository" entries
	//"updates" each url found
	this->master.update_all();
	this->master.write();
}

void RepositoryManager::print() {
	//prints all repositories
	string url = "repository";
	this->master.search(url);
}
