#pragma once
class Translator
{
private:
	static bool global;
	static string cur_fun_name;
	static vector<string> register_descriptor[10];//$t0-$t9�ļĴ���������
public:
	static ofstream out;
	Translator(void);
	~Translator(void);
	static bool isnum(string s);
	static void init(char *path);
	static void proc_quat(Quaternion q);
	static void translate();
	static void load_to(string name, string register_name);				//��name���ص��Ĵ���register_name, name�����Ǵ����֡��ַ�����ʶ����ȫ�ֺ;ֲ���
	static void store_to(string name, string register_name);			//�ѼĴ���register_name�浽name���ڴ���
	static string get_read_reg(string name, string register_name, string ban_reg1, string ban_reg2);//����ֻ���Ĵ���
	static string tmp_reg_alloc(string name, string ban_reg1, string ban_reg2);//�޼Ĵ�������������ʱ�Ĵ���
	static string tmp_reg_alloc_for_alloced_val(string name, string ban_reg1, string ban_reg2);//�мĴ�������������ʱ�Ĵ���
	static void save_all_val();											//����Ĵ����е����б���
	static void clear_register_descriptor();							//������мĴ���������
	static void refresh_reg(string name, string register_name);			//����ʹ�ñ���������ֵֻ�����ڴ˼Ĵ��������ڱ�д�Ĵ���
	static void add_to_reg_des(string name, string register_name);		//����������ӵ��Ĵ���������
	static void add_to_reg_des(string name, int register_index);		//����������ӵ��Ĵ���������
	static void del_from_reg_des(string name, string register_name);	//���������ӼĴ�����������ɾ��
};