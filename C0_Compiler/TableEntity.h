#pragma once
class TableEntity
{
public:
	string	name;		//符号的唯一标识，字符串是没有名字的，由name保存其内容
	int		addr;		//符号在运行中的相对地址
	enum _CLASS _class;	//符号所属种类
	enum kinds type;	//符号的数据类型:int,char,string 对于函数，这是它的返回值类型
	int		value;		//符号的值
	int		dim;		//非数组维数为0吧，函数则是参数个数
	string	parent;		//父函数名
	TableEntity(void);
	TableEntity(string name, int addr, enum _CLASS _class,
		enum kinds type, int value, int dim, string parent);
	~TableEntity(void);
};

