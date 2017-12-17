// Compiler.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
bool debug_in_main = true;

int _tmain(int argc, _TCHAR* argv[])
{
	StringTable::init();//初始化字符串表
	if (debug_in_main) {
		int b;
		cin >> b;
		Lexer::init(b==1?"./in.txt":"./in2.txt");
	} else {
		char ipath[100];
		cin >> ipath;
		Lexer::init(ipath);
	}
	Lexer::getToken();
	Parse::proc_program();
	Table::print("./table.txt");
	StringTable::print("./StringTable.txt");
	Intermediate_code::print("./Intermediate_code.txt");
	Translator::init("./mips.asm");
	Translator::translate();
	cout << "Done!" << endl;


	return 0;
}