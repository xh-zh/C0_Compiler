#include "StdAfx.h"
#include "StringTable.h"

int StringTable::i = 1;//0Œª÷√ «"\\n"
vector<string> StringTable::names;
vector<string> StringTable::contents;

StringTable::StringTable(void)
{
}


StringTable::~StringTable(void)
{
}

void StringTable::init() {
	names.push_back("string_0");
	contents.push_back("\\n");
}

string StringTable::add(const string content) {
	string name = "string_" + int2str(i++);
	names.push_back(name);
	contents.push_back(content);
	return name;
}

string StringTable::look_up(const string name) {
	for(int i=0; i < names.size(); i++)
		if (names[i] == name) {
			return contents[i];
		}
	return "";
}

void StringTable::print(char *path) {
	ofstream out(path);
	for	(int i=0; i<names.size(); i++)
		out << names[i] << "\t" << contents[i] << endl;
	out.close();
}

void StringTable::print(ofstream out) {
	for	(int i=0; i<names.size(); i++)
		out << names[i] << ":\t.assicz\t" << contents[i] << endl;
}
