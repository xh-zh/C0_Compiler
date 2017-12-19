#pragma once
class Translator
{
private:
	static bool global;
	static string cur_fun_name;
	static string regs[8];
	static int para_dim_cnt;//����������������һ��Ϊ0��
	static int counter;//�Ĵ�������ָ��
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
	static string reg_alloc(string name, string ban_name_1, string ban_name_2);//����Ĵ�����FIFO�㷨��
	static string reg_alloc(string name, string ban_name);//����Ĵ�����FIFO�㷨��
	static string reg_alloc_and_load(string name, string ban_name);//����Ĵ�����FIFO�㷨��
	static void save_in_cal();//�������߱�����ʱ������$s0-$s7���ڱ������߿���ջ�ռ��ʹ��
	static void save_in_return();//�������߷���ʱ������$s0-$s7��ı������ָ��ֳ����ڱ������߻ָ�ջ�ռ�ǰʹ��
	static bool in_reg(string name);//ͨ���л�����ʱ���regs������֤�˺�����Ϊ��ȷ

};