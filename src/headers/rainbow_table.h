#ifndef RAINBOW_TABLE_H
#define RAINBOW_TABLE_H

#define PUGIXML_HEADER_ONLY
#include "pugixml.hpp"
#include <string>

using namespace std;


class RainbowTable {

	public:
		RainbowTable();
		RainbowTable(const string &path) : file_path(path) {}

		void parse() throw(int);
		void search(string &hash);
		void add(string &file_path, string &key) throw(int);
		void remove(string &key);
		void update_all();
		void add_entry(string,string,string);
		void write();
		void add_url(string &url, string &key) throw(int);
		bool find_repo(string url);
		string getPath();

		//errors
		const static int ERROR_READING_FILE;
		

	private:
		string file_path;
		pugi::xml_document tree;

		static void print_entry(pugi::xml_node &entry);
};
#endif
