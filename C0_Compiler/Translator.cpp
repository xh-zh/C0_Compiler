#include "StdAfx.h"
#include "Translator.h"

/***********DEBUG*************/
bool debug = false;//汇编代码中显示中间代码
/***********DEBUG*************/

ofstream Translator::out;
bool Translator::global = true;
string Translator::cur_fun_name = "top";
vector<string> Translator::register_descriptor[10];

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
		const string para1_reg = q.para1=="$v0"?"$v0":"$t0";
		const string para2_reg = q.para2=="$v0"?"$v0":"$t1";
		if (para1_reg != "$v0")	load_to(q.para1, para1_reg);
		if (para2_reg != "$v0")	load_to(q.para2, para2_reg);
		if (q.op == "+") {
			out << "add	$t2, " << para1_reg << ", " << para2_reg <<endl;
		} else if (q.op == "-") {
			if (q.para1 == "0")
				out << "neg	$t2, " << para2_reg << endl;
			else 
				out << "sub	$t2, " << para1_reg << ", " << para2_reg <<endl;
		} else if (q.op == "*") {
			out << "mul	$t2, " << para1_reg << ", " << para2_reg <<endl;
		} else if (q.op == "/") {
			out << "div	" << para1_reg << ", " << para2_reg <<endl;
			out << "mflo	$t2" << endl;
		} else if (q.op == "<") {
			out << "slt	$t2, " << para1_reg << ", " << para2_reg <<endl;
		} else if (q.op == "<=") {
			out << "sle	$t2, " << para1_reg << ", " << para2_reg <<endl;
		} else if (q.op == ">") {
			out << "sgt	$t2, " << para1_reg << ", " << para2_reg <<endl;
		} else if (q.op == ">=") {
			out << "sge	$t2, " << para1_reg << ", " << para2_reg <<endl;
		} else {
			out << "seq	$t2, " << para1_reg << ", " << para2_reg <<endl;
			if (q.op == "!=") {
				out << "xori	$t2, 1" << endl;
			}
		}
		store_to(q.result, "$t2");

	} else if (q.op == "=") {//=	value	blank	IDSY_name
		if (q.para1 == "$v0") {
			store_to(q.result, "$v0");
		} else {
			load_to(q.para1, "$t0");
			store_to(q.result, "$t0");
		}

	} else if (q.op == "[]=") {//[]=, index_name, expr_name, array_name
		if (Table::is_global(cur_fun_name, q.result)) {//全局数组
			out << "la	$t0, " << q.result << endl;//base绝对地址
		} else {
			const int array_addr = Table::get_addr(cur_fun_name, q.result);
			out << "li	$t0, " << int2str(array_addr) << endl;//base相对于栈指针的地址
			out << "add	$t0, $t0, $sp" << endl;//现在是绝对地址了
		}
		//$t0:	数组首绝对地址
		const string index_reg = q.para1=="$v0"?"$v0":"$t1";
		if (index_reg != "$v0")	load_to(q.para1, index_reg);//index
		out << "sll	" << index_reg << ", " << index_reg << ", 2" << endl;//offest
		//$t1:	该元素相对于首地址的偏移
		out << "add	$t0, $t0, " << index_reg << endl;
		//$t0:	该元素绝对地址
		const string expr_reg = q.para2=="$v0"?"$v0":"$t1";
		if (expr_reg != "$v0")	load_to(q.para2, expr_reg);
		out << "sw	" << expr_reg << ", 0($t0)" << endl;

	} else if (q.op == "=[]") {//=[], array_name, index_name, result
		if (Table::is_global(cur_fun_name, q.para1)) {
			out << "la	$t0, " << q.para1 << endl;//base绝对地址
		} else {	
			const int array_addr = Table::get_addr(cur_fun_name, q.para1); 
			out << "la	$t0, " << int2str(array_addr) << endl;//base相对于栈指针的地址
			out << "add	$t0, $t0 ,$sp" << endl;//绝对地址
		}
		//$t0:	数组首绝对地址
		const string index_reg = q.para2=="$v0"?"$v0":"$t1";
		if (index_reg != "$v0")	load_to(q.para2, index_reg);//index
		out << "sll	" << index_reg << ", " << index_reg << ", 2" << endl;//offest
		//$t1:	该元素相对于首地址的偏移
		out << "add	$t0, $t0, " << index_reg << endl;
		//$t0:	该元素绝对地址
		out << "lw	$t0, 0($t0)" << endl;
		store_to(q.result, "$t0");//被赋值的应该不会是$v0吧

	} else if (q.op == "BZ") {//BZ	条件		LABLE，不成立跳转
		const string bz_reg = q.para1=="$v0"?"$v0":"$t0";
		if (bz_reg != "$v0")	load_to(q.para1, bz_reg);
		out << "beq	" << bz_reg << ", $0, " << q.para2 << endl;

	} else if (q.op == "BNZ") {//BNZ	条件		LABLE，成立跳转
		const string bnz_reg = q.para1=="$v0"?"$v0":"$t0";
		if (bnz_reg != "$v0")	load_to(q.para1, bnz_reg);
		out << "bne	" << bnz_reg << ", $0, " << q.para2 << endl;

	} else if (q.op == "GOTO") {//GOTO	LABLE
		out << "j	" << q.para1 << endl;

	} else if (q.op == "LABLE") {//LABLE	lable_name
		out << q.para1 << ":" << endl;

	} else if (q.op == "FUN" && q.para1 == "BEGIN") {//全局变量声明结束
		out << ".text" << endl;
		out << "j	main" << endl;
		global = false;

	} else if (q.op == "FUN") {//FUN	INTSY	fun_name
		cur_fun_name = q.para2;
		const int size = Table::get_fun_size(cur_fun_name);
		out << cur_fun_name << ":" << endl;
		out << "subi	$sp, $sp, " << int2str(size) << endl;
		out << "sw	$ra, 0($sp)" << endl;

	} else if (q.op == "PUSH") {//PUSH	val_name	para_name	fun_name
		//最后还是决定不用寄存器传参了，因为当一个函数调用作为另一个函数参数传入的时候，会发生严重错误
		//para_name一定是函数参数名，因此这里没必要用stroe_to()
		const int fun_size = Table::get_fun_size(q.result);
		//const int val_addr = Table::get_addr(cur_fun_name, q.para1);//这个是传入的参数的地址，不是在被调用函数中的地址
		const int para_addr = Table::get_addr(q.result, q.para2);//参数在被调用函数中的地址
		const string val_reg = q.para1=="$v0"?"$v0":"$t0";
		if (val_reg != "$v0")	load_to(q.para1, val_reg);
		out << "subi	$sp, $sp, " << int2str(fun_size) << endl;
		out << "sw	" << val_reg << ", " << int2str(para_addr) << "($sp)" << endl;
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
		//主函数只有TERMINATE，没有END
		if (!Table::is_void_func(cur_fun_name)) {
			load_to(q.para2, "$v0");//返回值
		}
		const int size = Table::get_fun_size(cur_fun_name);
		out << "lw	$ra, 0($sp)" << endl;
		out << "addi	$sp, $sp, " << int2str(size) << endl;
		out << "jr	$ra" <<endl;

	} else if (q.op == "LOAD_RETURN_VALUE") {//LOAD_RETURN_VALUE	blank	blank	name
		store_to(q.result, "$v0");
	}
	else if (q.op == "PRINT") {//PRINT	type	name，type = INTSY/CHARSY/STRING
		if (q.para1 == "INTSY") {
			if (q.para2 != "$v0")	load_to(q.para2, "$a0");
			else out << "move	$a0, $v0" << endl;
			out << "li	$v0, 1" << endl;
		} else if (q.para1 == "CHARSY") {
			if (q.para2 != "$v0")	load_to(q.para2, "$a0");
			else out << "move	$a0, $v0" << endl;
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
	} else if (name[0] == '$') {//字符
		out << "li	" << register_name << ", " << name.substr(1) << endl;
	} /*else if (Table::get_CLASS(cur_fun_name, name) == _CLASS::PARA_CLASS &&
		Table::get_dim(cur_fun_name, name) < 4) {
		const int para_cnt = Table::get_dim(cur_fun_name, name);
		out << "move	" << register_name << ", " << "$a"+int2str(para_cnt) << endl;
	}*/
	//参数都通过运行栈传递
	else if (Table::is_global(cur_fun_name, name)) {//全局量
		//out << "la	" << register_name << ", " << name << endl;
		//out << "lw	" << register_name << ", 0(" << register_name << ")" << endl;
		out << "lw	" << register_name << ", " << name << endl;
	} else {//局部量
		const int addr = Table::get_addr(cur_fun_name, name);
		out << "lw	" << register_name << ", " << int2str(addr) << "($sp)" << endl;
	}
}

void Translator::store_to(const string name, const string register_name) {
	if (isnum(name)) {} //数字
	else if (name[0] == '$') {} //字符
	else if (Table::is_global(cur_fun_name, name)) {
		out << "sw	" << register_name << ", " << name << endl;
	} else {
		const int addr = Table::get_addr(cur_fun_name, name);
		out << "sw	" << register_name << ", " << int2str(addr) << "($sp)" << endl;
	}
}
