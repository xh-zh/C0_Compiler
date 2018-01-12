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

//处理整数：[+|-]<无符号整数>|0，实现了所有分支的预读入，返回num
int Parse::proc_int_num(int &num) {
	int sign = 1;
	if (Lexer::symbol == kinds::PLUSSY) {//带正号的正整数
		sign = 1;
		Lexer::getToken();
		if (Lexer::symbol != kinds::USINTSY ||
			(Lexer::symbol == kinds::USINTSY && Lexer::num == 0)) {
			//正号后面没有数字或后面是0，报错
			Error::addError(Lexer::line, ERROR_INT);
		}
	} else if (Lexer::symbol == kinds::MINUSSY) {//带负号的负整数
		sign = -1;
		Lexer::getToken();
		if (Lexer::symbol != kinds::USINTSY ||
			(Lexer::symbol == kinds::USINTSY && Lexer::num == 0)) {
			//负号后面没有数字或后面是0，报错
			Error::addError(Lexer::line, ERROR_INT);
		}
	} else if (Lexer::symbol != kinds::USINTSY) {
		//没有正负号，没有数字
		Error::addError(Lexer::line, ERROR_INT);
	}
	//不带符号的正整数
	num = sign * Lexer::num;//保存这个整数值
	Lexer::getToken();//预读入
	if(print_grammar_item) cout << "整数" << endl;
	return 0;
}

//程序，主函数不会预读入
int Parse::proc_program() {
	bool have_main = false;
	//常量说明
	if (Lexer::symbol == kinds::CONST) {
		proc_const_decl();//处理常量说明
	}
	//变量说明
	int save_p = save_ptr++;
	if (Lexer::symbol == kinds::INT || Lexer::symbol == kinds::CHAR) {
		Lexer::save(save_p);//保存当前读到的位置
		Lexer::getToken();//标识符
		Lexer::getToken();//如果是函数应该读到左括号
		if (Lexer::symbol != kinds::LPARSY) {
			Lexer::recover(save_p);//恢复位置
			proc_var_decl();//处理变量说明
		} else {//说明接下来的是函数说明，也要恢复
			Lexer::recover(save_p);
		}
	}
	Intermediate_code::push_back(Quaternion("~FUN", "~BEGIN", "", ""));
	//函数说明
	while (Lexer::symbol == kinds::INT || Lexer::symbol == kinds::CHAR || Lexer::symbol == kinds::VOID) {
		save_p = save_ptr++;
		if (Lexer::symbol == kinds::VOID) {//无返回值函数
			Lexer::save(save_p);
			Lexer::getToken();
			//这里保证了不会出现主函数以外的void mian函数
			if (Lexer::symbol == kinds::MAIN) {//读到主函数
				Lexer::recover(save_p);
				break;
			}
			Lexer::recover(save_p);
			proc_void_fun_decl();//处理无返回值函数声明
		}
		else {//有返回值函数
			//干脆在外面检查了函数名是不是main
			Lexer::save(save_p);
			Lexer::getToken();
			if (Lexer::symbol == kinds::MAIN) {
				//函数名是main，跟主函数重名，错误
				have_main = true;
				Error::addError(Lexer::line, ERROR_MAIN_FUN_TYP);
			}
			Lexer::recover(save_p);
			proc_ioc_fun_decl();//处理有返回值函数声明
		}
	}
	if (Lexer::symbol == kinds::VOID) {//主函数
		proc_main_fun();//主函数
	}else if (!have_main) {
		//没有主函数，报错
		Error::addError(Lexer::line, MISS_MAIN_FUN);
	}
	if(print_grammar_item) cout<<"程序" <<endl;
	return 0;
}

//常量说明，实现了预读入
int Parse::proc_const_decl() {
	//由父函数保证已经读到一个const才会执行此函数
	do {
		Lexer::getToken();
		proc_const_defi();
		if (Lexer::symbol != kinds::SEMISY) {
			//常量定义后面不是分号，报错
			Error::addError(Lexer::line, MISS_SEMISY);
			if (Lexer::symbol != kinds::COMMASY) {//不是逗号，跳读
				int save_p = save_ptr++;
				Lexer::save(save_p);
				while (Lexer::symbol != kinds::CONST) {
					save_p = save_ptr++;
					Lexer::save(save_p);
					Lexer::getToken();
				}
				Lexer::recover(save_p);
			}
			//是逗号就接着往下走，和分号一样（容错）
		}
		//正确源代码这里不会跳过，只有在不是分号且不是逗号的情况下才会跳过，遇到逗号致报一个错，其余的和分号一样
		if (Lexer::symbol != kinds::INT && Lexer::symbol != kinds::CHAR) {
			Lexer::getToken();
		}
	}
	while (Lexer::symbol == kinds::CONST);//读到CONST说明仍在声明常量，否则跳出
	if(print_grammar_item) cout << "常量说明" <<endl;
	return 0;
}

//常量定义，实现了预读入，填符号表
int Parse::proc_const_defi() {
	string name;
	int value;
	if (Lexer::symbol == kinds::INT) {
		Lexer::getToken();
		do {
			if (Lexer::symbol != kinds::IDSY) {
				//没出现标识符
				Error::addError(Lexer::line, MISS_IDSY);
				while (Lexer::symbol != IDSY) {//跳读到下一个标识符，这样做其实有风险，很容易跳读到常量定义之外了
					Lexer::getToken();
				}
			}
			if (Lexer::symbol == kinds::MAIN) {//不允许出现名为main的标识符
				Error::addError(Lexer::line, ERROR_USE_MAIN);
			}
			name = Lexer::token;
			Lexer::getToken();
			if(Lexer::symbol != kinds::ASINSY) {
				//没出现等号
				Error::addError(Lexer::line, MISS_ASINSY);
				while (Lexer::symbol != IDSY) {//跳读到下一个标识符，这样做其实有风险，很容易跳读到常量定义之外了
					Lexer::getToken();
				}
				continue;
			}
			Lexer::getToken();
			proc_int_num(value);//处理等号右端的整数
			if (0 != Table::con_enter(name, kinds::INTSY, value)) {//填表
				//重复定义，后者不入表
				Error::addError(Lexer::line, ANOTHER_DEF);
			} else {
				Intermediate_code::push_back(Quaternion("~CONST", "!INTSY", int2str(value), name));
			}
			if (Lexer::symbol != kinds::COMMASY) {
				break;
			}
			Lexer::getToken();//为下一次循环做预读入
		}
		while (true);
	}
	else if (Lexer::symbol == kinds::CHAR) {
		Lexer::getToken();
		do {
			if (Lexer::symbol != kinds::IDSY) {
				//没出现标识符
				Error::addError(Lexer::line, MISS_IDSY);
				while (Lexer::symbol != IDSY) {//跳读到下一个标识符，这样做其实有风险，很容易跳读到常量定义之外了
					Lexer::getToken();
				}
			}
			if (Lexer::symbol == kinds::MAIN) {//不允许出现名为main的标识符
				Error::addError(Lexer::line, ERROR_USE_MAIN);
			}
			name = Lexer::token;
			Lexer::getToken();
			if (Lexer::symbol != kinds::ASINSY) {
				//没出现等号
				Error::addError(Lexer::line, MISS_ASINSY);
				while (Lexer::symbol != IDSY) {//跳读到下一个标识符，这样做其实有风险，很容易跳读到常量定义之外了
					Lexer::getToken();
				}
				continue;
			}
			Lexer::getToken();
			if (Lexer::symbol != kinds::CHARSY) {
				//等号右边不是char
				Error::addError(Lexer::line, UNMATCHING);
			} else {
				value = Lexer::num;//charsy的value即其assic值
				if (0 != Table::con_enter(name, kinds::CHARSY, value)) {//填表
					//重复定义
					Error::addError(Lexer::line, ANOTHER_DEF);
				} else {
					Intermediate_code::push_back(Quaternion("~CONST", "!CHARSY", int2str(value), name));
				}
			}
			Lexer::getToken();
			if (Lexer::symbol != kinds::COMMASY) {
				break;
			}
			Lexer::getToken();//为下一次迭代做预读入
		}
		while (true);
	} else {
		//const后出现int、char以外的东西
		//错误局部化
		return 1;
	}
	if(print_grammar_item) cout<<"常量定义"<<endl;
	return 0;
}

//变量说明，实现了预读入
int Parse::proc_var_decl() {
	//父函数保证读到int或char且不是函数说明才会进入此函数
	do {
		int save_p = save_ptr++;
		Lexer::save(save_p);
		Lexer::getToken();
		Lexer::getToken();
		if (Lexer::symbol == kinds::LPARSY) {//读到左括号说明是函数声明
			Lexer::recover(save_p);
			return 0;
		}
		Lexer::recover(save_p);
		proc_var_defi();
		if (Lexer::symbol != kinds::SEMISY) {
			//缺少分号，报错
			Error::addError(Lexer::line, MISS_SEMISY);
			if (Lexer::symbol != kinds::COMMASY) {//不是逗号，跳读
				save_p = save_ptr++;
				Lexer::save(save_p);
				while (Lexer::symbol != kinds::INT && Lexer::symbol != kinds::CHAR) {
					save_p = save_ptr++;
					Lexer::save(save_p);
					Lexer::getToken();
				}
				Lexer::recover(save_p);
			}
			//是逗号就接着往下走，和分号一样（容错）
		}
		//正确源代码这里不会跳过，只有在不是分号且不是逗号的情况下才会跳过，遇到逗号致报一个错，其余的和分号一样
		if (Lexer::symbol != kinds::INT && Lexer::symbol != kinds::CHAR) {
			Lexer::getToken();
		}
	}
	while (Lexer::symbol == kinds::INT || Lexer::symbol == kinds::CHAR);
	if(print_grammar_item) cout<<"变量说明" <<endl;
	return 0;
}

//变量定义， 实现了预读入，填符号表
int Parse::proc_var_defi() {
	if (Lexer::symbol == kinds::INT || Lexer::symbol == kinds::CHAR) {
		const enum kinds type = Lexer::symbol==kinds::INT?kinds::INTSY:kinds::CHARSY;
		const string typ = type==kinds::INTSY?"INTSY":"CHARSY";
		Lexer::getToken();
		do {
			if (Lexer::symbol != kinds::IDSY) {
				//没出现标识符
				return 1;
			}
			const string name = Lexer::token;
			Lexer::getToken();
			if (Lexer::symbol == kinds::LBRACSY ) {//数组
				Lexer::getToken();
				if (Lexer::symbol != kinds::USINTSY) {
					//方括号后不是整数
					return 1;
				}
				const int dim = Lexer::num;
				if (dim <= 0) {
					Error::addError(Lexer::line, ERROR_ARRAY_DIM_0);
				}
				Lexer::getToken();
				if (Lexer::symbol != kinds::RBRACSY) {
					//没有右方括号
					return 1;
				}
				//此处可以确定数组声明正确（且不论后面的逗号或分号）
				Table::array_enter(name, type, dim);//填表
				Intermediate_code::push_back(Quaternion("~ARRAY", "!"+typ, int2str(dim), name));
				Lexer::getToken();
			} else {
				//此处可以确定变量声明正确（且不论后面的逗号或分号）
				Table::val_enter(name, type);//填表
				Intermediate_code::push_back(Quaternion("~VAL", "!"+typ, "", name));
			}
			if (Lexer::symbol != kinds::COMMASY) {
				break;
			}
			Lexer::getToken();
		}
		while (true);
	} else {
		//const后出现int、char以外的东西
		//错误局部化
		return 1;
	}
	if(print_grammar_item) cout<<"变量定义"<<endl;
	return 0;
}

//无返回值函数定义， 有预读入
int Parse::proc_void_fun_decl() {
	if (Lexer::symbol != kinds::VOID) {
		//返回值类型有误，报错
		Error::addError(Lexer::line, ERROR_RET_TYPE);
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::IDSY) {
		//函数名错误，这样就没法填符号表了，因此返回
		Error::addError(Lexer::line, MISS_IDSY);
		return 1;
	}
	const string name = Lexer::token;
	cur_fun = name;
	//我觉得在这里就就应该填符号表了,但是这里确定不了参数个数，因此需要回填参数个数，回填的同时要记得更改符号表的level，cur_parent
	if (0 != Table::func_enter(name, kinds::VOID)) {
		//声明过同名。。。
		Error::addError(Lexer::line, ANOTHER_DEF);
	} else {
		Intermediate_code::push_back(Quaternion("~FUN", "!VOID", name, ""));//生成中间代码
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::LPARSY) {//这里认为缺少左括号后就直接是参数列表了
		//缺少左括号
		Error::addError(Lexer::line, MISS_LPARSY);
	} else
		Lexer::getToken();
	int dim = 0;
	if (Lexer::symbol != kinds::RPARSY) {
		//缺少右括号,认为有参数
		if (0 != proc_para(dim)) {
			//参数表有误
			return 1;
		}
		if (Lexer::symbol != kinds::RPARSY) {//默认接受了参数表的预读入
			//参数表正确，然额没有右括号，这里应该要进行适度容错
			Error::addError(Lexer::line, MISS_RPARSY);
		}
	}
	Table::func_fill_back_dim(name, dim);//回填参数个数，不然递归调用时没法判断参数个数是否正确
	//左右括号齐全，参数表正确
	Lexer::getToken();
	if (Lexer::symbol != kinds::LCBRACSY) {
		//缺少左花括号
		Error::addError(Lexer::line, MISS_LCBRACSY);
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::RCBRACSY) {
		proc_cplx_stat();//处理复合语句
		if (Lexer::symbol != kinds::RCBRACSY) {
			//缺少右花括号
			Error::addError(Lexer::line, MISS_RCBRACSY);
		}
	} 
	//左右花括号齐全，参数表正确
	//函数声明完毕
	//填表
	Intermediate_code::push_back(Quaternion("~END", name, "", ""));//四元式中插入函数声明结束标志
	Table::func_fill_back_value(name);//回填栈空间大小
	cur_fun = "top";
	Lexer::getToken();
	if(print_grammar_item) cout << "无返回值函数定义" <<endl;
	return 0;
}

//有返回值函数定义，有预读入
int Parse::proc_ioc_fun_decl() {
	if (Lexer::symbol != kinds::INT && Lexer::symbol != kinds::CHAR) {
		//返回值类型有误，报错
		Error::addError(Lexer::line, ERROR_RET_TYPE);
	}
	const enum kinds type = Lexer::symbol==kinds::INT?kinds::INTSY:kinds::CHARSY;
	Lexer::getToken();
	if (Lexer::symbol != kinds::IDSY) {
		//函数名错误，这样就没法填符号表了，因此返回
		Error::addError(Lexer::line, MISS_IDSY);
		return 1;
	}
	const string name = Lexer::token;
	cur_fun = name;
	if (0 != Table::func_enter(name, type)) {
		//声明过同名。。。
		Error::addError(Lexer::line, ANOTHER_DEF);
	} else {
		const string typ = type==kinds::INTSY?"INTSY":"CHARSY";
		Intermediate_code::push_back(Quaternion("~FUN", "!"+typ, name, ""));//生成中间代码
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::LPARSY) {//这里认为缺少左括号后就直接是参数列表了
		//缺少左括号
		Error::addError(Lexer::line, MISS_LPARSY);
	} else
		Lexer::getToken();
	int dim = 0;
	if (Lexer::symbol != kinds::RPARSY) {
		//缺少右括号,认为有参数
		if (0 != proc_para(dim)) {
			//参数表有误
			return 1;
		}
		if (Lexer::symbol != kinds::RPARSY) {//默认接受了参数表的预读入
			//参数表正确，然额没有右括号，这里应该要进行适度容错
			Error::addError(Lexer::line, MISS_RPARSY);
		}
	}
	Table::func_fill_back_dim(name, dim);//回填参数个数，不然递归调用时没法判断参数个数是否正确
	//左右括号齐全，参数表正确
	Lexer::getToken();
	if (Lexer::symbol != kinds::LCBRACSY) {
		//缺少左花括号
		Error::addError(Lexer::line, MISS_LCBRACSY);
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::RCBRACSY) {
		proc_cplx_stat();//处理复合语句
		if (Lexer::symbol != kinds::RCBRACSY) {
			//缺少右花括号
			Error::addError(Lexer::line, MISS_RCBRACSY);
		}
	} 
	//左右花括号齐全，参数表正确
	//函数声明完毕
	//填表
	Intermediate_code::push_back(Quaternion("~END", name, "", ""));//四元式中插入函数声明结束标志
	Table::func_fill_back_value(name);//这里其实是回填栈空间大小
	cur_fun = "top";
	Lexer::getToken();
	if(print_grammar_item) cout << "有返回值函数定义" <<endl;
	return 0;
}

//主函数, 无预读入
int Parse::proc_main_fun() {
	if (Lexer::symbol != kinds::VOID) {
		//报错，不过应该是其调用函数保证不会不是void
		return 1;
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::MAIN) {
		//报错，不过应该是其调用函数保证不会不是main
		return 1;
	}
	cur_fun = "main";
	if (0 != Table::func_enter("main", kinds::VOID)) {//mian无参数，之后的声明只能是在main这层，故不回填
		//报错，main已经被声明过了
		return 1;
	}
	Intermediate_code::push_back(Quaternion("~FUN", "!VOID", "main", ""));//生成中间代码
	Lexer::getToken();
	if (Lexer::symbol != kinds::LPARSY) {
		//报错
		return 1;
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::RPARSY) {
		//报错
		return 1;
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::LCBRACSY) {
		//报错
		return 1;
	}
	Lexer::getToken();
	if ( 0!=proc_cplx_stat()) {
		//复合语句有误
		return 1;
	}
	if (Lexer::symbol != kinds::RCBRACSY) {
		//报错
		return 1;
	}
	//Lexer::getToken();//预读入
	Table::func_fill_back_dim("main", 0);//其实这里不回填也没事，因为dim默认为0
	Table::func_fill_back_value("main");
	cur_fun = "top";//实则可有可无
	Intermediate_code::push_back(Quaternion("~TERMINATE", "" ,"" ,""));
	if(print_grammar_item) cout <<"主函数"<<endl;
	return 0;
}

//参数，也是参数表，函数声明时()里面的，有预读入
int Parse::proc_para(int &dim) {
	int d = 0;
	while (Lexer::symbol == kinds::INT || Lexer::symbol == kinds::CHAR) {
		const enum kinds type = Lexer::symbol==kinds::INT?INTSY:CHARSY;
		Lexer::getToken();
		if (Lexer::symbol != kinds::IDSY) {
			//参数列表不是标识符，报错，这里最好错误局部化
			Error::addError(Lexer::line, MISS_IDSY);
			while (!(Lexer::symbol == kinds::INT || Lexer::symbol == kinds::CHAR)) {
				Lexer::getToken();//这里有读到别的模块的风险
			}
		}
		const string name = Lexer::token;
		if (0 != Table::para_enter(name, type, d)) {//填符号表
			//本层有同名标识符，报错
			Error::addError(Lexer::line, ANOTHER_DEF);
		}
		const string typ = type==kinds::INTSY?"INTSY":"CHARSY";
		Intermediate_code::push_back(Quaternion("~PARA", "!"+typ, name, ""));//生成中间代码
		Lexer::getToken();
		d++;
		if (Lexer::symbol != kinds::COMMASY) {
			break;
		}
		Lexer::getToken();
	}
	dim = d;
	if(print_grammar_item) cout << "参数表" <<endl;
	return 0;
}

//复合语句，有预读入
int Parse::proc_cplx_stat() {
	//常量说明
	if (Lexer::symbol == kinds::CONST) {
		proc_const_decl();
	}
	//变量说明
	if (Lexer::symbol == kinds::INT || Lexer::symbol == kinds::CHAR) {
		proc_var_decl();
	}
	//语句列
	proc_stat_list();
	if(print_grammar_item) cout << "复合语句"<<endl;
	return 0;
}

//语句列，实现了预读入
int Parse::proc_stat_list() {
	//没法判断是正确读完所有的语句还是出错了
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
			proc_stat();//语句处理
			break;
		default:
			if(print_grammar_item) cout <<"语句列"<<endl;
			return 0;
		}
		Lexer::save(save_p);
		if (-1 == Lexer::getToken()) {
			break;
		}
		Lexer::recover(save_p);
	}
	if(print_grammar_item) cout <<"语句列"<<endl;
	return 0;
}

//if语句，有预读入，由调用者保证已经识别到if
int Parse::proc_if_stat() {
	//由调用者保证已经识别到if
	//实际上很难做到每个地方都有调用者来保证，所以我还是认为函数自身再检查一遍为好
	if (Lexer::symbol != kinds::IF) {
		return 1;//首个单词并不是if，不存在的！没有if就不会进入此方法
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::LPARSY) {//认为没有左括号就直接是条件了
		//没有左括号
		Error::addError(Lexer::line, MISS_LPARSY);
	} else 
		Lexer::getToken();
	string val1;//存放条件中间结果
	enum kinds cond_type;
	proc_cond(val1, cond_type);//处理条件
	if (cond_type != kinds::INTSY) {//条件结果必须是整型
		Error::addError(Lexer::line, ERROR_COND_TYPE);
	}
	if (Lexer::symbol != kinds::RPARSY ) {
		//没有右括号，报错
		Error::addError(Lexer::line, MISS_LPARSY);
	}
	//接下来处理语句
	const string lable1 = new_lable();
	Intermediate_code::push_back(Quaternion("~BZ", val1, lable1, ""));//处理语句前要生成跳转指令
	Lexer::getToken();
	proc_stat();
	const string lable2 = new_lable();
	Intermediate_code::push_back(Quaternion("~GOTO", lable2, "", ""));//插入无条件跳转语句
	Intermediate_code::push_back(Quaternion("~LABLE", lable1, "", ""));//插入标签
	if (Lexer::symbol == kinds::ELSE) {
		Lexer::getToken();
		proc_stat();
	}
	Intermediate_code::push_back(Quaternion("~LABLE", lable2, "", ""));//插入标签
	if(print_grammar_item) cout <<"if语句"<<endl;
	return 0;
}

//条件，出现在if、for中，有预读入
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
		Lexer::symbol == kinds::EQUSY || Lexer::symbol == kinds::NEQUSY) {//条件运算符，说明会有形为1>2的形式
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
		Intermediate_code::push_back(Quaternion(op, val1, val2, result));//生成目标代码
	} else {//括号里只有一个表达式
		result = val1;
	}
	type = kinds::INTSY;
	if(print_grammar_item) cout <<"条件（出现在if、for语句的括号中）"<<endl;
	return 0;
}

//语句， 实现了所有分支的预读入
int Parse::proc_stat() {
	if (Lexer::symbol == kinds::IF) {	//if语句
		proc_if_stat();//if语句处理
		return 0;
	}
	if (Lexer::symbol == kinds::FOR) {//for语句
		proc_for_stat();//for语句处理
		return 0;
	}
	if (Lexer::symbol == kinds::LCBRACSY) {//{语句列}
		Lexer::getToken();
		proc_stat_list();//语句列处理
		if (Lexer::symbol != kinds::RCBRACSY) {
			//语句列没有}
			Error::addError(Lexer::line, MISS_RCBRACSY);
		}
		Lexer::getToken();//预读入
		return 0;
	}
	if (Lexer::symbol == kinds::SWITCH) {//swith-case语句
		proc_swit_stat();//switch-case语句
		return 0;
	}
	if (Lexer::symbol == kinds::SEMISY) {//空语句
		Lexer::getToken();
		if(print_grammar_item) cout << "空语句"<<endl;
		return 0;
	}
	if (Lexer::symbol == kinds::SCANF) {//读语句
		proc_read_stat();//读语句
	} else if (Lexer::symbol == kinds::PRINTF) {//写语句
		proc_writ_stat();//写语句
	} else if (Lexer::symbol == kinds::RETURN) {//返回语句
		proc_retu_stat();//返回语句
	} else if (Lexer::symbol == kinds::IDSY) {
		const int save_p = save_ptr++;
		Lexer::save(save_p);
		Lexer::getToken();
		if (Lexer::symbol == kinds::ASINSY || Lexer::symbol == kinds::LBRACSY) {	//赋值语句
			Lexer::recover(save_p);
			proc_assi_stat();//赋值语句
		} else if (Lexer::symbol == kinds::LPARSY) {//函数调用语句
			//查符号表，再决定调用有返回值函数语句还是无返回值函数语句
			///现在两个函数调用语句都一样
			Lexer::recover(save_p);
			string fun_retron_name;
			enum kinds fun_retron_type;
			proc_cal_fun(fun_retron_name, fun_retron_type);//函数调用语句
			//这里好像不用对返回值及其类型做任何检查
		} else {
			Lexer::recover(save_p);
			Error::addError(Lexer::line, UNDEFINED_STAT);
		}
	}
	//有分号语句统一在这里判断分号，无分号语句再各自的分支里就都判断完了
	if (Lexer::symbol != kinds::SEMISY) {
		//有分号语句缺少分号
		Error::addError(Lexer::line, MISS_SEMISY);
	}
	Lexer::getToken();//预读入
	if(print_grammar_item) cout <<"语句"<<endl;
	return 0;
}

//表达式，会有预读入
int Parse::proc_expr(string &result, kinds &type) {
	string sign = "+";
	if (Lexer::symbol == kinds::PLUSSY) {
		//正号，不用操作
		Lexer::getToken();
	} else if (Lexer::symbol == kinds::MINUSSY) {
		//负号，需要给第一个项乘-1
		sign = "-";
		Lexer::getToken();
	}
	string term_result;
	enum kinds term_type;
	proc_term(term_result, term_type);//项处理
	type = term_type;
	const string tmp_result = new_val(type, 0);
	if (sign == "-") Intermediate_code::push_back(Quaternion(sign, "0", term_result, tmp_result));//正号就不操作了
	else Intermediate_code::push_back(Quaternion("=", term_result, "", tmp_result));
	while (Lexer::symbol == kinds::PLUSSY || Lexer::symbol == kinds::MINUSSY) {
		//只要有加法运算符，就必有term，否则就是错的，所以只要是正确的输入，循环只会因为循环条件截止而不会return 1强制截止
		sign = Lexer::symbol==kinds::PLUSSY?"+":"-";
		Lexer::getToken();
		string val;
		proc_term(val, term_type);//项处理
		Intermediate_code::push_back(Quaternion(sign, tmp_result, val, tmp_result));
		if (term_type == kinds::INTSY) {
			type = kinds::INTSY;
			Table::set_type(tmp_result, INTSY);
		}
	}
	result = tmp_result;
	if(print_grammar_item) cout <<"表达式"<<endl;
	return 0;
}

//项，会有预读入
int Parse::proc_term(string &result, kinds &type) {
	string fact_result;
	enum kinds fact_type;
	proc_fact(fact_result, type);
	if (!(Lexer::symbol == kinds::STARSY || Lexer::symbol == kinds::DIVISY)) {//只有一项
		result = fact_result;
		if(print_grammar_item) cout <<"项"<<endl;
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
	if(print_grammar_item) cout <<"项"<<endl;
	return 0;
}

//因子，无论是哪个分支都有预读入
int Parse::proc_fact(string &result, kinds &type) {
	const int save_p = save_ptr++;
	switch (Lexer::symbol) {
	case kinds::USINTSY://整数：[+|-]<无符号整数>|0
	case kinds::PLUSSY:
	case kinds::MINUSSY:
		int int_num;
		proc_int_num(int_num);//处理整数
		//result = new_val(INTSY, int_num);
		result = int2str(int_num);
		type = kinds::INTSY;
		break;
	case kinds::CHARSY://字符
		//result = new_val(CHARSY, Lexer::num);
		result = "$"+int2str(Lexer::num);
		type = kinds::CHARSY;
		Lexer::getToken();
		break;
	case kinds::LPARSY://（表达式）
		Lexer::getToken();
		proc_expr(result, type);
		if (Lexer::symbol != kinds::RPARSY) {
			//没有右括号，报错
		}
		Lexer::getToken();
		break;
	case kinds::IDSY://标识符、数组元素、有返回值函数调用
		Lexer::save(save_p);
		Lexer::getToken();
		if (Lexer::symbol == kinds::LBRACSY) {//数组元素
			Lexer::recover(save_p);
			const string array_name = Lexer::token;
			if (!Table::contain(cur_fun, array_name)) {
				Error::addError(Lexer::line, UNDEFINED_IDSY);
			}
			if (Table::get_CLASS(cur_fun, array_name) != ARRAY_CLASS) {
				Error::addError(Lexer::line, UNMATCHING);
			}
			type = Table::get_type(cur_fun, array_name);
			Lexer::getToken();//读左方括号
			Lexer::getToken();
			string index_name;
			enum kinds index_type;
			/*******************************检查越界错误*************************************/
			//数组越界？？？只需要对整型常量或整数报错
			const int dim = Table::get_dim(cur_fun, array_name);
			if (Lexer::symbol == kinds::INTSY) {//[]里是整数，越界报错
				if (!(0 <= Lexer::num && Lexer::num < dim)) {
					Error::addError(Lexer::line, ERROR_DIM_ARRAY);
				}
			} else if (Lexer::symbol == IDSY) {//[]里是常量（包括整型常量、字符常量），越界报错
				if (Table::get_CLASS(cur_fun, Lexer::token) == _CLASS::CONST_CLASS) {
					if (!(0 <= Lexer::num && Lexer::num < dim)) {
						Error::addError(Lexer::line, ERROR_DIM_ARRAY);
					}
				}
			}
			/*******************************检查越界错误*************************************/	
			proc_expr(index_name, index_type);
			if (index_type != kinds::INTSY && index_type != kinds::CHARSY) {
			//只允许方括号里是非负整型或字符型，这里还无法判断是否越界（包括负越界）
				Error::addError(Lexer::line, ERROR_TYP_ARRAY_INDEX);
			}
			if (Lexer::symbol != kinds::RBRACSY) {
			//没有右方括号，报错
				Error::addError(Lexer::line, MISS_RBRACSY);
			}
			result = new_val(type, 0);
			Intermediate_code::push_back(Quaternion("=[]", array_name, index_name, result));
			Lexer::getToken();
		} else if (Lexer::symbol == kinds::LPARSY) {//有返回值函数调用
			Lexer::recover(save_p);
			proc_cal_fun(result, type);//有返回值调用语句
		} else {//标识符
			Lexer::recover(save_p);
			result = Lexer::token;
			if (Table::contain(cur_fun, result)) {//声明过此标识符，而且是简单类型
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
	if(print_grammar_item) cout <<"因子"<<endl;
	return 0;
}

//函数调用语句，包括参数列表，有预读入
int Parse::proc_cal_fun(string &result, kinds &type) {
	int dim = 0;
	string fun_name;
	if (Lexer::symbol != kinds::IDSY) {
		//没有标识符，报错，通常不会进入此分支
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
			//没有左括号，报错
			Error::addError(Lexer::line, MISS_LPARSY);
		} else {
			Lexer::getToken();
			if (Lexer::symbol != kinds::RPARSY) {
				//应该从这里开始检查参数类型和声明类型是否一致
				vector<TableEntity> fun_para = Table::get_para(fun_name);
				dim = 0;
				string para_name;
				enum kinds para_type;
				//第一个参数
				proc_expr(para_name, para_type);
				if (!(para_type == fun_para[dim].type || (para_type == kinds::CHARSY && fun_para[dim].type == kinds::INTSY)))
				{	
					Error::addError(Lexer::line, CAL_FUN_UNMATCHING);
				}
				dim++;
				string typ = para_type==kinds::INTSY?"INTSY":"CHARSY";
				Intermediate_code::push_back(Quaternion("~PUSH", para_name, fun_para[0].name, fun_name));
				while (Lexer::symbol == kinds::COMMASY ) {//读到逗号说明还有参数
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
					//没有右括号，报错
					Error::addError(Lexer::line, MISS_RPARSY);
				}
			} else {
				dim = 0;//参数列表为空
			}
		}
	}
	if (Table::get_dim(cur_fun, fun_name) != dim) {
		Error::addError(Lexer::line, ERROR_DIM_FUN);//函数参数个数不对
	}
	type = Table::get_type(cur_fun, fun_name);//INTSY/CHARSY/VOID
	result = new_val(type, 0);
	Intermediate_code::push_back(Quaternion("~CALL", fun_name, "", ""));
	Intermediate_code::push_back(Quaternion("=", "$v0", "", result));//保存返回值
	Lexer::getToken();
	if(print_grammar_item) cout<<"有返回值函数调用语句"<<endl;
	return 0;
}

//循环语句，正确分支有预读入
int Parse::proc_for_stat() {
	const int save1 = save_ptr++;
	const int save2 = save_ptr++;
	Intermediate_code::push_back(Quaternion("~LOOP", "~BEDIN", "", ""));
	if (Lexer::symbol != kinds::FOR) {
		return 1;
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::LPARSY ) {
		//缺少左括号，报错
		return 1;
	} else {
		Lexer::getToken();
		if (Lexer::symbol != kinds::IDSY) {
			//没有标识符，报错
			Error::addError(Lexer::line, MISS_IDSY);
		} else {
			const string ID_name = Lexer::token;
			const enum kinds ID_type = Table::get_type(cur_fun, ID_name);
			if (!Table::contain(cur_fun, ID_name)) {
				Error::addError(Lexer::line, UNDEFINED_IDSY);
			}
			Lexer::getToken();
			if (Lexer::symbol != kinds::ASINSY) {
				//不是赋值号，报错
				Error::addError(Lexer::line, MISS_ASINSY);
			} else {
				Lexer::getToken();
				string expr_name;
				enum kinds expr_type;
				proc_expr(expr_name, expr_type);//赋值号右部是表达式
				if (!((ID_type == expr_type && expr_type == kinds::INTSY) || 
					(ID_type == expr_type && expr_type == kinds::CHARSY) || 
					(ID_type == kinds::INTSY && expr_type == kinds::CHARSY))) {
					Error::addError(Lexer::line, UNMATCHING);
				}
				Intermediate_code::push_back(Quaternion("=", expr_name, "", ID_name));
				const string lable = new_lable();
				Intermediate_code::push_back(Quaternion("~LABLE", lable, "", ""));
				if (Lexer::symbol != kinds::SEMISY ) {
					//不是分号，报错
					Error::addError(Lexer::line, MISS_SEMISY);
				} else {
					Lexer::save(save1);//保存条件之前的现场
					do {//跳过条件部分
						Lexer::getToken();
					}
					while (Lexer::symbol != kinds::SEMISY);//接下来再读一个就可以处理步长了
					
					if (Lexer::symbol != kinds::SEMISY) {
						//条件后面没有分号，报错
						Error::addError(Lexer::line, MISS_SEMISY);
					} else {
						Lexer::getToken();
						if (Lexer::symbol != kinds::IDSY) {
							//步长部分没有第一个标识符，报错
							Error::addError(Lexer::line, MISS_IDSY);
						} else {
							const string ID2_name = Lexer::token;
							const enum kinds ID2_type = Table::get_type(cur_fun, ID2_name);
							if (!Table::contain(cur_fun, ID2_name)) {
								Error::addError(Lexer::line, UNMATCHING);
							}
							Lexer::getToken();
							if (Lexer::symbol != kinds::ASINSY) {
								//步长部分没出现等号，报错
								Error::addError(Lexer::line, MISS_ASINSY);
							} else {
								Lexer::getToken();
								if (Lexer::symbol != kinds::IDSY) {
									//步长部分没有第二个标识符，报错
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
										//没出现加减号，报错
										Error::addError(Lexer::line, MISS_PLUS_MINU);
									} else {
										const string op = Lexer::symbol == kinds::PLUSSY?"+":"-";
										Lexer::getToken();
										if (!(Lexer::symbol != kinds::USINTSY ||
											(Lexer::symbol == kinds::USINTSY && Lexer::num != 0))) {
											//步长不是正整数，报错
											Error::addError(Lexer::line, ERROR_TYPE_IN_BC);
										} else {
											const long step_long = Lexer::num;
											const string step = int2str(step_long);
											if(print_grammar_item) cout << "步长"<<endl;
											Lexer::getToken();
											if (Lexer::symbol != kinds::RPARSY ) {
												//for()缺少右括号
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
													proc_stat();//语句处理
													if(print_grammar_item) cout <<"for语句"<<endl;
													Intermediate_code::push_back(Quaternion(op, ID3_name, step, ID2_name));//加减步长
													Lexer::save(save2);//保存现场
													Lexer::recover(save1);//开始处理条件
													Lexer::getToken();
													string cond_name;
													enum kinds cond_type;
													proc_cond(cond_name, cond_type);//中间条件
													Lexer::recover(save2);
													Intermediate_code::push_back(Quaternion("~BNZ", cond_name, lable, ""));
													Intermediate_code::push_back(Quaternion("~LOOP", "~END"	, "", ""));
													return 0;
												}
												//不是语句的开头符号，正常情况不会到此分支
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
	return 1;//正确的代码不会执行这里
}

//switch-case语句，实现了所有分支的预读入
int Parse::proc_swit_stat() {
	if (Lexer::symbol != kinds::SWITCH) {
		return 1;//首个单词不是switch
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::LPARSY ) {
		Error::addError(Lexer::line, MISS_LPARSY);//switch后缺少(
	}
	Lexer::getToken();
	string expr_name;
	enum kinds expr_type;
	proc_expr(expr_name, expr_type);//这里有预读入
	if (Lexer::symbol != kinds::RPARSY) {
		Error::addError(Lexer::line, MISS_RPARSY);//缺少）
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::LCBRACSY) {
		Error::addError(Lexer::line, MISS_LCBRACSY);//缺少{
	}
	Lexer::getToken();
	const string end_lable = new_lable();
	proc_case_list(expr_name, expr_type, end_lable);//这里有预读入
	proc_default();//这里有预读入
	if (Lexer::symbol != kinds::RCBRACSY) {
		//缺少}，报错
		Error::addError(Lexer::line, MISS_RCBRACSY);
	}
	Intermediate_code::push_back(Quaternion("~LABLE", end_lable, "", ""));
	Lexer::getToken();//预读入
	if(print_grammar_item) cout <<"switch-case语句"<<endl;
	return 0;
}

//情况表，实现了所有分支的预读入
int Parse::proc_case_list(const string name, const enum kinds type, const string end_lable) {
	proc_case_stat(name, type, end_lable);//第一条情况子语句
	while (Lexer::symbol == kinds::CASE) {
		proc_case_stat(name, type, end_lable);//情况子语句出错
	}
	if(print_grammar_item) cout <<"情况表"<<endl;
	return 0;
}

//情况子语句，实现了的所有分支的预读入
int Parse::proc_case_stat(const string name, const enum kinds type, const string end_lable) {
	if (Lexer::symbol != kinds::CASE) {
		return 1;//首单词不是case
	}
	Lexer::getToken();
	enum kinds const_type;
	int const_value;
	proc_const(const_type, const_value);//此函数有预读入
	const string tmp = new_val(INTSY, 0);
	const string case_lable = new_lable();
	Intermediate_code::push_back(Quaternion("-", name, int2str(const_value), tmp));
	Intermediate_code::push_back(Quaternion("~BNZ", tmp, case_lable, ""));
	if (type != const_type) {
		Error::addError(Lexer::line, ERROR_TYPE_IN_CASE);
	}
	if (Lexer::symbol != kinds::COLONSY) {
		//不是冒号，报错
		Error::addError(Lexer::line, MISS_COLONSY);
	} else {
		Lexer::getToken();
		proc_stat();//这里实现了预读入
		Intermediate_code::push_back(Quaternion("~GOTO", end_lable, "", ""));
		Intermediate_code::push_back(Quaternion("~LABLE", case_lable, "", ""));
		if(print_grammar_item) cout <<"情况子语句"<<endl;
		return 0;
	}
	return 1;
}

//常量，用在case语句中, 实现了所有分支的预读入，两个综合属性
int Parse::proc_const(enum kinds &type, int &value) {
	if (Lexer::symbol == kinds::CHARSY) {
		//将字符常量返回啥的
		type = kinds::CHARSY;
		value = Lexer::num;
		Lexer::getToken();
		if(print_grammar_item) cout <<"常量（出现在情况子语句中）"<<endl;
		return 0;
	} else if (0 == proc_int_num(value)) {//这个实现了预读入
		//将 proc_int_num() 得到的整数返回啥的
		type = kinds::INTSY;
		if(print_grammar_item) cout <<"常量（出现在情况子语句中）"<<endl;
		return 0;
	}
	//非字符常量、整数常量，即常量不合法
	Error::addError(Lexer::line, ERROR_TYPE_IN_CONST);
	return 1;
}

//default语句，实现了所有分支的预读入
int Parse::proc_default() {
	if (Lexer::symbol != kinds::DEFAULT) {
		//首单词错误，报错
		Error::addError(Lexer::line, MISS_DEFAULT);
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::COLONSY) {
		//冒号错误，报错
		Error::addError(Lexer::line, MISS_COLONSY);
	}
	Lexer::getToken();
	proc_stat();//语句处理
	if(print_grammar_item) cout <<"default语句"<<endl;
	return 0;
}

//赋值语句，实现了所有分支的预读入
int Parse::proc_assi_stat() {
	if (Lexer::symbol != kinds::IDSY) {
		//左部标识符有问题，报错
		Error::addError(Lexer::line, MISS_IDSY);
	}
	const string ID_name = Lexer::token;
	const enum kinds ID_type = Table::get_type(cur_fun, ID_name);
	Lexer::getToken();
	if (Lexer::symbol == kinds::ASINSY) {//左部是简单常量
		Lexer::getToken();
		string expr_name;
		enum kinds expr_type;
		proc_expr(expr_name, expr_type);//表达式
		if (!((ID_type == expr_type && expr_type == kinds::INTSY) || 
			(ID_type == expr_type && expr_type == kinds::CHARSY) || 
			(ID_type == kinds::INTSY && expr_type == kinds::CHARSY))) {
			Error::addError(Lexer::line, UNMATCHING);
		}
		Intermediate_code::push_back(Quaternion("=", expr_name, "", ID_name));
		if(print_grammar_item) cout <<"赋值语句"<<endl;
		return 0;
	} else if (Lexer::symbol == kinds::LBRACSY) {//[说明左部是数组
		if (Table::get_CLASS(cur_fun, ID_name) != _CLASS::ARRAY_CLASS) {//ID_name不是数组名，报错
			Error::addError(Lexer::line, ERROR_USE_ARRAY);
		}
		Lexer::getToken();
		/*******************************检查越界错误*************************************/
		//数组越界？？？只需要对整型常量或整数报错
		const int dim = Table::get_dim(cur_fun, ID_name);
		if (Lexer::symbol == kinds::INTSY) {//[]里是整数，越界报错
			if (!(0 <= Lexer::num && Lexer::num < dim)) {
				Error::addError(Lexer::line, ERROR_DIM_ARRAY);
			}
		} else if (Lexer::symbol == IDSY) {//[]里是常量（包括整型常量、字符常量），越界报错
			if (Table::get_CLASS(cur_fun, Lexer::token) == _CLASS::CONST_CLASS) {
				if (!(0 <= Lexer::num && Lexer::num < dim)) {
					Error::addError(Lexer::line, ERROR_DIM_ARRAY);
				}
			}
		}
		/*******************************检查越界错误*************************************/
		string index_name;
		enum kinds index_type;
		proc_expr(index_name, index_type);//表达式
		if (index_type != kinds::INTSY && index_type != kinds::CHARSY) {
			Error::addError(Lexer::line, ERROR_TYP_ARRAY_INDEX);//只允许INTSY、CHARSY作为索引
		}
		if (Lexer::symbol != RBRACSY) {
			//缺少]，报错
			Error::addError(Lexer::line, MISS_RBRACSY);
		}
		Lexer::getToken();
		if (Lexer::symbol != kinds::ASINSY) {
			//缺少=，报错
			Error::addError(Lexer::line, MISS_ASINSY);
		}
		Lexer::getToken();
		string expr_name;
		enum kinds expr_type;
		proc_expr(expr_name, expr_type);//表达式
		Intermediate_code::push_back(Quaternion("[]=", index_name, expr_name, ID_name));//给数组元素赋值
		if(print_grammar_item) cout <<"赋值语句"<<endl;
		return 0;		
	} else {
		//标识符后面不是=，也不是[，报错
		return 1;
	}
}

//读语句，实现了所有分支的预读入
int Parse::proc_read_stat() {
	if (Lexer::symbol != kinds::SCANF) {
		//scanf错误，报错
		return 1;
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::LPARSY) {
		//(错误，报错
		Error::addError(Lexer::line, MISS_LPARSY);
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::IDSY) {
		//第一个标识符就错了或者没有，报错
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
	while (Lexer::symbol == kinds::COMMASY) {//有逗号说明还有要读的
		Lexer::getToken();
		if (Lexer::symbol != kinds::IDSY) {
			//标识符错了或者没有，报错
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
		//缺少最后的右括号，报错
		Error::addError(Lexer::line, MISS_RPARSY);
	}
	Lexer::getToken();
	if(print_grammar_item) cout << "读语句"<<endl;
	return 0;
}

//写语句，实现了所有分支的预读入
int Parse::proc_writ_stat() {
	if (Lexer::symbol != kinds::PRINTF) {
		//scanf错误，报错
		return 1;
	}
	Lexer::getToken();
	if (Lexer::symbol != kinds::LPARSY) {
		//(错误，报错
		return 1;
	}
	Lexer::getToken();
	if (Lexer::symbol == kinds::STRSY) {
		//现在读到了字符串，后面可能还有逗号，标识符
		Intermediate_code::push_back(Quaternion("~PRINT", "!STRING", StringTable::add(Lexer::token), ""));
		Lexer::getToken();
		if (Lexer::symbol == kinds::COMMASY) {
			//有读到了逗号，期望后面有表达式
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
			//达到了期望，即print字符串和表达式，并且有了预读入
		}
	} else {//只有表达式
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
		//缺少最后的右括号，报错
		Error::addError(Lexer::line, MISS_RPARSY);
	}
	Intermediate_code::push_back(Quaternion("~PRINT", "!STRING", "string_0", ""));
	Lexer::getToken();
	if(print_grammar_item) cout <<"写语句"<<endl;
	return 0;
}

//返回语句，实现了所有分支的预读入
int Parse::proc_retu_stat() {//这里其实应该回传返回类型，并在函数中判断有无返回语句、返回类型是否正确
	if (Lexer::symbol != kinds::RETURN) {
		//首单词不是return，报错
		return 1;
	}
	Lexer::getToken();
	if (Lexer::symbol == kinds::SEMISY) {
		//return; 语句，相当于有了预读入
		Intermediate_code::push_back(Quaternion("~RETURN", "~NONE", "", ""));
		if(print_grammar_item) cout <<"return语句（无返回值）"<<endl;
		return 0;
	}
	if (Lexer::symbol != kinds::LPARSY) {
		//(错误，报错
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
		//)错误，报错
		Error::addError(Lexer::line, MISS_RPARSY);
	}
	Lexer::getToken();
	if(print_grammar_item) cout<<"return语句（有返回值）"<<endl;
	return 0;
}

//新标签
string Parse::new_lable() {
	static int lable_num = 0;
	return "lable_" + int2str(lable_num++);
}

//新临时变量
string Parse::new_val(const kinds type, const int value) {
	static int val_num = 0;
	string name = int2str(val_num++) + "_t";//这样取名字避免了和临时变量重名
	Table::val_enter_t(name, type, value);
	return name;
}
