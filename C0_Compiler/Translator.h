#pragma once
class Translator
{
private:
	static bool global;
	static string cur_fun_name;
public:
	static ofstream out;
	Translator(void);
	~Translator(void);
	static bool isnum(string s);
	static void init(char *path);
	static void table_tran();
	static void proc_quat(Quaternion q);
	static void translate();
	static void load_to(string name, string register_name);//��name���ص��Ĵ���register_name, name�����Ǵ����֡��ַ�����ʶ����ȫ�ֺ;ֲ���
	static void store_to(string name, string register_name);
};