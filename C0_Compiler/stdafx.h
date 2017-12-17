// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: 在此处引用程序需要的其他头文件
#include <vector>
#include "string"
#include "iostream"
#include "algorithm"
#include "Error.h"
#include "fstream"
#include "Lexer.h"
#include "Parse.h"
#include "TableEntity.h"
#include "Table.h"
#include "Intermediate_code.h"
#include "Translator.h"
#include "sstream"
#include "StringTable.h"

using namespace std;

enum kinds{
	null, PLUSSY, MINUSSY, STARSY, LESSY, NLESSY, MORSY, NMORSY, 
	DIVISY, LPARSY, RPARSY, LBRACSY, RBRACSY, LCBRACSY, RCBRACSY, 
	COMMASY, SEMISY, COLONSY, EQUSY, ULINE, APOSY, QUOTESY, CHARSY,		USINTSY, INTSY, STRSY, IDSY, NEQUSY, ASINSY,//不等号和赋值号
	//USINTSY: 非负整数	INTSY: 整数
	//保留字
	CONST, INT, CHAR, VOID, MAIN, IF, ELSE, FOR, SWITCH, CASE, 
	DEFAULT, SCANF, PRINTF, RETURN, 
};

//extern string token;
//extern int num;
//extern enum kinds symbol;
string getSymbol(const enum kinds k);


enum _CLASS
{
	NONE_CLASS,
	ARRAY_CLASS,
	FUN_VOID_CLASS,
	FUN_IOC_CLASS,
	CONST_CLASS,
	VAL_CLASS,
	PARA_CLASS,
};

string  int2str(const int &int_temp);