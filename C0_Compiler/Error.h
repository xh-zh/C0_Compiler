#pragma once
using namespace std;
//错误种类
const int UNDEFINED_INPUT = 0;		//非法输入，主要用于词法分析部分
const int UNDEFINED_IDSY = 1;		//未定义标识符
const int ERROR_INT = 2;			//整数错误	
const int ERROR_MAIN_FUN_TYP = 3;	//主函数返回值类型有误
const int MISS_MAIN_FUN = 4;		//缺失主函数
const int MISS_SEMISY = 5;			//缺失分号
const int MISS_IDSY = 6;			//缺失标识符
const int MISS_ASINSY = 7;			//缺失等号
const int ANOTHER_DEF = 8;			//重复定义
const int ERROR_USE_MAIN = 9;		//非法使用main标识符
const int UNMATCHING = 10;			//左右类型不匹配
const int MISS_RET_TYP = 11;		//缺失返回类型
const int MISS_LPARSY = 12;			//缺失左括号
const int MISS_RPARSY = 13;			//缺失右括号
const int MISS_LCBRACSY = 14;		//缺失左花括号
const int MISS_RCBRACSY = 15;		//缺失右花括号
const int MISS_LBRACSY = 16;		//缺失左方括号
const int MISS_RBRACSY = 17;		//缺失右方括号
const int UNDEFINED_STAT = 18;		//未定义语句
const int ERROR_DIM_FUN = 19;		//函数参数不对
const int MISS_PLUS_MINU = 21;		//步长部分缺少加减号
const int ERROR_TYPE_IN_BC = 22;	//步长不是正整数
const int MISS_COLONSY = 23;		//缺少冒号（switch-case）
const int ERROR_TYPE_IN_CASE = 24;	//case中类型错误
const int ERROR_TYPE_IN_CONST = 25;	//常量类型错误
const int MISS_DEFAULT = 26;		//缺失default
const int ERROR_IDSY = 30;			//标识符错误（期望标识符，读到的非标识符)
const int ERROR_SCANF = 31;			//读的不是变量
const int ERROR_PRINT = 32;			//打印的不是变量（可以是数组）
const int ERROR_RETURN_TYPE = 33;	//返回类型错误（return...）
const int CAL_FUN_UNMATCHING = 34;	//函数调用参数类型错误
const int ERROR_COND_TYPE = 35;		//条件类型错误
const int ERROR_CAL_MAIN = 36;		//调用main函数
const int ERROR_RET_TYPE = 37;		//返回类型错误
const int ERROR_USE_ARRAY = 27;		//错误使用数组（标识符不是数组）
const int ERROR_TYP_ARRAY_INDEX = 28;//数组索引类型错误（只能用INTSY、CHARSY）
const int ERROR_DIM_ARRAY = 20;		//数组越界
const int ARRAY_OUT_OF_BOUND = 29;	//数组越界
const int ERROR_ARRAY_DIM_0 = 38;	//数组维数非正整数错误

struct errorEntity
{
	string t;
	int l;
	int type;
};

class Error
{
private:
	static vector<struct errorEntity> errorList;
public:
	Error();
	~Error();
	static void addError(string t, int l, int type);
	static void addError(int l, int type);
};
