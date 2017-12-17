#include "StdAfx.h"

vector<struct errorEntity> Error::errorList;
Error::Error() {
	
}

Error::~Error() {
	
}

void Error::addError(const string t, const int l, const int type) {//只有词法分析是这个
	struct errorEntity e = {
		t,
		l,
		type
	};
	errorList.insert(errorList.end(), e);
	switch (type) {
		case UNDEFINED_INPUT:
			cout << "Error token " << t << " in line " << l << endl;
			break;
		case UNDEFINED_IDSY:
			cout << "Error in line " << l << ":\t标识符未定义"<<endl;
			break;
		case ERROR_INT:
			cout << "Error in line " << l << ":\t整数错误"<<endl;
			break;
		case ERROR_MAIN_FUN_TYP:
			cout << "Error in line " << l << ":\t主函数返回值类型错误"<<endl;
			break;
		case MISS_MAIN_FUN:
			cout << "Error in line " << l << ":\t主函数缺失"<<endl;
			break;
		case MISS_SEMISY:
			cout << "Error in line " << l << ":\t分号缺失" << endl;
			break;
		case MISS_IDSY:
			cout << "Error in line " << l << ":\t标识符缺失" << endl;
			break;
		case MISS_ASINSY:
			cout << "Error in line " << l << ":\t赋值号缺失" << endl;
			break;
		case ANOTHER_DEF:
			cout << "Error in line " << l << ":\t重复定义" << endl;
			break;
		case ERROR_USE_MAIN:
			cout << "Error in line " << l << ":\t非法使用main标识符" << endl;
			break;
		case UNMATCHING:
			cout << "Error in line " << l << ":\t类型不匹配" << endl;
			break;
		case MISS_RET_TYP:
			cout << "Error in line " << l << ":\t返回类型缺失" << endl;
			break;
		case MISS_LPARSY:
			cout << "Error in line " << l << ":\t左圆括号缺失" << endl;
			break;
		case MISS_RPARSY:
			cout << "Error in line " << l << ":\t右圆括号缺失" << endl;
			break;
		case MISS_LCBRACSY:
			cout << "Error in line " << l << ":\t左花括号缺失" << endl;
			break;
		case MISS_RCBRACSY:
			cout << "Error in line " << l << ":\t右花括号缺失" << endl;
			break;
		case MISS_LBRACSY:
			cout << "Error in line " << l << ":\t左方括号缺失" << endl;
			break;
		case MISS_RBRACSY:
			cout << "Error in line " << l << ":\t右方括号缺失" << endl;
			break;
		case UNDEFINED_STAT:
			cout << "Error in line " << l << ":\t未定义语句" << endl;
			break;
		case ERROR_DIM_FUN:
			cout << "Error in line " << l << ":\t函数参数个数错误" << endl;
			break;
		case ERROR_DIM_ARRAY:
			cout << "Error in line " << l << ":\t访问数组越界" << endl;
			break;
		case MISS_PLUS_MINU:
			cout << "Error in line " << l << ":\tfor语句<步长>前加减号缺失" << endl;
			break;
		case ERROR_TYPE_IN_BC:
			cout << "Error in line " << l << ":\tfor语句<步长>不是正整数" << endl;
			break;
		case MISS_COLONSY:
			cout << "Error in line " << l << ":\t<情况子语句>常量后面冒号缺失" << endl;
			break;
		case ERROR_TYPE_IN_CASE:
			cout << "Error in line " << l << ":\t<情况子语句>常量类型不匹配" << endl;
			break;
		case ERROR_TYPE_IN_CONST:
			cout << "Error in line " << l << ":\t常量类型错误" << endl;
			break;
		case MISS_DEFAULT:
			cout << "Error in line " << l << ":\tswitch-case语句default分支缺失" << endl;
			break;
		case ERROR_USE_ARRAY:
			cout << "Error in line " << l << ":\t以数组形式访问了非数组的标识符" << endl;
			break;
		case ERROR_TYP_ARRAY_INDEX:
			cout << "Error in line " << l << ":\t数组索引类型错误" << endl;
			break;
		case ARRAY_OUT_OF_BOUND:
			cout << "Error in line " << l << ":\t访问数组越界" << endl;
			break;
		case ERROR_IDSY:
			cout << "Error in line " << l << ":\t标识符错误" << endl;
			break;
		case ERROR_SCANF:
			cout << "Error in line " << l << ":\tscanf语句错误，只能读取变量" << endl;
			break;
		case ERROR_PRINT:
			cout << "Error in line " << l << ":\tprintf语句错误" << endl;
			break;
		case ERROR_RETURN_TYPE:
			cout << "Error in line " << l << ":\t返回类型错误" << endl;
			break;
		case CAL_FUN_UNMATCHING:
			cout << "Error in line " << l << ":\t参数类型错误" << endl;
			break;
		case ERROR_COND_TYPE:
			cout << "Error in line " << l << ":\t条件类型错误" << endl;
			break;
		case ERROR_CAL_MAIN:
			cout << "Error in line " << l << ":\t非法调用main" << endl;
			break;
		case ERROR_RET_TYPE:
			cout << "Error in line " << l << ":\t函数定义时返回类型错误" << endl;
			break;
		case ERROR_ARRAY_DIM_0:
			cout << "Error in line " << l << ":\t数组维数错误，必须是正整数" << endl;
			break;
	/*	case :
			cout << "Error in line " << l << ":\t" << endl;
			break;*/
		default:
			;
		}   
}

void Error::addError(const int line, const int type) {
	addError("", line, type);
}

