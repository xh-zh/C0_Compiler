// Compiler.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
bool debug_in_main = false;

int _tmain(int argc, _TCHAR* argv[])
{
	StringTable::init();//��ʼ���ַ�����
	char ipath[100];
	cin >> ipath;
	Lexer::init(ipath);
	Lexer::getToken();
	Parse::proc_program();
	Intermediate_code::print("../data/Intermediate_code.txt");
	Intermediate_code::optimize();
	Intermediate_code::print("../data/Intermediate_code_after_optimize.txt");
	Translator::init("../data/mips.asm");
	Translator::translate();
	cout << "Done!" << endl;

	return 0;
}