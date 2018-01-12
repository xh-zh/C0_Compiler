#pragma once
class TableEntity
{
public:
	string	name;		//������
	int		addr;		//�����������е���Ե�ַ
	enum _CLASS _class;	//������������
	enum kinds type;	//���ŵ���������:int,char,string ���ں������������ķ���ֵ����
	int		value;		//���ŵ�ֵ
	int		dim;		//������ά��Ϊ0�ɣ��������ǲ����������ٸ�������һ���µ����壺Ϊ-1���������ʱ����
	string	parent;		//��������
	vector<string> address_descriptor;//��ַ���������ɰ����Ĵ������ڴ��ַ
	TableEntity(void);
	TableEntity(string name, int addr, enum _CLASS _class,
		enum kinds type, int value, int dim, string parent);
	~TableEntity(void);
};

