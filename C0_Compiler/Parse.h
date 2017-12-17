#pragma once
class Parse
{
private:
	static int save_ptr;
	static string cur_fun;
	public:

	//static int proc_add_op();
	//static int proc_mult_op();
	//static int proc_rela_op();
	//static int proc_alpha();
	//static int proc_num();

	static int proc_int_num(int &num);//处理整数：[+|-]<无符号整数>|0
	
	static int proc_const_decl();//常量说明
	static int proc_const_defi();//常量定义
	static int proc_var_decl();//变量说明
	static int proc_var_defi();//变量定义
	static int proc_void_fun_decl();//无返回值函数定义
	static int proc_ioc_fun_decl();//有返回值函数定义
	static int proc_main_fun();//主函数
	static int proc_para(int& dim);//参数、参数表
	//static int proc_valu_para(int &dim);//值参数表
	static int proc_cplx_stat();//复合语句
	static int proc_stat_list();//语句列
	static int proc_stat();//语句
	static int proc_if_stat();//if语句
	static int proc_for_stat();//循环语句（for语句）
	//static int proc_cal_ioc_fun(string &result, kinds &type);//有返回值函数调用语句
	//static int proc_cal_void_fun(string &result, kinds &type);//无返回值函数调用语句
	static int proc_cal_fun(string &result, kinds &type);//函数调用
	static int proc_assi_stat();//赋值语句
	static int proc_read_stat();//读语句
	static int proc_writ_stat();//写语句
	//static int proc_blan_stat();//空语句：没有写函数，直接实现了
	static int proc_swit_stat();//情况语句（switch-case）
	static int proc_retu_stat();//返回语句

	static int proc_cond(string &result, kinds &type);//条件，出现在if、for中
	static int proc_expr(string &result, kinds &type);//表达式
	static int proc_term(string &result, kinds &type);//项
	static int proc_fact(string &result, kinds &type);//因子

	static int proc_case_list(string name, enum kinds type, string end_lable);//情况表，出现在switch-case语句中
	static int proc_case_stat(string name, enum kinds type, string end_lable);//情况子语句
	static int proc_const(enum kinds &type, int &value);//常量，用在case语句中
	static int proc_default();//default，用在switch-case里

	static string new_lable();//新建lable
	static string new_val(enum kinds type, int value);//申请中间变量
public:
	Parse(Lexer lexer);
	~Parse(void);
	static int proc_program();
};

