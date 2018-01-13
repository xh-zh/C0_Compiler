#include "StdAfx.h"
#include "Translator.h"

/***********DEBUG*************/
bool debug = false;//����������ʾ�м����
bool show_regisiter_descriptor = false;//����������ʾ�Ĵ���������
/***********DEBUG*************/

ofstream Translator::out;
bool Translator::global = true;
string Translator::cur_fun_name = "top";
vector<string> Translator::register_descriptor[10];//$t0-$t9�ļĴ���������

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
	out << ".data" << endl;//��ͷ����������
	for (unsigned i=0; i<StringTable::names.size(); i++)//�ַ�����
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
		if (global) {//ȫ��������
			out << q.result << ": .word\t" << q.para2 <<endl;	
		} else {//����ջ
			const int addr = Table::get_addr(cur_fun_name, q.result);
			out << "li	$t0, " << q.para2 << endl;
			out << "sw	$t0, " << int2str(addr) << "($sp)" << endl;
		}

	} else if (q.op == "~VAL") {//VAL	type	blank	name
		if (global) {//ȫ��������
			out << q.result << ": .word\t0" <<endl;	
		} else {//����ջ
			//�൱�ڳ�ʼ����0
		}

	} else if (q.op == "~ARRAY") {//ARRAY	type	dim	name
		if (global) {//ȫ��������
			out << q.result << ": .word\t1 : " << q.para2 << endl;//��ʼ����1
		} else {//����ջ
			//�൱�ڳ�ʼ����0
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
		if (Table::is_global(cur_fun_name, q.result)) {//ȫ������
			out << "la	" << tmp_reg << ", " << q.result << endl;//base���Ե�ַ
		} else {
			const int array_addr = Table::get_addr(cur_fun_name, q.result);
			out << "li	" << tmp_reg << ", " << int2str(array_addr) << endl;//base�����ջָ��ĵ�ַ
			out << "add	" << tmp_reg << ", " << tmp_reg << ", $sp" << endl;//�����Ǿ��Ե�ַ��
		}
		//tmp_reg:	�����׾��Ե�ַ
		const string index_reg = get_read_reg(q.para1, "$a3", "", "");
		out << "sll	" << "$a3" << ", " << index_reg << ", 2" << endl;//offest
		//$v1:	��Ԫ��������׵�ַ��ƫ��
		out << "add	" << tmp_reg << ", " << tmp_reg << ", " << "$a3" << endl;
		//tmp_reg:	��Ԫ�ؾ��Ե�ַ
		const string expr_reg = get_read_reg(q.para2, "$a3", index_reg, "");
		out << "sw	" << expr_reg << ", 0(" << tmp_reg << ")" << endl;

	} else if (q.op == "=[]") {//=[], array_name, index_name, result
		const string tmp_reg = "$a2";
		if (Table::is_global(cur_fun_name, q.para1)) {
			out << "la	" << tmp_reg << ", " << q.para1 << endl;//base���Ե�ַ
		} else {	
			const int array_addr = Table::get_addr(cur_fun_name, q.para1); 
			out << "la	" << tmp_reg << ", " << int2str(array_addr) << endl;//base�����ջָ��ĵ�ַ
			out << "add	" << tmp_reg << ", " << tmp_reg << " ,$sp" << endl;//���Ե�ַ
		}
		//tmp_reg:	�����׾��Ե�ַ
		const string index_reg = get_read_reg(q.para2, "$a3", "", "");
		out << "sll	" << "$a3" << ", " << index_reg << ", 2" << endl;//offest
		//$v1:	��Ԫ��������׵�ַ��ƫ��
		out << "add	" << tmp_reg << ", " << tmp_reg << ", " << "$a3" << endl;
		//tmp_reg:	��Ԫ�ؾ��Ե�ַ
		string result_reg;
		if (Table::only_in_stack(cur_fun_name, q.result)) {
			result_reg = tmp_reg_alloc(q.result, "", "");
		} else {
			result_reg = tmp_reg_alloc_for_alloced_val(q.result, "", "");
		}
		refresh_reg(q.result, result_reg);
		out << "lw	" << result_reg << ", 0(" << tmp_reg << ")" << endl;

	} else if (q.op == "~BZ") {//BZ	����		LABLE����������ת
		save_all_val();
		//�������ûsave�Ļ��ǲ���ֱ��load �ģ���Ϊ���ܱ�֤ջ�д������ȷ��ֵ
		const string bz_reg = q.para1=="$v0"?"$v0":"$a3";
		if (bz_reg != "$v0")	load_to(q.para1, bz_reg);
		out << "beq	" << bz_reg << ", $0, " << q.para2 << endl;

	} else if (q.op == "~BNZ") {//BNZ	����		LABLE��������ת
		save_all_val();
		//�������ûsave�Ļ��ǲ���ֱ��load �ģ���Ϊ���ܱ�֤ջ�д������ȷ��ֵ
		const string bnz_reg = q.para1=="$v0"?"$v0":"$a3";
		if (bnz_reg != "$v0")	load_to(q.para1, bnz_reg);
		out << "bne	" << bnz_reg << ", $0, " << q.para2 << endl;

	} else if (q.op == "~GOTO") {//GOTO	LABLE
		save_all_val();
		out << "j	" << q.para1 << endl;

	} else if (q.op == "~LABLE") {//LABLE	lable_name
		save_all_val();
		out << q.para1 << ":" << endl;

	} else if (q.op == "~FUN" && q.para1 == "~BEGIN") {//ȫ�ֱ�����������
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
		//����Ǿ������üĴ��������ˣ���Ϊ��һ������������Ϊ��һ���������������ʱ�򣬻ᷢ�����ش���
		//para_nameһ���Ǻ������������������û��Ҫ��stroe_to()
		const int fun_size = Table::get_fun_size(q.result);
		//const int val_addr = Table::get_addr(cur_fun_name, q.para1);//����Ǵ���Ĳ����ĵ�ַ�������ڱ����ú����еĵ�ַ
		const int para_addr = Table::get_addr(q.result, q.para2);//�����ڱ����ú����еĵ�ַ
		const string val_reg = get_read_reg(q.para1, "$a3", "", "");
		out << "subi	$sp, $sp, " << int2str(fun_size) << endl;
		out << "sw	" << val_reg << ", " << int2str(para_addr) << "($sp)" << endl;
		out << "addi	$sp, $sp, " << int2str(fun_size) << endl;

	} else if (q.op == "~CALL") {//CALL	fun_name
		save_all_val();
		out << "jal	" << q.para1 << endl;

	} else if (q.op == "~RETURN") {//RETURN	val_type	val_name
		if (cur_fun_name == "main") {
			//����Ͳ�����Ĵ������δ����ֵ��
			out << "li	$v0, 10" << endl;
			out << "syscall" << endl;
			
		} else {
			save_all_val();
			if (!Table::is_void_func(cur_fun_name)) {//����RETURN	NONE			
				//�������ûsave�Ļ��ǲ���ֱ��load �ģ���Ϊ���ܱ�֤ջ�д������ȷ��ֵ
				load_to(q.para2, "$v0");//����ֵ
			}
			const int size = Table::get_fun_size(cur_fun_name);
			out << "lw	$ra, 0($sp)" << endl;
			out << "addi	$sp, $sp, " << int2str(size) << endl;
			out << "jr	$ra" <<endl;
		}

	} else if (q.op == "~END") {//END	fun_name//�з������Ļ�����ִ�е���
		//������ֻ��TERMINATE��û��END
		save_all_val();
		if (!Table::is_void_func(cur_fun_name)) {
			//�������ûsave�Ļ��ǲ���ֱ��load �ģ���Ϊ���ܱ�֤ջ�д������ȷ��ֵ
			load_to(q.para2, "$v0");//����ֵ
		}
		const int size = Table::get_fun_size(cur_fun_name);
		out << "lw	$ra, 0($sp)" << endl;
		out << "addi	$sp, $sp, " << int2str(size) << endl;
		out << "jr	$ra" <<endl;

	}
	else if (q.op == "~PRINT") {//PRINT	type	name��type = INTSY/CHARSY/STRING
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
	if (isnum(name)) {//����
		out << "li	" << register_name << ", " << name << endl;
	} else if (name[0] == '$') {//�ַ�
		out << "li	" << register_name << ", " << name.substr(1) << endl;
	} 
	//������ͨ������ջ����
	else if (Table::is_global(cur_fun_name, name)) {//ȫ����
		out << "lw	" << register_name << ", " << name << endl;
	} else {//�ֲ���
		const int addr = Table::get_addr(cur_fun_name, name);
		out << "lw	" << register_name << ", " << int2str(addr) << "($sp)" << endl;
	}
}

string Translator::get_read_reg(const string name, const string register_name, const string ban_reg1, const string ban_reg2) {
	if (name == "$v0") {
		return "$v0";
	}
	if (isnum(name)) {//����
		out << "li	" << register_name << ", " << name << endl;
		return register_name;
	}
	if (name[0] == '$') {//�ַ�
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
	if (isnum(name)) {} //����
	else if (name[0] == '$') {} //�ַ�
	else if (Table::is_global(cur_fun_name, name)) {
		out << "sw	" << register_name << ", " << name << endl;
	} else {
		const int addr = Table::get_addr(cur_fun_name, name);
		out << "sw	" << register_name << ", " << int2str(addr) << "($sp)" << endl;
	}
}

//�������ֻ��δ����Ĵ����ı�������Ĵ���
string Translator::tmp_reg_alloc(const string name, const string ban_reg1, const string ban_reg2) {
	if (!Table::contain(cur_fun_name, name)) {
		return "";
	}
	for	(int i=0; i<10; i++) {//�пռĴ���ֱ�ӷ���
		if (register_descriptor[i].empty()) {
			const string reg = "$t" + int2str(i);
			//���±����ĵ�ַ������
			Table::add_addr(cur_fun_name, name, reg);
			//���¼Ĵ����ı���������
			add_to_reg_des(name, i);
			return reg;
		}
	}
	/********************�޿ռĴ���������һ����̭���۽�С�ļĴ�������̭֮*********************/
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
	//$t_index�б���ı������٣�������Ĵ�����̭
	const string reg = "$t" + int2str(index);
	//��̭ԭ�б���
	for (vector<string>::iterator iter = register_descriptor[index].begin(); iter != register_descriptor[index].end(); ++iter) {
		if (Table::only_here(cur_fun_name, *iter, reg) && *iter != name) {//ԭ�б���ֻ����������Ĵ�����, �Ҳ��ǽ�Ҫ������ı���
			store_to(*iter, reg);
			Table::clear_addr(cur_fun_name, *iter);
			Table::add_stack_addr(cur_fun_name, *iter);
		} else {//ԭ�б����ڱ��б���
			Table::del_addr(cur_fun_name, *iter, reg);
		}
	}
	//���¼Ĵ���������
	register_descriptor[index].clear();
	add_to_reg_des(name, index);
	//�������ǰ����
	Table::add_addr(cur_fun_name, name, reg);
	return reg;
}

//�������ֻ���ѷ���Ĵ����ı������������С�ļĴ�����Ϊд����׼��
//��Ϊ�����ֻ���Ļ����ѷ���Ĵ����ı����ǲ���Ҫ�ٴη����
string Translator::tmp_reg_alloc_for_alloced_val(const string name, const string ban_reg1, string ban_reg2) {
	if (!Table::contain(cur_fun_name, name)) {
		return "";
	}
	vector<string> v = Table::get_address_descriptor(cur_fun_name, name);
	const string tmp_reg = Table::get_reg(cur_fun_name, name);//�������һ���Ĵ�����Ϊ��С���üĴ���
	int min_pay_reg_index = tmp_reg[tmp_reg.size()-1] - '0';//��ǰ��С�Ĵ�����
	for (vector<string>::iterator iter=v.begin(); iter!=v.end(); ++iter) {
		if (!isnum(*iter)) {//����ջ�еĵ�ַ
			const int index = (*iter)[(*iter).size()-1] - '0';//���ڱ����ļĴ�����
			if (register_descriptor[index].size() < register_descriptor[min_pay_reg_index].size()) {
				min_pay_reg_index = index;
			}
		}
	}
	const int min_reg_size = register_descriptor[min_pay_reg_index].size();//�˼Ĵ����б�������
	if (min_reg_size == 1) {//����Ĵ���ֻ����name��һ������
		return "$t"+int2str(min_pay_reg_index);
	}
	//�Ĵ����в�ֹname��һ�����������ȫ���Ĵ���������
	for (int i=0; i<10; i++) {
		if (register_descriptor[i].size() < min_reg_size-1 && 
			register_descriptor[i].size() < register_descriptor[min_pay_reg_index].size()
			&& (ban_reg1=="" || i != ban_reg1[ban_reg1.size()-1]-'0')
			&& (ban_reg2=="" || i != ban_reg2[ban_reg2.size()-1]-'0')) {
			min_pay_reg_index = i;
		}
	}
	const string reg = "$t" + int2str(min_pay_reg_index);//ѡ�мĴ���
	if (register_descriptor[min_pay_reg_index].size() != 0) {//�üĴ������б�ı���
		//��̭ԭ�б���
		for (vector<string>::iterator iter = register_descriptor[min_pay_reg_index].begin(); iter != register_descriptor[min_pay_reg_index].end(); ++iter) {
			if (Table::only_here(cur_fun_name, *iter, reg) && *iter != name) {//�Ĵ�����ԭ�б���ֻ����������Ĵ�����
				store_to(*iter, reg);
				Table::clear_addr(cur_fun_name, *iter);
				Table::add_stack_addr(cur_fun_name, *iter);
			} else {//�Ĵ�����ԭ�б����ڱ��б���
				Table::del_addr(cur_fun_name, *iter, reg);
			}
		}
	}
	//���¼Ĵ���������
	register_descriptor[min_pay_reg_index].clear();
	add_to_reg_des(name, min_pay_reg_index);
	//���±�����ַ������
	//Table::clear_addr(cur_fun_name, name);
	Table::add_addr(cur_fun_name, name, reg);
	return reg;
}

void Translator::save_all_val() {
	for (int i=0; i<10; i++) {
		for (vector<string>::iterator iter=register_descriptor[i].begin(); iter!=register_descriptor[i].end(); ++iter) {
			if (!Table::in_stack(cur_fun_name, *iter)) {//�������в���ջ�еı���
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

