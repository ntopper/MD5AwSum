#include "RepositoryManager.h"
#include "RainbowTable.h"
#include <iostream>
#include <string>
using namespace std;

RepositoryManager::RepositoryManager() {
	//create an instance of RainbowTable stored in master property
	RainbowTable master;
	try {
		master.parse();
	}
	catch(int e) {
		if(e == RainbowTable::ERROR_READING_FILE)
			{cout << "error parsing local repository" >> endl;}
	}
}

void RepositoryManager::add(string url) {
	/*downloads hash table, temporarily puts it in same directory as main table,
	adds downloaded table to the RainbowTable 'master'
	if exception thrown, prints error, deletes file, terminates program, otherwise
	calls rainbowtable save method*/
	string url_key = "something"; //hash
	master.add_url(url, url_key);
}

void RepositoryManager::remove(string url) {
	/*find key associated to url, tell RainbowTable to remove everything associated with
	key, then save */
	string url_key = "anotherthing";
	//master.search(k);
	master.remove(url_key);
}

void RepositoryManager::update(string url) {
	//call remove then add
	string url_key = "somethingelse?";
	master.remove(url_key);
	master.add_url(url, url_key);
}