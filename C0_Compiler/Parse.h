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

	static int proc_int_num(int &num);//����������[+|-]<�޷�������>|0
	
	static int proc_const_decl();//����˵��
	static int proc_const_defi();//��������
	static int proc_var_decl();//����˵��
	static int proc_var_defi();//��������
	static int proc_void_fun_decl();//�޷���ֵ��������
	static int proc_ioc_fun_decl();//�з���ֵ��������
	static int proc_main_fun();//������
	static int proc_para(int& dim);//������������
	//static int proc_valu_para(int &dim);//ֵ������
	static int proc_cplx_stat();//�������
	static int proc_stat_list();//�����
	static int proc_stat();//���
	static int proc_if_stat();//if���
	static int proc_for_stat();//ѭ����䣨for��䣩
	//static int proc_cal_ioc_fun(string &result, kinds &type);//�з���ֵ�����������
	//static int proc_cal_void_fun(string &result, kinds &type);//�޷���ֵ�����������
	static int proc_cal_fun(string &result, kinds &type);//��������
	static int proc_assi_stat();//��ֵ���
	static int proc_read_stat();//�����
	static int proc_writ_stat();//д���
	//static int proc_blan_stat();//����䣺û��д������ֱ��ʵ����
	static int proc_swit_stat();//�����䣨switch-case��
	static int proc_retu_stat();//�������

	static int proc_cond(string &result, kinds &type);//������������if��for��
	static int proc_expr(string &result, kinds &type);//���ʽ
	static int proc_term(string &result, kinds &type);//��
	static int proc_fact(string &result, kinds &type);//����

	static int proc_case_list(string name, enum kinds type, string end_lable);//�����������switch-case�����
	static int proc_case_stat(string name, enum kinds type, string end_lable);//��������
	static int proc_const(enum kinds &type, int &value);//����������case�����
	static int proc_default();//default������switch-case��

	static string new_lable();//�½�lable
	static string new_val(enum kinds type, int value);//�����м����
public:
	Parse(Lexer lexer);
	~Parse(void);
	static int proc_program();
};

