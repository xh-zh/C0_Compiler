#include "StdAfx.h"
#include "Translator.h"

/***********DEBUG*************/
bool debug = false;//汇编代码中显示中间代码
/***********DEBUG*************/

ofstream Translator::out;
bool Translator::global = true;
string Translator::cur_fun_name = "top";

Translator::Translator()
{
}


Translator::~Translator()
{
}

bool Translator::isnum(const string s) { 
	stringstream sin(s);  
	double t;  
	char p;  
	if(!(sin >> t))
		return false;  
	if(sin >> p) 
		return false;  
	else  
		return true;  
}

void Translator::init(char* path) {
	out = ofstream(path);
	out << ".data" << endl;//开头就是数据区
	for (unsigned i=0; i<StringTable::names.size(); i++)//字符串表
		out << StringTable::names[i] << ":\t.asciiz\t\"" << StringTable::contents[i] << "\"" << endl;
}

void Translator::table_tran() {
	
}

void Translator::proc_quat(const Quaternion q) {
	if (debug) out<< "#" << q.op << "\t" << q.para1 << "\t" << q.para2 << "\t" << q.result << endl;
	if (q.op == "CONST") {//CONST	type	value	name
		if (global) {//全局数据区
			out << q.result << ": .word\t" << q.para2 <<endl;	
		} else {//运行栈
			const int addr = Table::get_addr(cur_fun_name, q.result);
			out << "li	$t0, " << q.para2 << endl;
			out << "sw	$t0, " << int2str(addr) << "($sp)" << endl;
		}

	} else if (q.op == "VAL") {//VAL	type	blank	name
		if (global) {//全局数据区
			out << q.result << ": .word\t0" <<endl;	
		} else {//运行栈
			//相当于初始化成0
		}

	} else if (q.op == "ARRAY") {//ARRAY	type	dim	name
		if (global) {//全局数据区
			out << q.result << ": .word\t1 : " << q.para2 << endl;//初始化成1
		} else {//运行栈
			//相当于初始化成0
		}

	} else if (q.op=="+" || q.op=="-" || q.op=="*" || q.op=="/" ||
		q.op=="<" || q.op=="<=" || q.op==">" || q.op==">=" || 
		q.op=="==" || q.op=="!=") {//op	para1	para2	result
		//$t0, $t1中存操作数, $t2中存结果
		load_to(q.para1, "$t0");
		load_to(q.para2, "$t1");
		if (q.op == "+") {
			out << "add	$t2, $t0, $t1" <<endl;
		} else if (q.op == "-") {
			out << "sub	$t2, $t0, $t1" <<endl;
		} else if (q.op == "*") {
			out << "mult	$t0, $t1" <<endl;
			out << "mflo	$t2" << endl;
		} else if (q.op == "/") {
			out << "div	$t0, $t1" <<endl;
			out << "mflo	$t2" << endl;
		} else if (q.op == "<") {
			out << "slt	$t2, $t0, $t1" << endl;
		} else if (q.op == "<=") {
			out << "sle	$t2, $t0, $t1" << endl;
		} else if (q.op == ">") {
			out << "sgt	$t2, $t0, $t1" << endl;
		} else if (q.op == ">=") {
			out << "sge	$t2, $t0, $t1" << endl;
		} else {
			out << "seq	$t2, $t0, $t1" << endl;
			if (q.op == "!=") {
				out << "xori	$t2, 1" << endl;
			}
		}
		store_to(q.result, "$t2");

	} else if (q.op == "=") {//=	value	blank	IDSY_name
		load_to(q.para1, "$t0");
		store_to(q.result, "$t0");

	} else if (q.op == "[]=") {//[]=, array_name, index_name, expr_name
		const int array_addr = Table::get_addr(cur_fun_name, q.para1);
		const int index_addr = Table::get_addr(cur_fun_name, q.para2);
		const int expr_addr = Table::get_addr(cur_fun_name, q.result);
		if (Table::is_global(cur_fun_name, q.para1)) {//全局数组
			out << "la	$t0, " << q.para1 << endl;//base绝对地址
		} else {
			out << "li	$t0, " << int2str(array_addr) << endl;//base相对于栈指针的地址
			out << "add	$t0, $t0, $sp" << endl;//现在是绝对地址了
		}
		//$t0:	数组首绝对地址
		load_to(q.para2, "$t1");//index
		out << "li	$t2, 4" << endl;
		out << "mult	$t1, $t2" << endl;
		out << "mflo	$t1" << endl;//offest
		//$t1:	该元素相对于首地址的偏移
		out << "add	$t0, $t0, $t1" << endl;
		//$t0:	该元素绝对地址
		load_to(q.result, "$t1");
		out << "sw	$t1, 0($t0)" << endl;

	} else if (q.op == "=[]") {//=[], array_name, index_name, result
		const int array_addr = Table::get_addr(cur_fun_name, q.para1);
		const int index_addr = Table::get_addr(cur_fun_name, q.para2);
		const int result_addr = Table::get_addr(cur_fun_name, q.result);
		if (Table::is_global(cur_fun_name, q.para1)) {
			out << "la	$t0, " << q.para1 << endl;//base绝对地址
		} else {
			out << "la	$t0, " << int2str(array_addr) << endl;//base相对于栈指针的地址
			out << "add	$t0, $t0 ,$sp" << endl;//绝对地址
		}
		//$t0:	数组首绝对地址
		load_to(q.para2, "$t1");//index
		out << "li	$t2, 4" << endl;
		out << "mult	$t1, $t2" << endl;
		out << "mflo	$t1" << endl;//offest
		//$t1:	该元素相对于首地址的偏移
		out << "add	$t0, $t0, $t1" << endl;
		//$t0:	该元素绝对地址
		out << "lw	$t0, 0($t0)" << endl;
		store_to(q.result, "$t0");

	} else if (q.op == "BZ") {//BZ	条件		LABLE，不成立跳转
		load_to(q.para1, "$t0");
		out << "beq	$t0, $0, " << q.para2 << endl;

	} else if (q.op == "BNZ") {//BNZ	条件		LABLE，成立跳转
		load_to(q.para1, "$t0");
		out << "bne	$t0, $0, " << q.para2 << endl;

	} else if (q.op == "GOTO") {//GOTO	LABLE
		out << "j	" << q.para1 << endl;

	} else if (q.op == "LABLE") {//LABLE	lable_name
		out << q.para1 << ":" << endl;

	} else if (q.op == "FUN" && q.para1 == "BEGIN") {//全局变量声明结束
		out << ".text" << endl;
		out << "j	main" << endl;
		global = false;

	} else if (q.op == "FUN") {//FUN	INTSY	fun0
		cur_fun_name = q.para2;
		const int size = Table::get_fun_size(cur_fun_name);
		out	<< cur_fun_name << ":" << endl;
		out << "subi	$sp, $sp, " << int2str(size) << endl;
		out << "sw	$ra, 0($sp)" << endl;

	} else if (q.op == "PUSH") {//PUSH	val_name	para_name	fun_name
		//para_name一定是函数参数名，因此这里没必要用stroe_to()
		const int fun_size = Table::get_fun_size(q.result);
		const int val_addr = Table::get_addr(cur_fun_name, q.para1);//这个是传入的参数的地址，不是在被调用函数中的地址
		const int para_addr = Table::get_addr(q.result, q.para2);//参数在被调用函数中的地址
		load_to(q.para1, "$t0");
		out << "subi	$sp, $sp, " << int2str(fun_size) << endl;
		out << "sw	$t0, " << int2str(para_addr) << "($sp)" << endl;
		out << "addi	$sp, $sp, " << int2str(fun_size) << endl;

	} else if (q.op == "CALL") {//CALL	fun_name
		out << "jal	" << q.para1 << endl;

	} else if (q.op == "RETURN") {//RETURN	val_type	val_name
		if (cur_fun_name == "main") {
			out << "li	$v0, 10" << endl;
			out << "syscall" << endl;
		}
		if (!Table::is_void_func(cur_fun_name)) {//即非RETURN	NONE
			load_to(q.para2, "$v0");//返回值
		}
		const int size = Table::get_fun_size(cur_fun_name);
		out << "lw	$ra, 0($sp)" << endl;
		out << "addi	$sp, $sp, " << int2str(size) << endl;
		out << "jr	$ra" <<endl;

	} else if (q.op == "END") {//END	fun_name//有返回语句的话不会执行到这
		if (!Table::is_void_func(cur_fun_name)) {	
			load_to(q.para2, "$v0");//返回值
		}
		const int size = Table::get_fun_size(cur_fun_name);
		out << "lw	$ra, 0($sp)" << endl;
		out << "addi	$sp, $sp, " << int2str(size) << endl;
		out << "jr	$ra" <<endl;

	} else if (q.op == "LOAD_RETURN_VALUE") {//LOAD_RETURN_VALUE	blank	blank	name
		/*const int addr = Table::get_addr(cur_fun_name, q.result);
		out << "sw	$v0, " << int2str(addr) << "($sp)" << endl;*/
		store_to(q.result, "$v0");
	}
	else if (q.op == "PRINT") {//PRINT	type	name，type = INTSY/CHARSY/STRING
		if (q.para1 == "INTSY") {
			load_to(q.para2, "$a0");
			out << "li	$v0, 1" << endl;
		} else if (q.para1 == "CHARSY") {
			load_to(q.para2, "$a0");
			out << "li	$v0, 11" << endl;
		} else {//String
			out << "la	$a0, " << q.para2 << endl;
			out << "li	$v0, 4" << endl;
		}
		out << "syscall" << endl;

	} else if (q.op == "SCANF") {//SCANF	type	name
		if (q.para1 == "INTSY") {
			out << "li	$v0, 5" << endl;
		} else {
			out << "li	$v0, 12" << endl;
		}
		out << "syscall" << endl;
		store_to(q.para2, "$v0");
	} else if (q.op == "TERMINATE") {
		out << "li	$v0, 10" << endl;
		out << "syscall" << endl;
	}
	if (debug) out << endl;
}

void Translator::translate() {
	for (unsigned i=0; i<Intermediate_code::code.size(); i++)
		Translator::proc_quat(Intermediate_code::code[i]);
	out.close();
}

void Translator::load_to(const string name, const string register_name) {
	if (isnum(name)) {//数字
		out << "li	" << register_name << ", " << name << endl;
	} else if ((!Table::contain(cur_fun_name, name)) && name.length() == 1) {//字符
		out << "li	" << register_name << ", '" << name[0] << "'" << endl;
	} else if (Table::is_global(cur_fun_name, name)) {//全局量
		//out << "la	" << register_name << ", " << name << endl;
		//out << "lw	" << register_name << ", 0(" << register_name << ")" << endl;
		out << "lw	" << register_name << ", " << name << endl;
	} else {//局部量
		const int addr = Table::get_addr(cur_fun_name, name);
		out << "lw	" << register_name << ", " << int2str(addr) << "($sp)" << endl;
	}
}

void Translator::store_to(const string name, const string register_name) {
	if (Table::is_global(cur_fun_name, name)) {
		out << "sw	" << register_name << ", " << name << endl;
	} else {
		const int addr = Table::get_addr(cur_fun_name, name);
		out << "sw	" << register_name << ", " << int2str(addr) << "($sp)" << endl;
	}
}