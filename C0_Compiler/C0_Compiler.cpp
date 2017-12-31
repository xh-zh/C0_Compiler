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
		Lexer::init(b==1?"../data/in.txt":"../data/in2.txt");
	} else {
		char ipath[100];
		cin >> ipath;
		Lexer::init(ipath);
	}
	Lexer::getToken();
	Parse::proc_program();
	if (debug_in_main) {
		Table::print("../data/table.txt");
		StringTable::print("../data/StringTable.txt");
		Intermediate_code::print("../data/Intermediate_code.txt");
		Intermediate_code::lable_combine();
		Intermediate_code::print("../data/Intermediate_code_after_lable_combine.txt");
		////Intermediate_code::divd_blk();
		////Intermediate_code::print_blk("../data/Intermediate_code_after_divd_blk.txt");
		//cout << Intermediate_code::code.size() << endl;
		//for	(int i=0; i<Intermediate_code::blocks.size(); i++) {
		//	cout << "begin = " << Intermediate_code::blocks[i].begin << "end = " << Intermediate_code::blocks[i].end << endl;
		//}

	}
	Translator::init("../data/mips.asm");
	Translator::translate();
	cout << "Done!" << endl;


	return 0;
}