// stdafx.cpp : 只包括标准包含文件的源文件
// Lexical Analysis.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中
// 引用任何所需的附加头文件，而不是在此文件中引用

//数字转字符串
string  int2str(const int &int_temp) {  
        stringstream stream;  
        stream<<int_temp;  
        return stream.str();   //此处也可以用 stream>>string_temp  
}  

//实现从枚举（编号）到类型名的映射（debug时用到的可能性比较大）
string getSymbol(const enum kinds k) {
	switch (k) {
	case kinds::PLUSSY:
		return "PLUSSY";
	case kinds::MINUSSY:
		return "MINUSSY";
	case kinds::STARSY:
		return "STARSY";
	case kinds::LESSY:
		return "LESSY";
	case kinds::NLESSY:
		return "NLESSY";
	case kinds::MORSY:
		return "MORSY";
	case kinds::NMORSY:
		return "NMORSY";
	case kinds::DIVISY:
		return "DIVISY";
	case kinds::LPARSY:
		return "LPARSY";
	case kinds::RPARSY:
		return "RPARSY";
	case kinds::LBRACSY:
		return "LBRACSY";
	case kinds::RBRACSY:
		return "RBRACSY";
	case kinds::LCBRACSY:
		return "LCBRACSY";
	case kinds::RCBRACSY:
		return "RCBRACSY";
	case kinds::COMMASY:
		return "COMMASY";
	case kinds::SEMISY:
		return "SEMISY";
	case kinds::COLONSY:
		return "COLONSY";
	case kinds::EQUSY:
		return "EQUSY";
	case kinds::ULINE:
		return "ULINE";
	case kinds::APOSY:
		return "APOSY";
	case kinds::QUOTESY:
		return "QUOTESY";
	case kinds::CHARSY:
		return "CHARSY";
	case kinds::USINTSY:
		return "USINTSY";
	case kinds::INTSY:
		return "INTSY";
	case kinds::STRSY:
		return "STRSY";
	case kinds::IDSY:
		return "IDSY";
	case kinds::CONST:
		return "CONST";
	case kinds::INT:
		return "INT";
	case kinds::CHAR:
		return "CHAR";
	case kinds::VOID:
		return "VOID";
	case kinds::MAIN:
		return "MAIN";
	case kinds::IF:
		return "IF";
	case kinds::ELSE:
		return "ELSE";
	case kinds::FOR:
		return "FOR";
	case kinds::SWITCH:
		return "SWITCH";
	case kinds::CASE:
		return "CASE";
	case kinds::DEFAULT:
		return "DEFAULT";
	case kinds::SCANF:
		return "SCANF";
	case kinds::PRINTF:
		return "PRINTF";
	case kinds::RETURN:
		return "RETURN";
	case kinds::ASINSY:
		return "ASINSY";//=
	case kinds::NEQUSY:
		return "NEQUSY";//!=
	default:
		return "null";
	}
}
