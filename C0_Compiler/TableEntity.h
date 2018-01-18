#pragma once
class TableEntity
{
public:
	string	name;		//符号名
	int		addr;		//符号在运行中的相对地址
	enum _CLASS _class;	//符号所属种类
	enum kinds type;	//符号的数据类型:int,char,string 对于函数，这是它的返回值类型
	int		value;		//符号的值
	int		dim;		//非数组维数为0吧，函数则是参数个数，再给它赋予一个新的意义：为-1则代表是临时变量
	string	parent;		//父函数名
	vector<string> address_descriptor;//地址描述符，可包含寄存器、内存地址
	TableEntity(void);
	TableEntity(string name, int addr, enum _CLASS _class,
		enum kinds type, int value, int dim, string parent);
	~TableEntity(void);
};

