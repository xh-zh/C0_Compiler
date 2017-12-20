#include "StdAfx.h"
#include "Translator.h"

/***********DEBUG*************/
bool debug = true;//汇编代码中显示中间代码
/***********DEBUG*************/

ofstream Translator::out;
bool Translator::global = true;
string Translator::cur_fun_name = "top";
string Translator::regs[8];
int Translator::para_dim_cnt = 0;
int Translator::counter = 0;

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
	for (int i=0; i<8; i++)
		regs[i] = "";
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
		string para1_reg, para2_reg;
		if (isnum(q.para1) && q.para1 == "0") para1_reg = "$0";
		else para1_reg = reg_alloc_and_load(q.para1, "");
		if (isnum(q.para2) && q.para2 == "0") para2_reg = "$0";
		else para2_reg = reg_alloc_and_load(q.para2, q.para1);
		const string result_reg = reg_alloc(q.result, q.para1, q.para2);
		if (q.op == "+") {
			out << "add	" << result_reg << ", " << para1_reg << ", " << para2_reg << endl;
		} else if (q.op == "-") {
			out << "sub	" << result_reg << ", " << para1_reg << ", " << para2_reg << endl;
		} else if (q.op == "*") {
			out << "mult	" << para1_reg << ", " << para2_reg << endl;
			out << "mflo	" << result_reg << endl;
		} else if (q.op == "/") {
			out << "div	" << para1_reg << ", " << para2_reg << endl;
			out << "mflo	" << result_reg << endl;
		} else if (q.op == "<") {
			out << "slt	" << result_reg << ", " << para1_reg << ", " << para2_reg << endl;
		} else if (q.op == "<=") {
			out << "sle	" << result_reg << ", " << para1_reg << ", " << para2_reg << endl;
		} else if (q.op == ">") {
			out << "sgt	" << result_reg << ", " << para1_reg << ", " << para2_reg << endl;
		} else if (q.op == ">=") {
			out << "sge	" << result_reg << ", " << para1_reg << ", " << para2_reg << endl;
		} else {
			out << "seq	" << result_reg << ", " << para1_reg << ", " << para2_reg << endl;
			if (q.op == "!=") {
				out << "xori	" << result_reg << ", 1" << endl;
			}
		}

	} else if (q.op == "=") {//=	value	blank	IDSY_name
		if (in_reg(q.para1)) {
			out << "move	" << reg_alloc(q.result, "") << ", " << reg_alloc(q.para1, q.result) << endl;
		} else {
			const string IDSY_reg = reg_alloc(q.result, "");
			load_to(q.para1, IDSY_reg);//直接把value load到IDSY对应的寄存器里
		}

	} else if (q.op == "[]=") {//[]=, array_name, index_name, expr_name
		const int array_addr = Table::get_addr(cur_fun_name, q.para1);
		const string index_reg = reg_alloc_and_load(q.para2, "");
		const string expr_reg = reg_alloc_and_load(q.result, q.para2);
		//load_to(q.para2, index_reg);//index
		//load_to(q.result, expr_reg);
		if (Table::is_global(cur_fun_name, q.para1)) {//全局数组
			out << "la	$t0, " << q.para1 << endl;//base绝对地址
		} else {
			out << "li	$t0, " << int2str(array_addr) << endl;//base相对于栈指针的地址
			out << "add	$t0, $t0, $sp" << endl;//现在是绝对地址了
		}
		//$t0:	数组首绝对地址
		out << "mul	$t1, " << index_reg << ", 4" << endl;//offest
		//$t1:	该元素相对于首地址的偏移
		out << "add	$t0, $t0, $t1" << endl;
		//$t0:	该元素绝对地址
		out << "sw	" << expr_reg << ", 0($t0)" << endl;

	} else if (q.op == "=[]") {//=[], array_name, index_name, result
		const int array_addr = Table::get_addr(cur_fun_name, q.para1);
		const string index_reg = reg_alloc_and_load(q.para2, "");
		const string result_reg = reg_alloc(q.result, q.para2);
		//load_to(q.para2, index_reg);//index
		if (Table::is_global(cur_fun_name, q.para1)) {
			out << "la	$t0, " << q.para1 << endl;//base绝对地址
		} else {
			out << "la	$t0, " << int2str(array_addr) << endl;//base相对于栈指针的地址
			out << "add	$t0, $t0 ,$sp" << endl;//绝对地址
		}
		//$t0:	数组首绝对地址
		out << "mul	$t1, " << index_reg << ", 4" << endl;//offest
		//$t1:	该元素相对于首地址的偏移
		out << "add	$t0, $t0, $t1" << endl;
		//$t0:	该元素绝对地址
		out << "lw	" << result_reg << ", 0($t0)" << endl;

	} else if (q.op == "BZ") {//BZ	条件		LABLE，不成立跳转
		const string cond_reg = reg_alloc_and_load(q.para1, "");
		//load_to(q.para1, cond_reg);
		out << "beq	" << cond_reg << ", $0, " << q.para2 << endl;

	} else if (q.op == "BNZ") {//BNZ	条件		LABLE，成立跳转
		const string cond_reg = reg_alloc_and_load(q.para1, "");
		//load_to(q.para1, cond_reg);
		out << "bne	" << cond_reg << ", $0, " << q.para2 << endl;

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
		out	<< cur_fun_name << ":" << endl;
		out << "subi	$sp, $sp, " << int2str(size) << endl;
		out << "sw	$ra, 0($sp)" << endl;
		if (q.para2 != "main") save_in_cal();

	} else if (q.op == "PUSH") {//PUSH	val_name	para_name	fun_name
		if (para_dim_cnt < 4) {//少于4个参数，直接用寄存器传递
			if (in_reg(q.para1)) {
				const string para_reg = reg_alloc(q.para1, "");
				out << "move	" << "$a"+int2str(para_dim_cnt) << ", " << para_reg << endl;
			} else
				load_to(q.para1, "$a"+int2str(para_dim_cnt));
		} else {
			//para_name一定是函数参数名，因此这里没必要用stroe_to()
			const int fun_size = Table::get_fun_size(q.result);
			const int para_addr = Table::get_addr(q.result, q.para2);//参数在被调用函数中的地址
			const string val_reg = reg_alloc_and_load(q.para1, "");
			//load_to(q.para1, val_reg);
			out << "subi	$sp, $sp, " << int2str(fun_size) << endl;
			out << "sw	" << val_reg << ", " << int2str(para_addr) << "($sp)" << endl;
			out << "addi	$sp, $sp, " << int2str(fun_size) << endl;
		}

	} else if (q.op == "CALL") {//CALL	fun_name
		out << "jal	" << q.para1 << endl;
		para_dim_cnt = 0;

	} else if (q.op == "RETURN") {//RETURN	val_type	val_name
		if (cur_fun_name == "main") {
			out << "li	$v0, 10" << endl;
			out << "syscall" << endl;
		}
		if (!Table::is_void_func(cur_fun_name)) {//即非RETURN	NONE
			if (in_reg(q.para2)) {
				const string reg = reg_alloc(q.para2, "");
				out << "move	$v0, " << reg << endl;
			} else 
				load_to(q.para2, "$v0");//返回值
		}
		save_in_return();
		const int size = Table::get_fun_size(cur_fun_name);
		out << "lw	$ra, 0($sp)" << endl;
		out << "addi	$sp, $sp, " << int2str(size) << endl;
		out << "jr	$ra" <<endl;

	} else if (q.op == "END") {//END	fun_name//有返回语句的话不会执行到这
		//主函数只有TERMINATE，没有END
		if (!Table::is_void_func(cur_fun_name)) {
			if (in_reg(q.para2)) {
				const string reg = reg_alloc(q.para2, "");
				out << "move	$v0, " << reg << endl;
			} else 
				load_to(q.para2, "$v0");//返回值
		}
		save_in_return();
		const int size = Table::get_fun_size(cur_fun_name);
		out << "lw	$ra, 0($sp)" << endl;
		out << "addi	$sp, $sp, " << int2str(size) << endl;
		out << "jr	$ra" <<endl;

	} else if (q.op == "LOAD_RETURN_VALUE") {//LOAD_RETURN_VALUE	blank	blank	name
		const string val_reg = reg_alloc(q.result, "");
		out << "move	" << val_reg << ", $v0" << endl;
	}
	else if (q.op == "PRINT") {//PRINT	type	name，type = INTSY/CHARSY/STRING
		if (q.para1 == "INTSY") {
			if (in_reg(q.para2)) {
				const string reg = reg_alloc(q.para2, "");
				out << "move	$a0, " << reg << endl;
			} else
				load_to(q.para2, "$a0");
			out << "li	$v0, 1" << endl;
		} else if (q.para1 == "CHARSY") {
			if (in_reg(q.para2)) {
				const string reg = reg_alloc(q.para2, "");
				out << "move	$a0, " << reg << endl;
			} else
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
		const string reg = reg_alloc(q.para2, "");
		out << "move	" << reg << ", $v0" << endl;
		//store_to(q.para2, "$v0");
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
		out << "li	" << register_name << ", '" << name[1] << "'" << endl;
	} else if (Table::get_CLASS(cur_fun_name, name) == _CLASS::PARA_CLASS &&
		Table::get_dim(cur_fun_name, name) < 4) {
		const int para_cnt = Table::get_dim(cur_fun_name, name);
		out << "move	" << register_name << ", " << "$a"+int2str(para_cnt) << endl;
	}
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

string Translator::reg_alloc(const string name, const string ban_name_1, const string ban_name_2) {
	for (int i=0; i<8; i++)//变量已经申请了寄存器
		if (regs[i] == name)
			return "$s" + int2str(i);
	//变量没有申请过寄存器，这时还要进行写存
	if (regs[counter] == ban_name_1) counter = (counter+1) % 8;
	if (regs[counter] == ban_name_2) counter = (counter+1) % 8;
	string reg = "$s" + int2str(counter);
	if (regs[counter] != "") store_to(regs[counter], reg);
	regs[counter] = name;
	counter = (counter+1) % 8;
	return reg;
}

string Translator::reg_alloc(const string name, const string ban_name) {
	return reg_alloc(name, ban_name, "");
}

string Translator::reg_alloc_and_load(const string name, const string ban_name) {
	for (int i=0; i<8; i++)//变量已经申请了寄存器，就没必要再load了
		if (regs[i] == name)
			return "$s" + int2str(i);
	//变量没有申请过寄存器，这时还要进行写存
	if (regs[counter] == ban_name) counter = (counter+1) % 8;
	string reg = "$s" + int2str(counter);
	if (regs[counter] != "") store_to(regs[counter], reg);
	regs[counter] = name;
	counter = (counter+1) % 8;
	load_to(name, reg);
	return reg;
}

void Translator::save_in_cal() {
	int addr = 4;
	for (int i=0; i<8; i++,addr+=4)
		out << "sw	" << "$s"+int2str(i) << ", " << int2str(addr) << "($sp)" << endl;
}

void Translator::save_in_return() {
	int addr = 4;
	for (int i=0; i<8; i++,addr+=4) {
		if (Table::get_parent(cur_fun_name, regs[i]) == "top") {
			store_to(regs[i], "$s"+int2str(i));
		}
		out << "lw	" << "$s"+int2str(i) << ", " << int2str(addr) << "($sp)" << endl;
		regs[i] = "";
	}
}

bool Translator::in_reg(const string name) {
	for (int i=0; i<8; i++)
		if (regs[i]==name)
			return true;
	return false;
}


