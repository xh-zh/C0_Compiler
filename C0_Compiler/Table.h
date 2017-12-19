#pragma once
#include "stdafx.h"
class Table
{
public:
	static vector<TableEntity> table;
	static int addr;
	static string cur_parent;
	static int cur_level_pointer;//从当前函数的下一项开始计算，对于top层，认为top.index = -1，填表的时候用到的
	Table(void);
	~Table(void);
	static int con_enter(string name, enum kinds type, int val);	//常量登录，常量不会出现数组
	static int val_enter(string name, enum kinds type);				//变量登录，初值为0
	static int val_enter(string name, enum kinds type, int value);	//变量登录
	static int array_enter(string name ,enum kinds type, int dim);	//数组登录
	static int func_enter(string name, enum kinds type);			//函数登录
	static int func_fill_back_value(string name);					//栈大小并恢复现场
	static int func_fill_back_dim(string name, int dim);			//函数回填参数个数
	static int para_enter(string name, enum kinds type, int para_dim_cut);			//参数登录

	static bool in_this_level(string name);				//当前层有同名标识符， 只能在登录时使用， 不允许与本函数名同名
	static bool contain_func(string name);				//声明过名为name的函数
	//static bool contain(string name);					//可见域内声明过某标识符
	static bool contain(string fun_name, string name);	//可见域内声明过某标识符
	static bool is_void_func(string fun_name);			//是无返回值函数

	static TableEntity get_func(string name);			//查询某函数


	static enum _CLASS get_CLASS(string fun_name, string name);	//查询种类，可以是变量，也可以是函数
	static enum kinds get_type(string fun_name, string name);	//查询类型
	static int get_value(string fun_name, string name);			//数组没有value
	static int get_dim(string fun_name, string name);			//数组维数、函数参数个数
	static int get_addr(string fun_name, string name);			//查询当前函数的变量的地址（生成代码，初始化变量时用到）
	static bool is_global(string fun_name, string name);		//是否是全局变量
	static int get_fun_size(string fun_name);					//get函数栈大小
	static string get_parent(string fun_name, string name);

	static vector<TableEntity> get_para(string name);			//得到函数参数

	static bool set_type(string name, enum kinds type);			//函数不安全，行为正确与否与Table::cur_level_pointer有关，只能在语法分析时用

	static void print(char *path);		//打印符号表
};

