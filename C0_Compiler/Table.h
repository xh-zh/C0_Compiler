#pragma once
#include "stdafx.h"
class Table
{
public:
	static vector<TableEntity> table;
	static int addr;
	static string cur_parent;
	static int cur_level_pointer;//�ӵ�ǰ��������һ�ʼ���㣬����top�㣬��Ϊtop.index = -1������ʱ���õ���
	Table(void);
	~Table(void);
	static int con_enter(string name, enum kinds type, int val);	//������¼�����������������
	static int val_enter(string name, enum kinds type);				//������¼����ֵΪ0
	static int val_enter(string name, enum kinds type, int value);	//������¼
	static int array_enter(string name ,enum kinds type, int dim);	//�����¼
	static int func_enter(string name, enum kinds type);			//������¼
	static int func_fill_back_value(string name);					//ջ��С���ָ��ֳ�
	static int func_fill_back_dim(string name, int dim);			//���������������
	static int para_enter(string name, enum kinds type, int para_dim_cut);			//������¼

	static bool in_this_level(string name);				//��ǰ����ͬ����ʶ���� ֻ���ڵ�¼ʱʹ�ã� �������뱾������ͬ��
	static bool contain_func(string name);				//��������Ϊname�ĺ���
	//static bool contain(string name);					//�ɼ�����������ĳ��ʶ��
	static bool contain(string fun_name, string name);	//�ɼ�����������ĳ��ʶ��
	static bool is_void_func(string fun_name);			//���޷���ֵ����

	static TableEntity get_func(string name);			//��ѯĳ����


	static enum _CLASS get_CLASS(string fun_name, string name);	//��ѯ���࣬�����Ǳ�����Ҳ�����Ǻ���
	static enum kinds get_type(string fun_name, string name);	//��ѯ����
	static int get_value(string fun_name, string name);			//����û��value
	static int get_dim(string fun_name, string name);			//����ά����������������
	static int get_addr(string fun_name, string name);			//��ѯ��ǰ�����ı����ĵ�ַ�����ɴ��룬��ʼ������ʱ�õ���
	static bool is_global(string fun_name, string name);		//�Ƿ���ȫ�ֱ���
	static int get_fun_size(string fun_name);					//get����ջ��С
	static string get_parent(string fun_name, string name);

	static vector<TableEntity> get_para(string name);			//�õ���������

	static bool set_type(string name, enum kinds type);			//��������ȫ����Ϊ��ȷ�����Table::cur_level_pointer�йأ�ֻ�����﷨����ʱ��

	static void print(char *path);		//��ӡ���ű�
};

