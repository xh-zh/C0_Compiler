#include "StdAfx.h"
#include "Translator.h"

/***********DEBUG*************/
bool debug = false;//汇编代码中显示中间代码
bool show_regisiter_descriptor = false;//汇编代码中显示寄存器描述符
/***********DEBUG*************/

ofstream Translator::out;
bool Translator::global = true;
string Translator::cur_fun_name = "top";
vector<string> Translator::register_descriptor[10];//$t0-$t9的寄存器描述符

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
	global = true;
	out = ofstream(path);
	out << ".data" << endl;//开头就是数据区
	for (unsigned i=0; i<StringTable::names.size(); i++)//字符串表
		out << StringTable::names[i] << ":\t.asciiz\t\"" << StringTable::contents[i] << "\"" << endl;
}

void Translator::proc_quat(const Quaternion q) {
	if (debug) out<< "#" << q.op << "\t" << q.para1 << "\t" << q.para2 << "\t" << q.result << endl;
	if (show_regisiter_descriptor) 
		for (int i=0; i<10; i++) {
			out << "# $t" << i << "\t";
			for (vector<string>::iterator iter=register_descriptor[i].begin(); iter != register_descriptor[i].end(); ++iter)
				out << *iter << "\t";
			out << endl;
		}
	if (q.op == "~CONST") {//CONST	type	value	name
		if (global) {//全局数据区
			out << q.result << ": .word\t" << q.para2 <<endl;	
		} else {//运行栈
			const int addr = Table::get_addr(cur_fun_name, q.result);
			out << "li	$t0, " << q.para2 << endl;
			out << "sw	$t0, " << int2str(addr) << "($sp)" << endl;
		}

	} else if (q.op == "~VAL") {//VAL	type	blank	name
		if (global) {//全局数据区
			out << q.result << ": .word\t0" <<endl;	
		} else {//运行栈
			//相当于初始化成0
		}

	} else if (q.op == "~ARRAY") {//ARRAY	type	dim	name
		if (global) {//全局数据区
			out << q.result << ": .word\t1 : " << q.para2 << endl;//初始化成1
		} else {//运行栈
			//相当于初始化成0
		}


	} else if (q.op=="+" || q.op=="-" || q.op=="*" || q.op=="/" ||
		q.op=="<" || q.op=="<=" || q.op==">" || q.op==">=" || 
		q.op=="==" || q.op=="!=") {//op	para1	para2	result

		string result_reg;
		const string para1_reg = get_read_reg(q.para1, "$a2", "", "");
		const string para2_reg = get_read_reg(q.para2, "$a3", para1_reg, "");
		if (Table::only_in_stack(cur_fun_name, q.result)) {
			//result_reg = tmp_reg_alloc(q.result, para1_reg, para2_reg);
			result_reg = tmp_reg_alloc(q.result, "", "");
		} else {
			//result_reg = tmp_reg_alloc_for_alloced_val(q.result, para1_reg, para2_reg);
			result_reg = tmp_reg_alloc_for_alloced_val(q.result, "", "");
		}
		refresh_reg(q.result, result_reg);

		if (q.op == "+") {
			out << "add	" << result_reg <<", " << para1_reg << ", " << para2_reg <<endl;
		} else if (q.op == "-") {
			if (q.para1 == "0")
				out << "neg	" << result_reg <<", " << para2_reg << endl;
			else 
				out << "sub	" << result_reg <<", " << para1_reg << ", " << para2_reg <<endl;
		} else if (q.op == "*") {
			out << "mul	" << result_reg <<", " << para1_reg << ", " << para2_reg <<endl;
		} else if (q.op == "/") {
			out << "div	" << para1_reg << ", " << para2_reg <<endl;
			out << "mflo	" << result_reg <<"" << endl;
		} else if (q.op == "<") {
			out << "slt	" << result_reg <<", " << para1_reg << ", " << para2_reg <<endl;
		} else if (q.op == "<=") {
			out << "sle	" << result_reg <<", " << para1_reg << ", " << para2_reg <<endl;
		} else if (q.op == ">") {
			out << "sgt	" << result_reg <<", " << para1_reg << ", " << para2_reg <<endl;
		} else if (q.op == ">=") {
			out << "sge	" << result_reg <<", " << para1_reg << ", " << para2_reg <<endl;
		} else {
			out << "seq	" << result_reg <<", " << para1_reg << ", " << para2_reg <<endl;
			if (q.op == "!=") {
				out << "xori	" << result_reg <<", 1" << endl;
			}
		}

	} else if (q.op == "=") {//=	value	blank	IDSY_name
		string result_reg;
		if (q.para1 != "$v0") {
			if (isnum(q.para1) || q.para1[0]=='$') {
				if (Table::only_in_stack(cur_fun_name, q.result)) {
					result_reg = tmp_reg_alloc(q.result, "", "");
				} else {
					result_reg = tmp_reg_alloc_for_alloced_val(q.result, "", "");
				}
				refresh_reg(q.result, result_reg);
				if (isnum(q.para1)) {
					out << "li	" << result_reg << ", " << q.para1 << endl;
				} else {
					out << "li	" << result_reg << ", " << q.para1.substr(1) << endl;
				}
			} else {
				const string para1_reg = get_read_reg(q.para1, "$a3", "", "");
				add_to_reg_des(q.result, para1_reg);
				refresh_reg(q.result, para1_reg);
			}
			
		} else {
			if (Table::only_in_stack(cur_fun_name, q.result)) {
				result_reg = tmp_reg_alloc(q.result, "", "");
			} else {
				result_reg = tmp_reg_alloc_for_alloced_val(q.result, "", "");
			}
			refresh_reg(q.result, result_reg);
			out << "move	" << result_reg << ", $v0" << endl;
		}

	} else if (q.op == "[]=") {//[]=, index_name, expr_name, array_name
		const string tmp_reg = "$a2";
		if (Table::is_global(cur_fun_name, q.result)) {//全局数组
			out << "la	" << tmp_reg << ", " << q.result << endl;//base绝对地址
		} else {
			const int array_addr = Table::get_addr(cur_fun_name, q.result);
			out << "li	" << tmp_reg << ", " << int2str(array_addr) << endl;//base相对于栈指针的地址
			out << "add	" << tmp_reg << ", " << tmp_reg << ", $sp" << endl;//现在是绝对地址了
		}
		//tmp_reg:	数组首绝对地址
		const string index_reg = get_read_reg(q.para1, "$a3", "", "");
		out << "sll	" << "$a3" << ", " << index_reg << ", 2" << endl;//offest
		//$v1:	该元素相对于首地址的偏移
		out << "add	" << tmp_reg << ", " << tmp_reg << ", " << "$a3" << endl;
		//tmp_reg:	该元素绝对地址
		const string expr_reg = get_read_reg(q.para2, "$a3", index_reg, "");
		out << "sw	" << expr_reg << ", 0(" << tmp_reg << ")" << endl;

	} else if (q.op == "=[]") {//=[], array_name, index_name, result
		const string tmp_reg = "$a2";
		if (Table::is_global(cur_fun_name, q.para1)) {
			out << "la	" << tmp_reg << ", " << q.para1 << endl;//base绝对地址
		} else {	
			const int array_addr = Table::get_addr(cur_fun_name, q.para1); 
			out << "la	" << tmp_reg << ", " << int2str(array_addr) << endl;//base相对于栈指针的地址
			out << "add	" << tmp_reg << ", " << tmp_reg << " ,$sp" << endl;//绝对地址
		}
		//tmp_reg:	数组首绝对地址
		const string index_reg = get_read_reg(q.para2, "$a3", "", "");
		out << "sll	" << "$a3" << ", " << index_reg << ", 2" << endl;//offest
		//$v1:	该元素相对于首地址的偏移
		out << "add	" << tmp_reg << ", " << tmp_reg << ", " << "$a3" << endl;
		//tmp_reg:	该元素绝对地址
		string result_reg;
		if (Table::only_in_stack(cur_fun_name, q.result)) {
			result_reg = tmp_reg_alloc(q.result, "", "");
		} else {
			result_reg = tmp_reg_alloc_for_alloced_val(q.result, "", "");
		}
		refresh_reg(q.result, result_reg);
		out << "lw	" << result_reg << ", 0(" << tmp_reg << ")" << endl;

	} else if (q.op == "~BZ") {//BZ	条件		LABLE，不成立跳转
		save_all_val();
		//这里如果没save的话是不能直接load 的，因为不能保证栈中存放了正确的值
		const string bz_reg = q.para1=="$v0"?"$v0":"$a3";
		if (bz_reg != "$v0")	load_to(q.para1, bz_reg);
		out << "beq	" << bz_reg << ", $0, " << q.para2 << endl;

	} else if (q.op == "~BNZ") {//BNZ	条件		LABLE，成立跳转
		save_all_val();
		//这里如果没save的话是不能直接load 的，因为不能保证栈中存放了正确的值
		const string bnz_reg = q.para1=="$v0"?"$v0":"$a3";
		if (bnz_reg != "$v0")	load_to(q.para1, bnz_reg);
		out << "bne	" << bnz_reg << ", $0, " << q.para2 << endl;

	} else if (q.op == "~GOTO") {//GOTO	LABLE
		save_all_val();
		out << "j	" << q.para1 << endl;

	} else if (q.op == "~LABLE") {//LABLE	lable_name
		save_all_val();
		out << q.para1 << ":" << endl;

	} else if (q.op == "~FUN" && q.para1 == "~BEGIN") {//全局变量声明结束
		out << ".text" << endl;
		out << "j	main" << endl;
		global = false;

	} else if (q.op == "~FUN") {//FUN	INTSY	fun_name
		clear_register_descriptor();
		cur_fun_name = q.para2;
		const int size = Table::get_fun_size(cur_fun_name);
		out << cur_fun_name << ":" << endl;
		out << "subi	$sp, $sp, " << int2str(size) << endl;
		out << "sw	$ra, 0($sp)" << endl;

	} else if (q.op == "~PUSH") {//PUSH	val_name	para_name	fun_name
		//最后还是决定不用寄存器传参了，因为当一个函数调用作为另一个函数参数传入的时候，会发生严重错误
		//para_name一定是函数参数名，因此这里没必要用stroe_to()
		const int fun_size = Table::get_fun_size(q.result);
		//const int val_addr = Table::get_addr(cur_fun_name, q.para1);//这个是传入的参数的地址，不是在被调用函数中的地址
		const int para_addr = Table::get_addr(q.result, q.para2);//参数在被调用函数中的地址
		const string val_reg = get_read_reg(q.para1, "$a3", "", "");
		out << "subi	$sp, $sp, " << int2str(fun_size) << endl;
		out << "sw	" << val_reg << ", " << int2str(para_addr) << "($sp)" << endl;
		out << "addi	$sp, $sp, " << int2str(fun_size) << endl;

	} else if (q.op == "~CALL") {//CALL	fun_name
		save_all_val();
		out << "jal	" << q.para1 << endl;

	} else if (q.op == "~RETURN") {//RETURN	val_type	val_name
		if (cur_fun_name == "main") {
			//这里就不保存寄存器里的未保存值了
			out << "li	$v0, 10" << endl;
			out << "syscall" << endl;
			
		} else {
			save_all_val();
			if (!Table::is_void_func(cur_fun_name)) {//即非RETURN	NONE			
				//这里如果没save的话是不能直接load 的，因为不能保证栈中存放了正确的值
				load_to(q.para2, "$v0");//返回值
			}
			const int size = Table::get_fun_size(cur_fun_name);
			out << "lw	$ra, 0($sp)" << endl;
			out << "addi	$sp, $sp, " << int2str(size) << endl;
			out << "jr	$ra" <<endl;
		}

	} else if (q.op == "~END") {//END	fun_name//有返回语句的话不会执行到这
		//主函数只有TERMINATE，没有END
		save_all_val();
		if (!Table::is_void_func(cur_fun_name)) {
			//这里如果没save的话是不能直接load 的，因为不能保证栈中存放了正确的值
			load_to(q.para2, "$v0");//返回值
		}
		const int size = Table::get_fun_size(cur_fun_name);
		out << "lw	$ra, 0($sp)" << endl;
		out << "addi	$sp, $sp, " << int2str(size) << endl;
		out << "jr	$ra" <<endl;

	}
	else if (q.op == "~PRINT") {//PRINT	type	name，type = INTSY/CHARSY/STRING
		if (q.para1 == "!STRING") {
			out << "la	$a0, " << q.para2 << endl;
			out << "li	$v0, 4" << endl;
		} else {
			if (isnum(q.para2) || (q.para2[0] == '$' && q.para2 != "$v0")) {
				get_read_reg(q.para2, "$a0", "", "");
			} else {
				const string prt_reg = get_read_reg(q.para2, "$a0", "", "");
				out << "move	$a0, " << prt_reg << endl;
			}

			if (q.para1 == "!INTSY") {
				out << "li	$v0, 1" << endl;
			} else {//CHARSY
				out << "li	$v0, 11" << endl;
			}
		}
		out << "syscall" << endl;

	} else if (q.op == "~SCANF") {//SCANF	type	name
		if (q.para1 == "!INTSY") {
			out << "li	$v0, 5" << endl;
		} else {
			out << "li	$v0, 12" << endl;
		}
		out << "syscall" << endl;
		string scf_reg;
		if (Table::only_in_stack(cur_fun_name, q.para2)) {
			scf_reg = tmp_reg_alloc(q.para2, "", "");
		} else {
			scf_reg = tmp_reg_alloc_for_alloced_val(q.para2, "", "");
		}
		Table::clear_addr(cur_fun_name, q.para2);
		Table::add_addr(cur_fun_name, q.para2, scf_reg);
		out << "move	" << scf_reg << ", $v0" << endl;
	} else if (q.op == "~TERMINATE") {
		out << "li	$v0, 10" << endl;
		out << "syscall" << endl;
	}
	if (debug) out << endl;
}

void Translator::translate() {
	for (unsigned i=0; i<Intermediate_code::code.size(); i++)
		proc_quat(Intermediate_code::code[i]);
	out.close();
}

void Translator::load_to(const string name, const string register_name) {
	if (isnum(name)) {//数字
		out << "li	" << register_name << ", " << name << endl;
	} else if (name[0] == '$') {//字符
		out << "li	" << register_name << ", " << name.substr(1) << endl;
	} 
	//参数都通过运行栈传递
	else if (Table::is_global(cur_fun_name, name)) {//全局量
		out << "lw	" << register_name << ", " << name << endl;
	} else {//局部量
		const int addr = Table::get_addr(cur_fun_name, name);
		out << "lw	" << register_name << ", " << int2str(addr) << "($sp)" << endl;
	}
}

string Translator::get_read_reg(const string name, const string register_name, const string ban_reg1, const string ban_reg2) {
	if (name == "$v0") {
		return "$v0";
	}
	if (isnum(name)) {//数字
		out << "li	" << register_name << ", " << name << endl;
		return register_name;
	}
	if (name[0] == '$') {//字符
		out << "li	" << register_name << ", " << name.substr(1) << endl;
		return register_name;
	}
	string reg;
	if (!Table::only_in_stack(cur_fun_name, name)) {
		reg = Table::get_reg(cur_fun_name, name);
	} else {
		reg = tmp_reg_alloc(name, ban_reg1, ban_reg2);
		load_to(name, reg);
	}
	return reg;
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

//这个方法只对未分配寄存器的变量申请寄存器
string Translator::tmp_reg_alloc(const string name, const string ban_reg1, const string ban_reg2) {
	if (!Table::contain(cur_fun_name, name)) {
		return "";
	}
	for	(int i=0; i<10; i++) {//有空寄存器直接分配
		if (register_descriptor[i].empty()) {
			const string reg = "$t" + int2str(i);
			//更新变量的地址描述符
			Table::add_addr(cur_fun_name, name, reg);
			//更新寄存器的变量描述符
			add_to_reg_des(name, i);
			return reg;
		}
	}
	/********************无空寄存器，搜索一个淘汰代价较小的寄存器，淘汰之*********************/
	int index = 0;
	for	(int i=0; i<10; i++) {
		if ((ban_reg1=="" || i != ban_reg1[ban_reg1.size()-1]-'0') &&
			(ban_reg2=="" || i != ban_reg2[ban_reg2.size()-1]-'0')) {
			index = i;
			break;
		}
	}
	for (int i=1; i<10; i++)
		if (register_descriptor[i].size() < register_descriptor[index].size() &&
			(ban_reg1=="" || i != ban_reg1[ban_reg1.size()-1]-'0') &&
			(ban_reg2=="" || i != ban_reg2[ban_reg2.size()-1]-'0')) {
			index = i;
		}
	//$t_index中保存的变量最少，将这个寄存器淘汰
	const string reg = "$t" + int2str(index);
	//淘汰原有变量
	for (vector<string>::iterator iter = register_descriptor[index].begin(); iter != register_descriptor[index].end(); ++iter) {
		if (Table::only_here(cur_fun_name, *iter, reg) && *iter != name) {//原有变量只存在于这个寄存器中, 且不是将要分配给的变量
			store_to(*iter, reg);
			Table::clear_addr(cur_fun_name, *iter);
			Table::add_stack_addr(cur_fun_name, *iter);
		} else {//原有变量在别处有备份
			Table::del_addr(cur_fun_name, *iter, reg);
		}
	}
	//更新寄存器描述符
	register_descriptor[index].clear();
	add_to_reg_des(name, index);
	//分配给当前变量
	Table::add_addr(cur_fun_name, name, reg);
	return reg;
}

//这个方法只对已分配寄存器的变量申请代价最小的寄存器，为写入做准备
//因为如果是只读的话，已分配寄存器的变量是不需要再次分配的
string Translator::tmp_reg_alloc_for_alloced_val(const string name, const string ban_reg1, string ban_reg2) {
	if (!Table::contain(cur_fun_name, name)) {
		return "";
	}
	vector<string> v = Table::get_address_descriptor(cur_fun_name, name);
	const string tmp_reg = Table::get_reg(cur_fun_name, name);//先随便找一个寄存器作为最小引用寄存器
	int min_pay_reg_index = tmp_reg[tmp_reg.size()-1] - '0';//当前最小寄存器号
	for (vector<string>::iterator iter=v.begin(); iter!=v.end(); ++iter) {
		if (!isnum(*iter)) {//不是栈中的地址
			const int index = (*iter)[(*iter).size()-1] - '0';//正在遍历的寄存器号
			if (register_descriptor[index].size() < register_descriptor[min_pay_reg_index].size()) {
				min_pay_reg_index = index;
			}
		}
	}
	const int min_reg_size = register_descriptor[min_pay_reg_index].size();//此寄存器中变量个数
	if (min_reg_size == 1) {//这个寄存器只存了name这一个变量
		return "$t"+int2str(min_pay_reg_index);
	}
	//寄存器中不止name这一个变量，则从全部寄存器中搜索
	for (int i=0; i<10; i++) {
		if (register_descriptor[i].size() < min_reg_size-1 && 
			register_descriptor[i].size() < register_descriptor[min_pay_reg_index].size()
			&& (ban_reg1=="" || i != ban_reg1[ban_reg1.size()-1]-'0')
			&& (ban_reg2=="" || i != ban_reg2[ban_reg2.size()-1]-'0')) {
			min_pay_reg_index = i;
		}
	}
	const string reg = "$t" + int2str(min_pay_reg_index);//选中寄存器
	if (register_descriptor[min_pay_reg_index].size() != 0) {//该寄存器中有别的变量
		//淘汰原有变量
		for (vector<string>::iterator iter = register_descriptor[min_pay_reg_index].begin(); iter != register_descriptor[min_pay_reg_index].end(); ++iter) {
			if (Table::only_here(cur_fun_name, *iter, reg) && *iter != name) {//寄存器中原有变量只存在于这个寄存器中
				store_to(*iter, reg);
				Table::clear_addr(cur_fun_name, *iter);
				Table::add_stack_addr(cur_fun_name, *iter);
			} else {//寄存器中原有变量在别处有备份
				Table::del_addr(cur_fun_name, *iter, reg);
			}
		}
	}
	//更新寄存器描述符
	register_descriptor[min_pay_reg_index].clear();
	add_to_reg_des(name, min_pay_reg_index);
	//更新变量地址描述符
	//Table::clear_addr(cur_fun_name, name);
	Table::add_addr(cur_fun_name, name, reg);
	return reg;
}

void Translator::save_all_val() {
	for (int i=0; i<10; i++) {
		for (vector<string>::iterator iter=register_descriptor[i].begin(); iter!=register_descriptor[i].end(); ++iter) {
			if (!Table::in_stack(cur_fun_name, *iter)) {//保存所有不在栈中的变量
				store_to(*iter, "$t"+int2str(i));
			}
		}
		for (vector<string>::iterator iter=register_descriptor[i].begin(); iter!=register_descriptor[i].end(); ++iter) {
			Table::clear_addr(cur_fun_name, *iter);
			Table::add_stack_addr(cur_fun_name, *iter);
		}
	}
	clear_register_descriptor();
}

void Translator::clear_register_descriptor() {
	for	(int i=0; i<10; i++)
		register_descriptor[i].clear();
}

void Translator::refresh_reg(const string name, const string register_name) {
	for (int i=0; i< Table::get_address_descriptor(cur_fun_name, name).size(); i++) {
		const string reg_name =  Table::get_address_descriptor(cur_fun_name, name)[i];
		del_from_reg_des(name, reg_name);
	}
	add_to_reg_des(name, register_name);
	Table::clear_addr(cur_fun_name, name);
	Table::add_addr(cur_fun_name, name, register_name);
}

void Translator::add_to_reg_des(const string name, const string register_name) {
	for	(int i=0; i<register_descriptor[register_name[register_name.size()-1]-'0'].size(); i++) {
		if (register_descriptor[register_name[register_name.size()-1]-'0'][i] == name) {
			return;
		}
	}
	register_descriptor[register_name[register_name.size()-1]-'0'].push_back(name);
}

void Translator::add_to_reg_des(const string name, const int register_index) {
	add_to_reg_des(name, "$t"+int2str(register_index));
}

void Translator::del_from_reg_des(const string name, const string register_name) {
	for (vector<string>::iterator iter = register_descriptor[register_name[register_name.size()-1]-'0'].begin(); iter!=register_descriptor[register_name[register_name.size()-1]-'0'].end(); ++iter) {
			if (*iter == name) {
				register_descriptor[register_name[register_name.size()-1]-'0'].erase(iter);
				break;
			}
		}
}

