#include "StdAfx.h"
#include "Quaternion.h"
#include "Intermediate_code.h"
#include "sstream"

/***********From Lexer*************/
extern string token;
extern int num;
extern enum kinds symbol;
/***********From Lexer*************/

/***************Debug***************/
//ofstream fout("../Parse_out.txt");
//#define cout fout
bool print_grammar_item = false;
/***************Debug***************/

int Parse::save_ptr = 0;
string Parse::cur_fun = "top";

Parse::Parse(Lexer lexer)
{
}

Parse::~Parse()
{
}

//����������[+|-]<�޷�������>|0��ʵ�������з�֧��Ԥ���룬����num
int Parse::proc_int_num(int &num) {
	int sign = 1;
	if (Lexer::symbol == kinds::PLUSSY) {//�����ŵ�������
		sign = 1;
		Lexer::getToken();
		if (Lexer::symbol != kinds::USINTSY ||
			(Lexer::symbol == kinds::USINTSY && Lexer::num == 0)) {
			//���ź���û�����ֻ������0������
			Error::addError(Lexer::line, ERROR_INT);
		}
	} else if (Lexer::symbol == kinds::MINUSSY) {//�����ŵĸ�����
		sign = -1;
		Lexer::getToken();
		if (Lexer::symbol != kinds::USINTSY ||
			(Lexer::symbol == kinds::USINTSY && Lexer::num == 0)) {
			//���ź���û�����ֻ������0������
			Error::addError(Lexer::line, ERROR_INT);
		}
	} else if (Lexer::symbol != kinds::USINTSY) {
		//û�������ţ�û������
		Error::addError(Lexer::line, ERROR_INT);
	}
	//�������ŵ�������
	num = sign * Lexer::num;//�����������ֵ
	Lexer::getToken();//Ԥ����
	if(print_grammar_item) cout << "����" << endl;
	return 0;
}

//��������������Ԥ����
int Parse::proc_program() {
	bool have_main = false;
	//����˵��
	if (Lexer::symbol == kinds::CONST) {
		proc_const_decl();//������˵��
	}
	//����˵��
	int save_p = save_ptr++;
	if (Lexer::symbol == kinds::INT || Lexer::symbol == kinds::CHAR) {
		Lexer::save(save_p);//���浱ǰ������λ��
		Lexer::getToken();//��ʶ��
		Lexer::getToken();//����Ǻ���Ӧ�ö���������
		if (Lexer::symbol != kinds::LPARSY) {
			Lexer::recover(save_p);//�ָ�λ��
			proc_var_decl();//�������˵��
		} else {//˵�����������Ǻ���˵����ҲҪ�ָ�
			Lexer::recover(save_p);
		}
	}
	Intermediate_code::push_back(Quaternion("~FUN", "~BEGIN", "", ""));
	//����˵��
	while (Lexer::symbol == kinds::INT || Lexer::symbol == kinds::CHAR || Lexer::symbol == kinds::VOID) {
		save_p = save_ptr++;
		if (Lexer::symbol == kinds::VOID) {//�޷���ֵ����
			Lexer::save(save_p);
			Lexer::getToken();
			//���ﱣ֤�˲�����������������void mian����
			if (Lexer::symbol == kinds::MAIN) {//����������
				Lexer::recover(save_p);
				break;
			}
			Lexer::recover(save_p);
			proc_void_fun_decl();//�����޷���ֵ��������
		}
		else {//�з���ֵ����
			//�ɴ����������˺������ǲ���main
			Lexer::save(save_p);
			Lexer::getToken();
			if (Lexer::symbol == kinds::MAIN) {
				//��������main��������������������
				have_main = true;
				Error::addError(Lexer::line, ERROR_MAIN_FUN_TYP);
			}
			Lexer::recover(save_p);
			proc_ioc_fun_decl();//�����з���ֵ��������
		}
	}
	if (Lexer::symbol == kinds::VOID) {//������
		proc_main_fun();//������
	}else if (!have_main) {
		//û��������������
		Error::addError(Lexer::line, MISS_MAIN_FUN);
	}
	if(print_grammar_item) cout<<"����" <<endl;
	return 0;
}

//����˵����ʵ����Ԥ����
int Parse::proc_const_decl() {
	//�ɸ�������֤�Ѿ�����һ��const�Ż�ִ�д˺���
	do {
		Lexer::getToken();
		proc_const_defi();
		if (Lexer::symbol != kinds::SEMISY) {
			//����������治�Ƿֺţ�����
			Error::addError(Lexer::line, MISS_SEMISY);
			if (Lexer::symbol != kinds::COMMASY) {//���Ƕ��ţ�����
				int save_p = save_ptr++;
				Lexer::save(save_p);
				while (Lexer::symbol != kinds::CONST) {
					save_p = save_ptr++;
					Lexer::save(save_p);
					Lexer::getToken();
				}
				Lexer::recover(save_p);
			}
			//�Ƕ��žͽ��������ߣ��ͷֺ�һ�����ݴ�
		}
		//��ȷԴ�������ﲻ��������ֻ���ڲ��Ƿֺ��Ҳ��Ƕ��ŵ�����²Ż����������������±�һ��������ĺͷֺ�һ��
		if (Lexer::symbol != kinds::INT && Lexer::symbol != kinds::CHAR) {
			Lexer::getToken();
		}
	}
	while (Lexer::symbol == kinds::CONST);//����CONST˵������������������������
	if(print_grammar_item) cout << "����˵��" <<endl;
	return 0;
}

//�������壬ʵ����Ԥ���룬����ű�
int Parse::proc_const_defi() {
	string name;
	int value;
	if (Lexer::symbol == kinds::INT) {
		Lexer::getToken();
		do {
			if (Lexer::symbol != kinds::IDSY) {
				//û���ֱ�ʶ��
				Error::addError(Lexer::line, MISS_IDSY);
				while (Lexer::symbol != IDSY) {//��������һ����ʶ������������ʵ�з��գ���������������������֮����
					Lexer::getToken();
				}
			}
			if (Lexer::symbol == kinds::MAIN) {//�����������Ϊmain�ı�ʶ��
				Error::addError(Lexer::line, ERROR_USE_MAIN);
			}
			name = Lexer::token;
			Lexer::getToken();
			if(Lexer::symbol != kinds::ASINSY) {
				//û���ֵȺ�
				Error::addError(Lexer::line, MISS_ASINSY);
				while (Lexer::symbol != IDSY) {//��������һ����ʶ������������ʵ�з��գ���������������������֮����
					Lexer::getToken();
				}
				continue;
			}
			Lexer::getToken();
			proc_int_num(value);//����Ⱥ��Ҷ˵�����
			if (0 != Table::con_enter(name, kinds::INTSY, value)) {//���
				//�ظ����壬���߲����
				Error::addError(Lexer::line, ANOTHER_DEF);
			} else {
				Intermediate_code::push_back(Quaternion("~CONST", "!INTSY", int2str(value), name));
			}
			if (Lexer::symbol != kinds::COMMASY) {
				break;
			}
			Lexer::getToken();//Ϊ��һ��ѭ����Ԥ����
		}
		while (true);
	}
	else if (Lexer::symbol == kinds::CHAR) {
		Lexer::getToken();
		do {
			if (Lexer::symbol != kinds::IDSY) {
				//û���ֱ�ʶ��
				Error::addError(Lexer::line, MISS_IDSY);
				while (Lexer::symbol != IDSY) {//��������һ����ʶ������������ʵ�з��գ���������������������֮����
					Lexer::getToken();
				}
			}
			if (Lexer::symbol == kinds::MAIN) {//�����������Ϊmain�ı�ʶ��
				Error::addError(Lexer::line, ERROR_USE_MAIN);
			}
			name = Lexer::token;
			Lexer::getToken();
			if (Lexer::symbol != kinds::ASINSY) {
				//û���ֵȺ�
				Error::addError(Lexer::line, MISS_ASINSY);
				while (Lexer::symbol != IDSY) {//��������һ����ʶ������������ʵ�з��գ���������������������֮����
					Lexer::getToken();
				}
				continue;
			}
			Lexer::getToken();
			if (Lexer::symbol != kinds::CHARSY) {
				//�Ⱥ��ұ߲���char
				Error::addError(Lexer::line, UNMATCHING);
			} else {
				value = Lexer::num;//charsy��value����assicֵ
				if (0 != Table::con_enter(name, kinds::CHARSY, value)) {//���
					//�ظ�����
					Error::addError(Lexer::line, ANOTHER_DEF);
				} else {
					Intermediate_code::push_back(Quaternion("~CONST", "!CHARSY", int2str(value), name));
				}
			}
			Lexer::getToken();
			if (Lexer::symbol != kinds::COMMASY) {
				break;
			}
			Lexer::getToken();//Ϊ��һ�ε�����Ԥ����
		}
		while (true);
	} else {
		//const�����int��char����Ķ���
		//����ֲ���
		return 1;
	}
	if(print_grammar_item) cout<<"��������"<<endl;
	return 0;
}

//����˵����ʵ����Ԥ����
int Parse::proc_var_decl() {
	//��������֤����int��char�Ҳ��Ǻ���˵���Ż����˺���
	do {
		int save_p = save_ptr++;
		Lexer::save(save_p);
		Lexer::getToken();
		Lexer::getToken();
		if (Lexer::symbol == kinds::LPARSY) {//����������˵���Ǻ�������
			Lexer::recover(save_p);
			return 0;
		}
		Lexer::recover(save_p);
		proc_var_defi();
		if (Lexer::symbol != kinds::SEMISY) {
			//ȱ�ٷֺţ�����
			Error::addError(Lexer::line, MISS_SEMISY);
			if (Lexer::symbol != kinds::COMMASY) {//���Ƕ��ţ�����
				save_p = save_ptr++;
				Lexer::save(save_p);
				while (Lexer::symbol != kinds::INT && Lexer::symbol != kinds::CHAR) {
					save_p = save_ptr++;
					Lexer::save(save_p);
					Lexer::getToken();
				}
				Lexer::recover(save_p);
			}
			//�Ƕ��žͽ��������ߣ��ͷֺ�һ�����ݴ�
		}
		//��ȷԴ�������ﲻ��������ֻ���ڲ��Ƿֺ��Ҳ��Ƕ��ŵ�����²Ż����������������±�һ��������ĺͷֺ�һ��
		if (Lexer::symbol != kinds::INT && Lexer::symbol != kinds::CHAR) {
			Lexer::getToken();
		}
	}
	while (Lexer::symbol == kinds::INT || Lexer::symbol == kinds::CHAR);
	if(print_grammar_item) cout<<"����˵��" <<endl;
	return 0;
}

//�������壬 ʵ����Ԥ���룬����ű�
int Parse::proc_var_defi() {
	if (Lexer::symbol == kinds::INT || Lexer::symbol == kinds::CHAR) {
		const enum kinds type = Lexer::symbol==kinds::INT?kinds::INTSY:kinds::CHARSY;
		const string typ = type==kinds::INTSY?"INTSY":"CHARSY";
		Lexer::getToken();
		do {
			if (Lexer::symbol != kinds::IDSY) {
				//û���ֱ�ʶ��
				return 1;
			}
			const string name = Lexer::token;
			Lexer::getToken();
			if (Lexer::symbol == kinds::LBRACSY ) {//����
				Lexer::getToken();
				if (Lexer::symbol != kinds::USINTSY) {
					//�����ź�������
					return 1;
				}
				const int dim = Lexer::num;
				if (dim <= 0) {
					Error::addError(Lexer::line, ERROR_ARRAY_DIM_0);
				}
				Lexer::getToken();
				if (Lexer::symbol != kinds::RBRACSY) {
					//û���ҷ�����
					return 1;
				}
				//�˴�����ȷ������������ȷ���Ҳ��ۺ���Ķ��Ż�ֺţ�
				Table::array_enter(name, type, dim);//���
				Intermediate_code::push_back(Quaternion("~ARRAY", "!"+typ, int2str(dim), name));
				Lexer::getToken();
			} else {
				//�˴�����ȷ������������ȷ���Ҳ��ۺ���Ķ��Ż�ֺţ�
				Table::val_enter(name, type);//���
				Intermediate_code::push_back(Quaternion("~VAL", "!"+typ, "", name));
			}
			if (Lexer::symbol != kinds::COMMASY) {
				break;
			}
			Lexer::getToken();
		}
		while (true);
	} else {
		//const�����int��char����Ķ���
		//����ֲ���
		return 1;
	}
	if(print_grammar_item) cout<<"��������"<<endl;
	return 0;
}

//�޷���ֵ�������壬 ��Ԥ����
int Parse::proc_void_fun_decl() {
	if (Lexer::symbol != kinds::VOID) {
		//����ֵ�������󣬱���
		Error::addError(Lexer::line, ERROR_RET_TYPE);
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::IDSY) {
		//����������������û������ű��ˣ���˷���
		Error::addError(Lexer::line, MISS_IDSY);
		return 1;
	}
	const string name = Lexer::token;
	cur_fun = name;
	//�Ҿ���������;�Ӧ������ű���,��������ȷ�����˲��������������Ҫ������������������ͬʱҪ�ǵø��ķ��ű��level��cur_parent
	if (0 != Table::func_enter(name, kinds::VOID)) {
		//������ͬ��������
		Error::addError(Lexer::line, ANOTHER_DEF);
	} else {
		Intermediate_code::push_back(Quaternion("~FUN", "!VOID", name, ""));//�����м����
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::LPARSY) {//������Ϊȱ�������ź��ֱ���ǲ����б���
		//ȱ��������
		Error::addError(Lexer::line, MISS_LPARSY);
	} else
		Lexer::getToken();
	int dim = 0;
	if (Lexer::symbol != kinds::RPARSY) {
		//ȱ��������,��Ϊ�в���
		if (0 != proc_para(dim)) {
			//����������
			return 1;
		}
		if (Lexer::symbol != kinds::RPARSY) {//Ĭ�Ͻ����˲������Ԥ����
			//��������ȷ��Ȼ��û�������ţ�����Ӧ��Ҫ�����ʶ��ݴ�
			Error::addError(Lexer::line, MISS_RPARSY);
		}
	}
	Table::func_fill_back_dim(name, dim);//���������������Ȼ�ݹ����ʱû���жϲ��������Ƿ���ȷ
	//����������ȫ����������ȷ
	Lexer::getToken();
	if (Lexer::symbol != kinds::LCBRACSY) {
		//ȱ��������
		Error::addError(Lexer::line, MISS_LCBRACSY);
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::RCBRACSY) {
		proc_cplx_stat();//���������
		if (Lexer::symbol != kinds::RCBRACSY) {
			//ȱ���һ�����
			Error::addError(Lexer::line, MISS_RCBRACSY);
		}
	} 
	//���һ�������ȫ����������ȷ
	//�����������
	//���
	Intermediate_code::push_back(Quaternion("~END", name, "", ""));//��Ԫʽ�в��뺯������������־
	Table::func_fill_back_value(name);//����ջ�ռ��С
	cur_fun = "top";
	Lexer::getToken();
	if(print_grammar_item) cout << "�޷���ֵ��������" <<endl;
	return 0;
}

//�з���ֵ�������壬��Ԥ����
int Parse::proc_ioc_fun_decl() {
	if (Lexer::symbol != kinds::INT && Lexer::symbol != kinds::CHAR) {
		//����ֵ�������󣬱���
		Error::addError(Lexer::line, ERROR_RET_TYPE);
	}
	const enum kinds type = Lexer::symbol==kinds::INT?kinds::INTSY:kinds::CHARSY;
	Lexer::getToken();
	if (Lexer::symbol != kinds::IDSY) {
		//����������������û������ű��ˣ���˷���
		Error::addError(Lexer::line, MISS_IDSY);
		return 1;
	}
	const string name = Lexer::token;
	cur_fun = name;
	if (0 != Table::func_enter(name, type)) {
		//������ͬ��������
		Error::addError(Lexer::line, ANOTHER_DEF);
	} else {
		const string typ = type==kinds::INTSY?"INTSY":"CHARSY";
		Intermediate_code::push_back(Quaternion("~FUN", "!"+typ, name, ""));//�����м����
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::LPARSY) {//������Ϊȱ�������ź��ֱ���ǲ����б���
		//ȱ��������
		Error::addError(Lexer::line, MISS_LPARSY);
	} else
		Lexer::getToken();
	int dim = 0;
	if (Lexer::symbol != kinds::RPARSY) {
		//ȱ��������,��Ϊ�в���
		if (0 != proc_para(dim)) {
			//����������
			return 1;
		}
		if (Lexer::symbol != kinds::RPARSY) {//Ĭ�Ͻ����˲������Ԥ����
			//��������ȷ��Ȼ��û�������ţ�����Ӧ��Ҫ�����ʶ��ݴ�
			Error::addError(Lexer::line, MISS_RPARSY);
		}
	}
	Table::func_fill_back_dim(name, dim);//���������������Ȼ�ݹ����ʱû���жϲ��������Ƿ���ȷ
	//����������ȫ����������ȷ
	Lexer::getToken();
	if (Lexer::symbol != kinds::LCBRACSY) {
		//ȱ��������
		Error::addError(Lexer::line, MISS_LCBRACSY);
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::RCBRACSY) {
		proc_cplx_stat();//���������
		if (Lexer::symbol != kinds::RCBRACSY) {
			//ȱ���һ�����
			Error::addError(Lexer::line, MISS_RCBRACSY);
		}
	} 
	//���һ�������ȫ����������ȷ
	//�����������
	//���
	Intermediate_code::push_back(Quaternion("~END", name, "", ""));//��Ԫʽ�в��뺯������������־
	Table::func_fill_back_value(name);//������ʵ�ǻ���ջ�ռ��С
	cur_fun = "top";
	Lexer::getToken();
	if(print_grammar_item) cout << "�з���ֵ��������" <<endl;
	return 0;
}

//������, ��Ԥ����
int Parse::proc_main_fun() {
	if (Lexer::symbol != kinds::VOID) {
		//��������Ӧ��������ú�����֤���᲻��void
		return 1;
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::MAIN) {
		//��������Ӧ��������ú�����֤���᲻��main
		return 1;
	}
	cur_fun = "main";
	if (0 != Table::func_enter("main", kinds::VOID)) {//mian�޲�����֮�������ֻ������main��㣬�ʲ�����
		//����main�Ѿ�����������
		return 1;
	}
	Intermediate_code::push_back(Quaternion("~FUN", "!VOID", "main", ""));//�����м����
	Lexer::getToken();
	if (Lexer::symbol != kinds::LPARSY) {
		//����
		return 1;
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::RPARSY) {
		//����
		return 1;
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::LCBRACSY) {
		//����
		return 1;
	}
	Lexer::getToken();
	if ( 0!=proc_cplx_stat()) {
		//�����������
		return 1;
	}
	if (Lexer::symbol != kinds::RCBRACSY) {
		//����
		return 1;
	}
	//Lexer::getToken();//Ԥ����
	Table::func_fill_back_dim("main", 0);//��ʵ���ﲻ����Ҳû�£���ΪdimĬ��Ϊ0
	Table::func_fill_back_value("main");
	cur_fun = "top";//ʵ����п���
	Intermediate_code::push_back(Quaternion("~TERMINATE", "" ,"" ,""));
	if(print_grammar_item) cout <<"������"<<endl;
	return 0;
}

//������Ҳ�ǲ�������������ʱ()����ģ���Ԥ����
int Parse::proc_para(int &dim) {
	int d = 0;
	while (Lexer::symbol == kinds::INT || Lexer::symbol == kinds::CHAR) {
		const enum kinds type = Lexer::symbol==kinds::INT?INTSY:CHARSY;
		Lexer::getToken();
		if (Lexer::symbol != kinds::IDSY) {
			//�����б��Ǳ�ʶ��������������ô���ֲ���
			Error::addError(Lexer::line, MISS_IDSY);
			while (!(Lexer::symbol == kinds::INT || Lexer::symbol == kinds::CHAR)) {
				Lexer::getToken();//�����ж������ģ��ķ���
			}
		}
		const string name = Lexer::token;
		if (0 != Table::para_enter(name, type, d)) {//����ű�
			//������ͬ����ʶ��������
			Error::addError(Lexer::line, ANOTHER_DEF);
		}
		const string typ = type==kinds::INTSY?"INTSY":"CHARSY";
		Intermediate_code::push_back(Quaternion("~PARA", "!"+typ, name, ""));//�����м����
		Lexer::getToken();
		d++;
		if (Lexer::symbol != kinds::COMMASY) {
			break;
		}
		Lexer::getToken();
	}
	dim = d;
	if(print_grammar_item) cout << "������" <<endl;
	return 0;
}

//������䣬��Ԥ����
int Parse::proc_cplx_stat() {
	//����˵��
	if (Lexer::symbol == kinds::CONST) {
		proc_const_decl();
	}
	//����˵��
	if (Lexer::symbol == kinds::INT || Lexer::symbol == kinds::CHAR) {
		proc_var_decl();
	}
	//�����
	proc_stat_list();
	if(print_grammar_item) cout << "�������"<<endl;
	return 0;
}

//����У�ʵ����Ԥ����
int Parse::proc_stat_list() {
	//û���ж�����ȷ�������е���仹�ǳ�����
	const int save_p = save_ptr++;
	while (true) {
		switch (Lexer::symbol) {
		case kinds::IF:
		case kinds::FOR:
		case kinds::LCBRACSY:
		case kinds::SWITCH:
		case kinds::SEMISY:
		case kinds::SCANF:
		case kinds::PRINTF:
		case kinds::RETURN:
		case kinds::IDSY:
			proc_stat();//��䴦��
			break;
		default:
			if(print_grammar_item) cout <<"�����"<<endl;
			return 0;
		}
		Lexer::save(save_p);
		if (-1 == Lexer::getToken()) {
			break;
		}
		Lexer::recover(save_p);
	}
	if(print_grammar_item) cout <<"�����"<<endl;
	return 0;
}

//if��䣬��Ԥ���룬�ɵ����߱�֤�Ѿ�ʶ��if
int Parse::proc_if_stat() {
	//�ɵ����߱�֤�Ѿ�ʶ��if
	//ʵ���Ϻ�������ÿ���ط����е���������֤�������һ�����Ϊ���������ټ��һ��Ϊ��
	if (Lexer::symbol != kinds::IF) {
		return 1;//�׸����ʲ�����if�������ڵģ�û��if�Ͳ������˷���
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::LPARSY) {//��Ϊû�������ž�ֱ����������
		//û��������
		Error::addError(Lexer::line, MISS_LPARSY);
	} else 
		Lexer::getToken();
	string val1;//��������м���
	enum kinds cond_type;
	proc_cond(val1, cond_type);//��������
	if (cond_type != kinds::INTSY) {//�����������������
		Error::addError(Lexer::line, ERROR_COND_TYPE);
	}
	if (Lexer::symbol != kinds::RPARSY ) {
		//û�������ţ�����
		Error::addError(Lexer::line, MISS_LPARSY);
	}
	//�������������
	const string lable1 = new_lable();
	Intermediate_code::push_back(Quaternion("~BZ", val1, lable1, ""));//�������ǰҪ������תָ��
	Lexer::getToken();
	proc_stat();
	const string lable2 = new_lable();
	Intermediate_code::push_back(Quaternion("~GOTO", lable2, "", ""));//������������ת���
	Intermediate_code::push_back(Quaternion("~LABLE", lable1, "", ""));//�����ǩ
	if (Lexer::symbol == kinds::ELSE) {
		Lexer::getToken();
		proc_stat();
	}
	Intermediate_code::push_back(Quaternion("~LABLE", lable2, "", ""));//�����ǩ
	if(print_grammar_item) cout <<"if���"<<endl;
	return 0;
}

//������������if��for�У���Ԥ����
int Parse::proc_cond(string &result, kinds &type) {
	string val1;
	enum kinds type1;
	string op;
	string val2;
	enum kinds type2;
	proc_expr(val1, type1);
	if (type1 != kinds::INTSY && type1 != kinds::CHARSY) {
		Error::addError(Lexer::line, ERROR_COND_TYPE);
	}
	if (Lexer::symbol == kinds::LESSY || Lexer::symbol == kinds::NLESSY ||
		Lexer::symbol == kinds::MORSY || Lexer::symbol == kinds::NMORSY ||
		Lexer::symbol == kinds::EQUSY || Lexer::symbol == kinds::NEQUSY) {//�����������˵��������Ϊ1>2����ʽ
		switch (Lexer::symbol) {
		case kinds::LESSY:
			op = "<";
			break;
		case kinds::NLESSY:
			op = ">=";
			break;
		case kinds::MORSY:
			op = ">";
			break;
		case kinds::NMORSY:
			op = "<=";
			break;
		case kinds::EQUSY:
			op = "==";
			break;
		case kinds::NEQUSY:
			op = "!=";
			break;
		default:
			op = "";
		}
		Lexer::getToken();
		proc_expr(val2, type2);
		if (type2 != CHARSY && type2 != INTSY) {
			Error::addError(Lexer::line, ERROR_COND_TYPE);
			type = null;
		}
		result = new_val(kinds::INTSY, 0);
		Intermediate_code::push_back(Quaternion(op, val1, val2, result));//����Ŀ�����
	} else {//������ֻ��һ�����ʽ
		result = val1;
	}
	type = kinds::INTSY;
	if(print_grammar_item) cout <<"������������if��for���������У�"<<endl;
	return 0;
}

//��䣬 ʵ�������з�֧��Ԥ����
int Parse::proc_stat() {
	if (Lexer::symbol == kinds::IF) {	//if���
		proc_if_stat();//if��䴦��
		return 0;
	}
	if (Lexer::symbol == kinds::FOR) {//for���
		proc_for_stat();//for��䴦��
		return 0;
	}
	if (Lexer::symbol == kinds::LCBRACSY) {//{�����}
		Lexer::getToken();
		proc_stat_list();//����д���
		if (Lexer::symbol != kinds::RCBRACSY) {
			//�����û��}
			Error::addError(Lexer::line, MISS_RCBRACSY);
		}
		Lexer::getToken();//Ԥ����
		return 0;
	}
	if (Lexer::symbol == kinds::SWITCH) {//swith-case���
		proc_swit_stat();//switch-case���
		return 0;
	}
	if (Lexer::symbol == kinds::SEMISY) {//�����
		Lexer::getToken();
		if(print_grammar_item) cout << "�����"<<endl;
		return 0;
	}
	if (Lexer::symbol == kinds::SCANF) {//�����
		proc_read_stat();//�����
	} else if (Lexer::symbol == kinds::PRINTF) {//д���
		proc_writ_stat();//д���
	} else if (Lexer::symbol == kinds::RETURN) {//�������
		proc_retu_stat();//�������
	} else if (Lexer::symbol == kinds::IDSY) {
		const int save_p = save_ptr++;
		Lexer::save(save_p);
		Lexer::getToken();
		if (Lexer::symbol == kinds::ASINSY || Lexer::symbol == kinds::LBRACSY) {	//��ֵ���
			Lexer::recover(save_p);
			proc_assi_stat();//��ֵ���
		} else if (Lexer::symbol == kinds::LPARSY) {//�����������
			//����ű��پ��������з���ֵ������仹���޷���ֵ�������
			///������������������䶼һ��
			Lexer::recover(save_p);
			string fun_retron_name;
			enum kinds fun_retron_type;
			proc_cal_fun(fun_retron_name, fun_retron_type);//�����������
			//��������öԷ���ֵ�����������κμ��
		} else {
			Lexer::recover(save_p);
			Error::addError(Lexer::line, UNDEFINED_STAT);
		}
	}
	//�зֺ����ͳһ�������жϷֺţ��޷ֺ�����ٸ��Եķ�֧��Ͷ��ж�����
	if (Lexer::symbol != kinds::SEMISY) {
		//�зֺ����ȱ�ٷֺ�
		Error::addError(Lexer::line, MISS_SEMISY);
	}
	Lexer::getToken();//Ԥ����
	if(print_grammar_item) cout <<"���"<<endl;
	return 0;
}

//���ʽ������Ԥ����
int Parse::proc_expr(string &result, kinds &type) {
	string sign = "+";
	if (Lexer::symbol == kinds::PLUSSY) {
		//���ţ����ò���
		Lexer::getToken();
	} else if (Lexer::symbol == kinds::MINUSSY) {
		//���ţ���Ҫ����һ�����-1
		sign = "-";
		Lexer::getToken();
	}
	string term_result;
	enum kinds term_type;
	proc_term(term_result, term_type);//���
	type = term_type;
	const string tmp_result = new_val(type, 0);
	if (sign == "-") Intermediate_code::push_back(Quaternion(sign, "0", term_result, tmp_result));//���žͲ�������
	else Intermediate_code::push_back(Quaternion("=", term_result, "", tmp_result));
	while (Lexer::symbol == kinds::PLUSSY || Lexer::symbol == kinds::MINUSSY) {
		//ֻҪ�мӷ���������ͱ���term��������Ǵ�ģ�����ֻҪ����ȷ�����룬ѭ��ֻ����Ϊѭ��������ֹ������return 1ǿ�ƽ�ֹ
		sign = Lexer::symbol==kinds::PLUSSY?"+":"-";
		Lexer::getToken();
		string val;
		proc_term(val, term_type);//���
		Intermediate_code::push_back(Quaternion(sign, tmp_result, val, tmp_result));
		if (term_type == kinds::INTSY) {
			type = kinds::INTSY;
			Table::set_type(tmp_result, INTSY);
		}
	}
	result = tmp_result;
	if(print_grammar_item) cout <<"���ʽ"<<endl;
	return 0;
}

//�����Ԥ����
int Parse::proc_term(string &result, kinds &type) {
	string fact_result;
	enum kinds fact_type;
	proc_fact(fact_result, type);
	if (!(Lexer::symbol == kinds::STARSY || Lexer::symbol == kinds::DIVISY)) {//ֻ��һ��
		result = fact_result;
		if(print_grammar_item) cout <<"��"<<endl;
		return 0;
	}
	const string tmp_result = new_val(type, 0);
	Intermediate_code::push_back(Quaternion("=", fact_result, "", tmp_result));
	while (Lexer::symbol == kinds::STARSY || Lexer::symbol == kinds::DIVISY) {
		const string sign = Lexer::symbol==kinds::STARSY?"*":"/";
		string val;
		Lexer::getToken();
		proc_fact(val, fact_type);
		Intermediate_code::push_back(Quaternion(sign, tmp_result, val, tmp_result));
		if (fact_type == kinds::INTSY) {
			type = kinds::INTSY;
			Table::set_type(tmp_result, INTSY);
		}
	}
	result = tmp_result;
	if(print_grammar_item) cout <<"��"<<endl;
	return 0;
}

//���ӣ��������ĸ���֧����Ԥ����
int Parse::proc_fact(string &result, kinds &type) {
	const int save_p = save_ptr++;
	switch (Lexer::symbol) {
	case kinds::USINTSY://������[+|-]<�޷�������>|0
	case kinds::PLUSSY:
	case kinds::MINUSSY:
		int int_num;
		proc_int_num(int_num);//��������
		//result = new_val(INTSY, int_num);
		result = int2str(int_num);
		type = kinds::INTSY;
		break;
	case kinds::CHARSY://�ַ�
		//result = new_val(CHARSY, Lexer::num);
		result = "$"+int2str(Lexer::num);
		type = kinds::CHARSY;
		Lexer::getToken();
		break;
	case kinds::LPARSY://�����ʽ��
		Lexer::getToken();
		proc_expr(result, type);
		if (Lexer::symbol != kinds::RPARSY) {
			//û�������ţ�����
		}
		Lexer::getToken();
		break;
	case kinds::IDSY://��ʶ��������Ԫ�ء��з���ֵ��������
		Lexer::save(save_p);
		Lexer::getToken();
		if (Lexer::symbol == kinds::LBRACSY) {//����Ԫ��
			Lexer::recover(save_p);
			const string array_name = Lexer::token;
			if (!Table::contain(cur_fun, array_name)) {
				Error::addError(Lexer::line, UNDEFINED_IDSY);
			}
			if (Table::get_CLASS(cur_fun, array_name) != ARRAY_CLASS) {
				Error::addError(Lexer::line, UNMATCHING);
			}
			type = Table::get_type(cur_fun, array_name);
			Lexer::getToken();//��������
			Lexer::getToken();
			string index_name;
			enum kinds index_type;
			/*******************************���Խ�����*************************************/
			//����Խ�磿����ֻ��Ҫ�����ͳ�������������
			const int dim = Table::get_dim(cur_fun, array_name);
			if (Lexer::symbol == kinds::INTSY) {//[]����������Խ�籨��
				if (!(0 <= Lexer::num && Lexer::num < dim)) {
					Error::addError(Lexer::line, ERROR_DIM_ARRAY);
				}
			} else if (Lexer::symbol == IDSY) {//[]���ǳ������������ͳ������ַ���������Խ�籨��
				if (Table::get_CLASS(cur_fun, Lexer::token) == _CLASS::CONST_CLASS) {
					if (!(0 <= Lexer::num && Lexer::num < dim)) {
						Error::addError(Lexer::line, ERROR_DIM_ARRAY);
					}
				}
			}
			/*******************************���Խ�����*************************************/	
			proc_expr(index_name, index_type);
			if (index_type != kinds::INTSY && index_type != kinds::CHARSY) {
			//ֻ�����������ǷǸ����ͻ��ַ��ͣ����ﻹ�޷��ж��Ƿ�Խ�磨������Խ�磩
				Error::addError(Lexer::line, ERROR_TYP_ARRAY_INDEX);
			}
			if (Lexer::symbol != kinds::RBRACSY) {
			//û���ҷ����ţ�����
				Error::addError(Lexer::line, MISS_RBRACSY);
			}
			result = new_val(type, 0);
			Intermediate_code::push_back(Quaternion("=[]", array_name, index_name, result));
			Lexer::getToken();
		} else if (Lexer::symbol == kinds::LPARSY) {//�з���ֵ��������
			Lexer::recover(save_p);
			proc_cal_fun(result, type);//�з���ֵ�������
		} else {//��ʶ��
			Lexer::recover(save_p);
			result = Lexer::token;
			if (Table::contain(cur_fun, result)) {//�������˱�ʶ���������Ǽ�����
				const enum _CLASS _class = Table::get_CLASS(cur_fun, result);
				if (_class == CONST_CLASS || _class == VAL_CLASS || _class == PARA_CLASS) {
					type = Table::get_type(cur_fun, result);
				} else {
					Error::addError(Lexer::line, UNMATCHING);
					type = null;
				}
			} else {
				cout << cur_fun << "\t" << Lexer::token << "\t" << result << endl;
				Table::contain(cur_fun, result);
				Error::addError(Lexer::line, UNDEFINED_IDSY);
				type = null;
			}
			Lexer::getToken();
		}
	default: ;
	}
	if(print_grammar_item) cout <<"����"<<endl;
	return 0;
}

//����������䣬���������б���Ԥ����
int Parse::proc_cal_fun(string &result, kinds &type) {
	int dim = 0;
	string fun_name;
	if (Lexer::symbol != kinds::IDSY) {
		//û�б�ʶ��������ͨ���������˷�֧
		return 1;
	} else {
		fun_name = Lexer::token;
		if (!Table::contain_func(fun_name)) {
			Error::addError(Lexer::line, UNDEFINED_IDSY);
		}
		if (fun_name == "main") {
			Error::addError(Lexer::line, ERROR_CAL_MAIN);
		}
		Lexer::getToken();
		if (Lexer::symbol != kinds::LPARSY ) {
			//û�������ţ�����
			Error::addError(Lexer::line, MISS_LPARSY);
		} else {
			Lexer::getToken();
			if (Lexer::symbol != kinds::RPARSY) {
				//Ӧ�ô����￪ʼ���������ͺ����������Ƿ�һ��
				vector<TableEntity> fun_para = Table::get_para(fun_name);
				dim = 0;
				string para_name;
				enum kinds para_type;
				//��һ������
				proc_expr(para_name, para_type);
				if (!(para_type == fun_para[dim].type || (para_type == kinds::CHARSY && fun_para[dim].type == kinds::INTSY)))
				{	
					Error::addError(Lexer::line, CAL_FUN_UNMATCHING);
				}
				dim++;
				string typ = para_type==kinds::INTSY?"INTSY":"CHARSY";
				Intermediate_code::push_back(Quaternion("~PUSH", para_name, fun_para[0].name, fun_name));
				while (Lexer::symbol == kinds::COMMASY ) {//��������˵�����в���
					Lexer::getToken();
					proc_expr(para_name, para_type);
					if (!(para_type == fun_para[dim].type || (para_type == kinds::CHARSY && fun_para[dim].type == kinds::INTSY)))
					{	
						Error::addError(Lexer::line, CAL_FUN_UNMATCHING);
					}
					typ = para_type==kinds::INTSY?"INTSY":"CHARSY";
					Intermediate_code::push_back(Quaternion("~PUSH", para_name, fun_para[dim].name, fun_name));
					dim++;
				}

				if (Lexer::symbol != kinds::RPARSY) {
					//û�������ţ�����
					Error::addError(Lexer::line, MISS_RPARSY);
				}
			} else {
				dim = 0;//�����б�Ϊ��
			}
		}
	}
	if (Table::get_dim(cur_fun, fun_name) != dim) {
		Error::addError(Lexer::line, ERROR_DIM_FUN);//����������������
	}
	type = Table::get_type(cur_fun, fun_name);//INTSY/CHARSY/VOID
	result = new_val(type, 0);
	Intermediate_code::push_back(Quaternion("~CALL", fun_name, "", ""));
	Intermediate_code::push_back(Quaternion("=", "$v0", "", result));//���淵��ֵ
	Lexer::getToken();
	if(print_grammar_item) cout<<"�з���ֵ�����������"<<endl;
	return 0;
}

//ѭ����䣬��ȷ��֧��Ԥ����
int Parse::proc_for_stat() {
	const int save1 = save_ptr++;
	const int save2 = save_ptr++;
	Intermediate_code::push_back(Quaternion("~LOOP", "~BEDIN", "", ""));
	if (Lexer::symbol != kinds::FOR) {
		return 1;
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::LPARSY ) {
		//ȱ�������ţ�����
		return 1;
	} else {
		Lexer::getToken();
		if (Lexer::symbol != kinds::IDSY) {
			//û�б�ʶ��������
			Error::addError(Lexer::line, MISS_IDSY);
		} else {
			const string ID_name = Lexer::token;
			const enum kinds ID_type = Table::get_type(cur_fun, ID_name);
			if (!Table::contain(cur_fun, ID_name)) {
				Error::addError(Lexer::line, UNDEFINED_IDSY);
			}
			Lexer::getToken();
			if (Lexer::symbol != kinds::ASINSY) {
				//���Ǹ�ֵ�ţ�����
				Error::addError(Lexer::line, MISS_ASINSY);
			} else {
				Lexer::getToken();
				string expr_name;
				enum kinds expr_type;
				proc_expr(expr_name, expr_type);//��ֵ���Ҳ��Ǳ��ʽ
				if (!((ID_type == expr_type && expr_type == kinds::INTSY) || 
					(ID_type == expr_type && expr_type == kinds::CHARSY) || 
					(ID_type == kinds::INTSY && expr_type == kinds::CHARSY))) {
					Error::addError(Lexer::line, UNMATCHING);
				}
				Intermediate_code::push_back(Quaternion("=", expr_name, "", ID_name));
				const string lable = new_lable();
				Intermediate_code::push_back(Quaternion("~LABLE", lable, "", ""));
				if (Lexer::symbol != kinds::SEMISY ) {
					//���Ƿֺţ�����
					Error::addError(Lexer::line, MISS_SEMISY);
				} else {
					Lexer::save(save1);//��������֮ǰ���ֳ�
					do {//������������
						Lexer::getToken();
					}
					while (Lexer::symbol != kinds::SEMISY);//�������ٶ�һ���Ϳ��Դ�������
					
					if (Lexer::symbol != kinds::SEMISY) {
						//��������û�зֺţ�����
						Error::addError(Lexer::line, MISS_SEMISY);
					} else {
						Lexer::getToken();
						if (Lexer::symbol != kinds::IDSY) {
							//��������û�е�һ����ʶ��������
							Error::addError(Lexer::line, MISS_IDSY);
						} else {
							const string ID2_name = Lexer::token;
							const enum kinds ID2_type = Table::get_type(cur_fun, ID2_name);
							if (!Table::contain(cur_fun, ID2_name)) {
								Error::addError(Lexer::line, UNMATCHING);
							}
							Lexer::getToken();
							if (Lexer::symbol != kinds::ASINSY) {
								//��������û���ֵȺţ�����
								Error::addError(Lexer::line, MISS_ASINSY);
							} else {
								Lexer::getToken();
								if (Lexer::symbol != kinds::IDSY) {
									//��������û�еڶ�����ʶ��������
									Error::addError(Lexer::line, MISS_IDSY);
								} else {
									const string ID3_name = Lexer::token;
									const enum kinds ID3_type = Table::get_type(cur_fun, ID3_name);
									if (!Table::contain(cur_fun, ID3_name)) {
										Error::addError(Lexer::line, UNMATCHING);
									}
									if (!((ID2_type == ID3_type && ID3_type == INTSY) ||
										(ID2_type == ID3_type && ID3_type == CHARSY) ||
										(ID2_type == INTSY && ID3_type == CHARSY))) {
										Error::addError(Lexer::line, UNMATCHING);
									}
									Lexer::getToken();
									if (Lexer::symbol != kinds::PLUSSY && Lexer::symbol != kinds::MINUSSY) {
										//û���ּӼ��ţ�����
										Error::addError(Lexer::line, MISS_PLUS_MINU);
									} else {
										const string op = Lexer::symbol == kinds::PLUSSY?"+":"-";
										Lexer::getToken();
										if (!(Lexer::symbol != kinds::USINTSY ||
											(Lexer::symbol == kinds::USINTSY && Lexer::num != 0))) {
											//��������������������
											Error::addError(Lexer::line, ERROR_TYPE_IN_BC);
										} else {
											const long step_long = Lexer::num;
											const string step = int2str(step_long);
											if(print_grammar_item) cout << "����"<<endl;
											Lexer::getToken();
											if (Lexer::symbol != kinds::RPARSY ) {
												//for()ȱ��������
												Error::addError(Lexer::line, MISS_RPARSY);
											} else {
												Lexer::getToken();
												switch (Lexer::symbol) {
												case kinds::IF:
												case kinds::FOR:
												case kinds::LCBRACSY:
												case kinds::SWITCH:
												case kinds::SEMISY:
												case kinds::SCANF:
												case kinds::PRINTF:
												case kinds::RETURN:
												case kinds::IDSY:
													proc_stat();//��䴦��
													if(print_grammar_item) cout <<"for���"<<endl;
													Intermediate_code::push_back(Quaternion(op, ID3_name, step, ID2_name));//�Ӽ�����
													Lexer::save(save2);//�����ֳ�
													Lexer::recover(save1);//��ʼ��������
													Lexer::getToken();
													string cond_name;
													enum kinds cond_type;
													proc_cond(cond_name, cond_type);//�м�����
													Lexer::recover(save2);
													Intermediate_code::push_back(Quaternion("~BNZ", cond_name, lable, ""));
													Intermediate_code::push_back(Quaternion("~LOOP", "~END"	, "", ""));
													return 0;
												}
												//�������Ŀ�ͷ���ţ�����������ᵽ�˷�֧
												return 1;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return 1;//��ȷ�Ĵ��벻��ִ������
}

//switch-case��䣬ʵ�������з�֧��Ԥ����
int Parse::proc_swit_stat() {
	if (Lexer::symbol != kinds::SWITCH) {
		return 1;//�׸����ʲ���switch
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::LPARSY ) {
		Error::addError(Lexer::line, MISS_LPARSY);//switch��ȱ��(
	}
	Lexer::getToken();
	string expr_name;
	enum kinds expr_type;
	proc_expr(expr_name, expr_type);//������Ԥ����
	if (Lexer::symbol != kinds::RPARSY) {
		Error::addError(Lexer::line, MISS_RPARSY);//ȱ�٣�
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::LCBRACSY) {
		Error::addError(Lexer::line, MISS_LCBRACSY);//ȱ��{
	}
	Lexer::getToken();
	const string end_lable = new_lable();
	proc_case_list(expr_name, expr_type, end_lable);//������Ԥ����
	proc_default();//������Ԥ����
	if (Lexer::symbol != kinds::RCBRACSY) {
		//ȱ��}������
		Error::addError(Lexer::line, MISS_RCBRACSY);
	}
	Intermediate_code::push_back(Quaternion("~LABLE", end_lable, "", ""));
	Lexer::getToken();//Ԥ����
	if(print_grammar_item) cout <<"switch-case���"<<endl;
	return 0;
}

//�����ʵ�������з�֧��Ԥ����
int Parse::proc_case_list(const string name, const enum kinds type, const string end_lable) {
	proc_case_stat(name, type, end_lable);//��һ����������
	while (Lexer::symbol == kinds::CASE) {
		proc_case_stat(name, type, end_lable);//�����������
	}
	if(print_grammar_item) cout <<"�����"<<endl;
	return 0;
}

//�������䣬ʵ���˵����з�֧��Ԥ����
int Parse::proc_case_stat(const string name, const enum kinds type, const string end_lable) {
	if (Lexer::symbol != kinds::CASE) {
		return 1;//�׵��ʲ���case
	}
	Lexer::getToken();
	enum kinds const_type;
	int const_value;
	proc_const(const_type, const_value);//�˺�����Ԥ����
	const string tmp = new_val(INTSY, 0);
	const string case_lable = new_lable();
	Intermediate_code::push_back(Quaternion("-", name, int2str(const_value), tmp));
	Intermediate_code::push_back(Quaternion("~BNZ", tmp, case_lable, ""));
	if (type != const_type) {
		Error::addError(Lexer::line, ERROR_TYPE_IN_CASE);
	}
	if (Lexer::symbol != kinds::COLONSY) {
		//����ð�ţ�����
		Error::addError(Lexer::line, MISS_COLONSY);
	} else {
		Lexer::getToken();
		proc_stat();//����ʵ����Ԥ����
		Intermediate_code::push_back(Quaternion("~GOTO", end_lable, "", ""));
		Intermediate_code::push_back(Quaternion("~LABLE", case_lable, "", ""));
		if(print_grammar_item) cout <<"��������"<<endl;
		return 0;
	}
	return 1;
}

//����������case�����, ʵ�������з�֧��Ԥ���룬�����ۺ�����
int Parse::proc_const(enum kinds &type, int &value) {
	if (Lexer::symbol == kinds::CHARSY) {
		//���ַ���������ɶ��
		type = kinds::CHARSY;
		value = Lexer::num;
		Lexer::getToken();
		if(print_grammar_item) cout <<"���������������������У�"<<endl;
		return 0;
	} else if (0 == proc_int_num(value)) {//���ʵ����Ԥ����
		//�� proc_int_num() �õ�����������ɶ��
		type = kinds::INTSY;
		if(print_grammar_item) cout <<"���������������������У�"<<endl;
		return 0;
	}
	//���ַ��������������������������Ϸ�
	Error::addError(Lexer::line, ERROR_TYPE_IN_CONST);
	return 1;
}

//default��䣬ʵ�������з�֧��Ԥ����
int Parse::proc_default() {
	if (Lexer::symbol != kinds::DEFAULT) {
		//�׵��ʴ��󣬱���
		Error::addError(Lexer::line, MISS_DEFAULT);
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::COLONSY) {
		//ð�Ŵ��󣬱���
		Error::addError(Lexer::line, MISS_COLONSY);
	}
	Lexer::getToken();
	proc_stat();//��䴦��
	if(print_grammar_item) cout <<"default���"<<endl;
	return 0;
}

//��ֵ��䣬ʵ�������з�֧��Ԥ����
int Parse::proc_assi_stat() {
	if (Lexer::symbol != kinds::IDSY) {
		//�󲿱�ʶ�������⣬����
		Error::addError(Lexer::line, MISS_IDSY);
	}
	const string ID_name = Lexer::token;
	const enum kinds ID_type = Table::get_type(cur_fun, ID_name);
	Lexer::getToken();
	if (Lexer::symbol == kinds::ASINSY) {//���Ǽ򵥳���
		Lexer::getToken();
		string expr_name;
		enum kinds expr_type;
		proc_expr(expr_name, expr_type);//���ʽ
		if (!((ID_type == expr_type && expr_type == kinds::INTSY) || 
			(ID_type == expr_type && expr_type == kinds::CHARSY) || 
			(ID_type == kinds::INTSY && expr_type == kinds::CHARSY))) {
			Error::addError(Lexer::line, UNMATCHING);
		}
		Intermediate_code::push_back(Quaternion("=", expr_name, "", ID_name));
		if(print_grammar_item) cout <<"��ֵ���"<<endl;
		return 0;
	} else if (Lexer::symbol == kinds::LBRACSY) {//[˵����������
		if (Table::get_CLASS(cur_fun, ID_name) != _CLASS::ARRAY_CLASS) {//ID_name����������������
			Error::addError(Lexer::line, ERROR_USE_ARRAY);
		}
		Lexer::getToken();
		/*******************************���Խ�����*************************************/
		//����Խ�磿����ֻ��Ҫ�����ͳ�������������
		const int dim = Table::get_dim(cur_fun, ID_name);
		if (Lexer::symbol == kinds::INTSY) {//[]����������Խ�籨��
			if (!(0 <= Lexer::num && Lexer::num < dim)) {
				Error::addError(Lexer::line, ERROR_DIM_ARRAY);
			}
		} else if (Lexer::symbol == IDSY) {//[]���ǳ������������ͳ������ַ���������Խ�籨��
			if (Table::get_CLASS(cur_fun, Lexer::token) == _CLASS::CONST_CLASS) {
				if (!(0 <= Lexer::num && Lexer::num < dim)) {
					Error::addError(Lexer::line, ERROR_DIM_ARRAY);
				}
			}
		}
		/*******************************���Խ�����*************************************/
		string index_name;
		enum kinds index_type;
		proc_expr(index_name, index_type);//���ʽ
		if (index_type != kinds::INTSY && index_type != kinds::CHARSY) {
			Error::addError(Lexer::line, ERROR_TYP_ARRAY_INDEX);//ֻ����INTSY��CHARSY��Ϊ����
		}
		if (Lexer::symbol != RBRACSY) {
			//ȱ��]������
			Error::addError(Lexer::line, MISS_RBRACSY);
		}
		Lexer::getToken();
		if (Lexer::symbol != kinds::ASINSY) {
			//ȱ��=������
			Error::addError(Lexer::line, MISS_ASINSY);
		}
		Lexer::getToken();
		string expr_name;
		enum kinds expr_type;
		proc_expr(expr_name, expr_type);//���ʽ
		Intermediate_code::push_back(Quaternion("[]=", index_name, expr_name, ID_name));//������Ԫ�ظ�ֵ
		if(print_grammar_item) cout <<"��ֵ���"<<endl;
		return 0;		
	} else {
		//��ʶ�����治��=��Ҳ����[������
		return 1;
	}
}

//����䣬ʵ�������з�֧��Ԥ����
int Parse::proc_read_stat() {
	if (Lexer::symbol != kinds::SCANF) {
		//scanf���󣬱���
		return 1;
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::LPARSY) {
		//(���󣬱���
		Error::addError(Lexer::line, MISS_LPARSY);
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::IDSY) {
		//��һ����ʶ���ʹ��˻���û�У�����
		Error::addError(Lexer::line, ERROR_IDSY);
		while (Lexer::symbol != kinds::SEMISY) {
			Lexer::getToken();
		}
		return 1;
	}
	string para_name = Lexer::token;
	if (Table::get_CLASS(cur_fun, para_name) != _CLASS::VAL_CLASS) {
		Error::addError(Lexer::line, ERROR_SCANF);	
	}
	enum kinds type = Table::get_type(cur_fun, para_name);
	string typ = type==kinds::INTSY?"INTSY":"CHARSY";
	Intermediate_code::push_back(Quaternion("~SCANF", "!"+typ, para_name, ""));
	Lexer::getToken();
	while (Lexer::symbol == kinds::COMMASY) {//�ж���˵������Ҫ����
		Lexer::getToken();
		if (Lexer::symbol != kinds::IDSY) {
			//��ʶ�����˻���û�У�����
			Error::addError(Lexer::line, ERROR_IDSY);
			while (Lexer::symbol != kinds::SEMISY) {
				Lexer::getToken();
			}
			return 1;
		}
		para_name = Lexer::token;
		if (Table::get_CLASS(cur_fun, para_name) != _CLASS::VAL_CLASS) {
			Error::addError(Lexer::line, ERROR_SCANF);	
		}
		type = Table::get_type(cur_fun, para_name);
		typ = type==kinds::INTSY?"INTSY":"CHARSY";
	Intermediate_code::push_back(Quaternion("~SCANF", "!"+typ, para_name, ""));
		Lexer::getToken();
	}
	if (Lexer::symbol != kinds::RPARSY) {
		//ȱ�����������ţ�����
		Error::addError(Lexer::line, MISS_RPARSY);
	}
	Lexer::getToken();
	if(print_grammar_item) cout << "�����"<<endl;
	return 0;
}

//д��䣬ʵ�������з�֧��Ԥ����
int Parse::proc_writ_stat() {
	if (Lexer::symbol != kinds::PRINTF) {
		//scanf���󣬱���
		return 1;
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::LPARSY) {
		//(���󣬱���
		return 1;
	}
	Lexer::getToken();
	if (Lexer::symbol == kinds::STRSY) {
		//���ڶ������ַ�����������ܻ��ж��ţ���ʶ��
		Intermediate_code::push_back(Quaternion("~PRINT", "!STRING", StringTable::add(Lexer::token), ""));
		Lexer::getToken();
		if (Lexer::symbol == kinds::COMMASY) {
			//�ж����˶��ţ����������б��ʽ
			Lexer::getToken();
			string expr_name;
			enum kinds expr_type;
			proc_expr(expr_name, expr_type);
			if (expr_type != kinds::INTSY && expr_type != kinds::CHARSY) {
				Error::addError(Lexer::line, ERROR_PRINT);
				while (Lexer::symbol != kinds::SEMISY) {
					Lexer::getToken();
				}
				return 1;
			}
			const string typ = expr_type==kinds::INTSY?"INTSY":"CHARSY";
			Intermediate_code::push_back(Quaternion("~PRINT", "!"+typ, expr_name, ""));
			//�ﵽ����������print�ַ����ͱ��ʽ����������Ԥ����
		}
	} else {//ֻ�б��ʽ
		string expr_name;
		enum kinds expr_type;
		proc_expr(expr_name, expr_type);
		if (expr_type != kinds::INTSY && expr_type != kinds::CHARSY) {
			Error::addError(Lexer::line, ERROR_PRINT);
			while (Lexer::symbol != kinds::SEMISY) {
				Lexer::getToken();
			}
			return 1;
		}
		const string typ = expr_type==kinds::INTSY?"INTSY":"CHARSY";
		Intermediate_code::push_back(Quaternion("~PRINT", "!"+typ, expr_name, ""));
	}
	if (Lexer::symbol != kinds::RPARSY) {
		//ȱ�����������ţ�����
		Error::addError(Lexer::line, MISS_RPARSY);
	}
	Intermediate_code::push_back(Quaternion("~PRINT", "!STRING", "string_0", ""));
	Lexer::getToken();
	if(print_grammar_item) cout <<"д���"<<endl;
	return 0;
}

//������䣬ʵ�������з�֧��Ԥ����
int Parse::proc_retu_stat() {//������ʵӦ�ûش��������ͣ����ں������ж����޷�����䡢���������Ƿ���ȷ
	if (Lexer::symbol != kinds::RETURN) {
		//�׵��ʲ���return������
		return 1;
	}
	Lexer::getToken();
	if (Lexer::symbol == kinds::SEMISY) {
		//return; ��䣬�൱������Ԥ����
		Intermediate_code::push_back(Quaternion("~RETURN", "~NONE", "", ""));
		if(print_grammar_item) cout <<"return��䣨�޷���ֵ��"<<endl;
		return 0;
	}
	if (Lexer::symbol != kinds::LPARSY) {
		//(���󣬱���
		Error::addError(Lexer::line, MISS_LPARSY);
	}
	Lexer::getToken();
	string expr_name;
	enum kinds expr_type;
	proc_expr(expr_name, expr_type);
	if (expr_type != kinds::CHARSY && expr_type != kinds::INTSY) {
		Error::addError(Lexer::line, ERROR_RETURN_TYPE);
	}
	const string typ = expr_type==kinds::INTSY?"INTSY":"CHARSY";
	Intermediate_code::push_back(Quaternion("~RETURN", "!"+typ, expr_name, ""));
	if (Lexer::symbol != kinds::RPARSY) {
		//)���󣬱���
		Error::addError(Lexer::line, MISS_RPARSY);
	}
	Lexer::getToken();
	if(print_grammar_item) cout<<"return��䣨�з���ֵ��"<<endl;
	return 0;
}

//�±�ǩ
string Parse::new_lable() {
	static int lable_num = 0;
	return "lable_" + int2str(lable_num++);
}

//����ʱ����
string Parse::new_val(const kinds type, const int value) {
	static int val_num = 0;
	string name = int2str(val_num++) + "_t";//����ȡ���ֱ����˺���ʱ��������
	Table::val_enter_t(name, type, value);
	return name;
}
