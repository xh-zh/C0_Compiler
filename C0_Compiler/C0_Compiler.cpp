// Compiler.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
bool debug_in_main = true;

int _tmain(int argc, _TCHAR* argv[])
{
	StringTable::init();//��ʼ���ַ�����
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