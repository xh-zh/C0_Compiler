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
	static void load_to(string name, string register_name);//把name加载到寄存器register_name, name可以是纯数字、字符、标识符（全局和局部）
	static void store_to(string name, string register_name);

};