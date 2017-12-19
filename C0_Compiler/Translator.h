#pragma once
class Translator
{
private:
	static bool global;
	static string cur_fun_name;
	static string regs[8];
	static int para_dim_cnt;//函数参数个数，第一个为0号
	static int counter;//寄存器分配指针
public:
	static ofstream out;
	Translator(void);
	~Translator(void);
	static bool isnum(string s);
	static void init(char *path);
	static void table_tran();
	static void proc_quat(Quaternion q);
	static void translate();
	static void load_to(string name, string register_name);//把name加载到寄存器register_name, name可以是纯数字、字符、标识符（全局和局部）
	static void store_to(string name, string register_name);
	static string reg_alloc(string name, string ban_name_1, string ban_name_2);//申请寄存器（FIFO算法）
	static string reg_alloc(string name, string ban_name);//申请寄存器（FIFO算法）
	static string reg_alloc_and_load(string name, string ban_name);//申请寄存器（FIFO算法）
	static void save_in_cal();//被调用者被调用时，保存$s0-$s7，在被调用者开辟栈空间后使用
	static void save_in_return();//被调用者返回时，保存$s0-$s7里的变量，恢复现场，在被调用者恢复栈空间前使用
	static bool in_reg(string name);//通过切换函数时清空regs表来保证此函数行为正确

};