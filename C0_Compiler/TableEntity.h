#pragma once
class TableEntity
{
public:
	string	name;		//���ŵ�Ψһ��ʶ���ַ�����û�����ֵģ���name����������
	int		addr;		//�����������е���Ե�ַ
	enum _CLASS _class;	//������������
	enum kinds type;	//���ŵ���������:int,char,string ���ں������������ķ���ֵ����
	int		value;		//���ŵ�ֵ
	int		dim;		//������ά��Ϊ0�ɣ��������ǲ�������
	string	parent;		//��������
	TableEntity(void);
	TableEntity(string name, int addr, enum _CLASS _class,
		enum kinds type, int value, int dim, string parent);
	~TableEntity(void);
};

