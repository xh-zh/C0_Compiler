#pragma once
class Translator
{
private:
	static bool global;
	static string cur_fun_name;
	static vector<string> register_descriptor[10];//$t0-$t9的寄存器描述符
public:
	static ofstream out;
	Translator(void);
	~Translator(void);
	static bool isnum(string s);
	static void init(char *path);
	static void proc_quat(Quaternion q);
	static void translate();
	static void load_to(string name, string register_name);				//把name加载到寄存器register_name, name可以是纯数字、字符、标识符（全局和局部）
	static void store_to(string name, string register_name);			//把寄存器register_name存到name的内存中
	static string get_read_reg(string name, string register_name, string ban_reg1, string ban_reg2);//申请只读寄存器
	static string tmp_reg_alloc(string name, string ban_reg1, string ban_reg2);//无寄存器变量申请临时寄存器
	static string tmp_reg_alloc_for_alloced_val(string name, string ban_reg1, string ban_reg2);//有寄存器变量申请临时寄存器
	static void save_all_val();											//保存寄存器中的所有变量
	static void clear_register_descriptor();							//清空所有寄存器描述符
	static void refresh_reg(string name, string register_name);			//更新使得变量的最新值只存在于此寄存器，用于被写寄存器
	static void add_to_reg_des(string name, string register_name);		//将变量名添加到寄存器描述符
	static void add_to_reg_des(string name, int register_index);		//将变量名添加到寄存器描述符
	static void del_from_reg_des(string name, string register_name);	//将变量名从寄存器描述符中删除
};