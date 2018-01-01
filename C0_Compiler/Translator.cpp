#include "StdAfx.h"
#include "Translator.h"

/***********DEBUG*************/
bool debug = false;//����������ʾ�м����
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
	out << ".data" << endl;//��ͷ����������
	for (unsigned i=0; i<StringTable::names.size(); i++)//�ַ�����
		out << StringTable::names[i] << ":\t.asciiz\t\"" << StringTable::contents[i] << "\"" << endl;
}

void Translator::proc_quat(const Quaternion q) {
	if (debug) out<< "#" << q.op << "\t" << q.para1 << "\t" << q.para2 << "\t" << q.result << endl;
	if (q.op == "CONST") {//CONST	type	value	name
		if (global) {//ȫ��������
			out << q.result << ": .word\t" << q.para2 <<endl;	
		} else {//����ջ
			const int addr = Table::get_addr(cur_fun_name, q.result);
			out << "li	$t0, " << q.para2 << endl;
			out << "sw	$t0, " << int2str(addr) << "($sp)" << endl;
		}

	} else if (q.op == "VAL") {//VAL	type	blank	name
		if (global) {//ȫ��������
			out << q.result << ": .word\t0" <<endl;	
		} else {//����ջ
			//�൱�ڳ�ʼ����0
		}

	} else if (q.op == "ARRAY") {//ARRAY	type	dim	name
		if (global) {//ȫ��������
			out << q.result << ": .word\t1 : " << q.para2 << endl;//��ʼ����1
		} else {//����ջ
			//�൱�ڳ�ʼ����0
		}


	} else if (q.op=="+" || q.op=="-" || q.op=="*" || q.op=="/" ||
		q.op=="<" || q.op=="<=" || q.op==">" || q.op==">=" || 
		q.op=="==" || q.op=="!=") {//op	para1	para2	result
		//$t0, $t1�д������, $t2�д���
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
		if (Table::is_global(cur_fun_name, q.result)) {//ȫ������
			out << "la	$t0, " << q.result << endl;//base���Ե�ַ
		} else {
			const int array_addr = Table::get_addr(cur_fun_name, q.result);
			out << "li	$t0, " << int2str(array_addr) << endl;//base�����ջָ��ĵ�ַ
			out << "add	$t0, $t0, $sp" << endl;//�����Ǿ��Ե�ַ��
		}
		//$t0:	�����׾��Ե�ַ
		const string index_reg = q.para1=="$v0"?"$v0":"$t1";
		if (index_reg != "$v0")	load_to(q.para1, index_reg);//index
		out << "sll	" << index_reg << ", " << index_reg << ", 2" << endl;//offest
		//$t1:	��Ԫ��������׵�ַ��ƫ��
		out << "add	$t0, $t0, " << index_reg << endl;
		//$t0:	��Ԫ�ؾ��Ե�ַ
		const string expr_reg = q.para2=="$v0"?"$v0":"$t1";
		if (expr_reg != "$v0")	load_to(q.para2, expr_reg);
		out << "sw	" << expr_reg << ", 0($t0)" << endl;

	} else if (q.op == "=[]") {//=[], array_name, index_name, result
		if (Table::is_global(cur_fun_name, q.para1)) {
			out << "la	$t0, " << q.para1 << endl;//base���Ե�ַ
		} else {	
			const int array_addr = Table::get_addr(cur_fun_name, q.para1); 
			out << "la	$t0, " << int2str(array_addr) << endl;//base�����ջָ��ĵ�ַ
			out << "add	$t0, $t0 ,$sp" << endl;//���Ե�ַ
		}
		//$t0:	�����׾��Ե�ַ
		const string index_reg = q.para2=="$v0"?"$v0":"$t1";
		if (index_reg != "$v0")	load_to(q.para2, index_reg);//index
		out << "sll	" << index_reg << ", " << index_reg << ", 2" << endl;//offest
		//$t1:	��Ԫ��������׵�ַ��ƫ��
		out << "add	$t0, $t0, " << index_reg << endl;
		//$t0:	��Ԫ�ؾ��Ե�ַ
		out << "lw	$t0, 0($t0)" << endl;
		store_to(q.result, "$t0");//����ֵ��Ӧ�ò�����$v0��

	} else if (q.op == "BZ") {//BZ	����		LABLE����������ת
		const string bz_reg = q.para1=="$v0"?"$v0":"$t0";
		if (bz_reg != "$v0")	load_to(q.para1, bz_reg);
		out << "beq	" << bz_reg << ", $0, " << q.para2 << endl;

	} else if (q.op == "BNZ") {//BNZ	����		LABLE��������ת
		const string bnz_reg = q.para1=="$v0"?"$v0":"$t0";
		if (bnz_reg != "$v0")	load_to(q.para1, bnz_reg);
		out << "bne	" << bnz_reg << ", $0, " << q.para2 << endl;

	} else if (q.op == "GOTO") {//GOTO	LABLE
		out << "j	" << q.para1 << endl;

	} else if (q.op == "LABLE") {//LABLE	lable_name
		out << q.para1 << ":" << endl;

	} else if (q.op == "FUN" && q.para1 == "BEGIN") {//ȫ�ֱ�����������
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
		//����Ǿ������üĴ��������ˣ���Ϊ��һ������������Ϊ��һ���������������ʱ�򣬻ᷢ�����ش���
		//para_nameһ���Ǻ������������������û��Ҫ��stroe_to()
		const int fun_size = Table::get_fun_size(q.result);
		//const int val_addr = Table::get_addr(cur_fun_name, q.para1);//����Ǵ���Ĳ����ĵ�ַ�������ڱ����ú����еĵ�ַ
		const int para_addr = Table::get_addr(q.result, q.para2);//�����ڱ����ú����еĵ�ַ
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
		if (!Table::is_void_func(cur_fun_name)) {//����RETURN	NONE
			load_to(q.para2, "$v0");//����ֵ
		}
		const int size = Table::get_fun_size(cur_fun_name);
		out << "lw	$ra, 0($sp)" << endl;
		out << "addi	$sp, $sp, " << int2str(size) << endl;
		out << "jr	$ra" <<endl;

	} else if (q.op == "END") {//END	fun_name//�з������Ļ�����ִ�е���
		//������ֻ��TERMINATE��û��END
		if (!Table::is_void_func(cur_fun_name)) {
			load_to(q.para2, "$v0");//����ֵ
		}
		const int size = Table::get_fun_size(cur_fun_name);
		out << "lw	$ra, 0($sp)" << endl;
		out << "addi	$sp, $sp, " << int2str(size) << endl;
		out << "jr	$ra" <<endl;

	} else if (q.op == "LOAD_RETURN_VALUE") {//LOAD_RETURN_VALUE	blank	blank	name
		store_to(q.result, "$v0");
	}
	else if (q.op == "PRINT") {//PRINT	type	name��type = INTSY/CHARSY/STRING
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
	if (isnum(name)) {//����
		out << "li	" << register_name << ", " << name << endl;
	} else if (name[0] == '$') {//�ַ�
		out << "li	" << register_name << ", " << name.substr(1) << endl;
	} /*else if (Table::get_CLASS(cur_fun_name, name) == _CLASS::PARA_CLASS &&
		Table::get_dim(cur_fun_name, name) < 4) {
		const int para_cnt = Table::get_dim(cur_fun_name, name);
		out << "move	" << register_name << ", " << "$a"+int2str(para_cnt) << endl;
	}*/
	//������ͨ������ջ����
	else if (Table::is_global(cur_fun_name, name)) {//ȫ����
		//out << "la	" << register_name << ", " << name << endl;
		//out << "lw	" << register_name << ", 0(" << register_name << ")" << endl;
		out << "lw	" << register_name << ", " << name << endl;
	} else {//�ֲ���
		const int addr = Table::get_addr(cur_fun_name, name);
		out << "lw	" << register_name << ", " << int2str(addr) << "($sp)" << endl;
	}
}

void Translator::store_to(const string name, const string register_name) {
	if (isnum(name)) {} //����
	else if (name[0] == '$') {} //�ַ�
	else if (Table::is_global(cur_fun_name, name)) {
		out << "sw	" << register_name << ", " << name << endl;
	} else {
		const int addr = Table::get_addr(cur_fun_name, name);
		out << "sw	" << register_name << ", " << int2str(addr) << "($sp)" << endl;
	}
}
