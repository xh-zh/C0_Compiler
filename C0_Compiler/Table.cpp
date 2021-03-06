#include "StdAfx.h"
#include "Table.h"

vector<TableEntity> Table::table;
int Table::addr = 0;
string Table::cur_parent = "top";
int Table::cur_level_pointer = 0;

Table::Table()
{
}

Table::~Table()
{
}

bool Table::in_this_level(const string name) {
	for(int i = cur_level_pointer==0?0:cur_level_pointer-1; i < table.size(); i++) {
		//从当前函数所在位置开始搜索
		if (table[i].name == name) {
			return true;
		}
	}
	return false;
}

int Table::con_enter(const string name, const enum kinds type, const int value) {
	if (in_this_level(name)) {//当前层有同名标识符
		return 1;
	}
	table.push_back(TableEntity(name, addr, _CLASS::CONST_CLASS, type, value, 0, cur_parent));
	addr += 4;
	return 0;
}

int Table::val_enter(const string name, const enum kinds type) {
	return val_enter(name, type, 0);//变量初值设为0
}

int Table::val_enter(const string name, const enum kinds type, const int value) {
	if (in_this_level(name)) {//当前层有同名标识符
		return 1;
	}
	table.push_back(TableEntity(name, addr, _CLASS::VAL_CLASS, type, value, 0, cur_parent));
	addr += 4;
	return 0;
}

int Table::val_enter_t(const string name, const enum kinds type, const int value){
	if (in_this_level(name)) {//当前层有同名标识符
		return 1;
	}
	table.push_back(TableEntity(name, addr, _CLASS::VAL_CLASS, type, value, -1, cur_parent));
	addr += 4;
	return 0;
}

int Table::array_enter(const string name, const enum kinds type, const int dim) {
	if (in_this_level(name)) {//当前层有同名标识符
		return 1;
	}
	table.push_back(TableEntity(name, addr, _CLASS::ARRAY_CLASS, type, 0, dim, cur_parent));
	addr += 4 * dim;
	return 0;
}

int Table::para_enter(const string name, const kinds type, const int para_dim_cut) {
	if (in_this_level(name)) {//当前层有同名标识符
		return 1;
	}
	table.push_back(TableEntity(name, addr, _CLASS::PARA_CLASS, type, 0, para_dim_cut, cur_parent));
	//if (para_dim_cut >= 4) addr += 4;//少于四个参数就不分配栈空间了，从0开始计数
	//那样会出问题
	addr += 4;
	return 0;
}

int Table::func_enter(const string name, const kinds type) {
	if (in_this_level(name)) {//当前层有同名标识符
		return 1;
	}
	const enum _CLASS kind = type == kinds::VOID?_CLASS::FUN_VOID_CLASS:_CLASS::FUN_IOC_CLASS;
	table.push_back(TableEntity(name, 0, kind, type, 0, 0, cur_parent));//value(size)、dim暂时设为0
	addr = 4 + 4 * 8;//0保存$ra，其余8个word保存$s0-$s7
	cur_parent = name;//函数声明后，马上改父函数名，声明结束时记得要改回去
	cur_level_pointer = table.size();//level_pointer改为当前函数u所在位置++，声明结束时要改回去
	return 0;
}

int Table::func_fill_back_value(const string name) {
	for (int i=0; i<table.size(); i++)
		if (table[i].parent == "top" && table[i].name == name) {
			table[i].value = addr;
		}
	cur_parent = "top";
	cur_level_pointer = 0;
	return 0;
}

int Table::func_fill_back_dim(const string name, const int dim) {
	for (int i=0; i<table.size(); i++)
		if (table[i].parent == "top" && table[i].name == name) {
			table[i].dim = dim;
		}
	return 0;
}

bool Table::contain(const string fun_name, const string name) {
	for (int i=0; i<table.size(); i++) {
		if (fun_name == "top") break;
		if (table[i].parent == fun_name && table[i].name == name)
			return true;//在函数fun_name数据区里找到了变量name
	}
	for (int i=0; i<table.size(); i++) {
		if (table[i].parent == "top" && table[i].name == name)
			return true;//没在函数数据区中找到，但在全局数据区找到了
		if (table[i].parent != "top")
			break;
	}
	return false;//没找到
}

bool Table::is_void_func(const string fun_name) {
	return get_CLASS("top", fun_name) == _CLASS::FUN_VOID_CLASS;
}

bool Table::contain_func(const string name) {
	for (int i=0; i<table.size();i++) {
		if (table[i].parent == "top" && table[i].name == name && 
			(table[i]._class == _CLASS::FUN_IOC_CLASS || 
			table[i]._class == _CLASS::FUN_VOID_CLASS)) {
			return true;
		}
	}
	return false;
}

TableEntity Table::get_func(const string name) {
	if (!contain_func(name)) {
		return TableEntity();
	}
	for (int i=0; i<table.size();i++) {
		if (table[i].parent == "top" &&
			table[i].name == name && 
			(table[i]._class == _CLASS::FUN_IOC_CLASS || 
			table[i]._class == _CLASS::FUN_VOID_CLASS)) {
			return table[i];
		}
	}
	return TableEntity();
}

/**
 *	@param	fun_name, name
 *	@return	_CLASS of name
 */
_CLASS Table::get_CLASS(const string fun_name, const string name) {
	for (int i=0; i<table.size(); i++) {//先在本层找
		if (fun_name == "top") break;
		if (table[i].parent == fun_name && table[i].name == name) {
			return table[i]._class;
		}
	}
	for (int i=0; i<table.size(); i++) {//在全局区找
		if (table[i].parent == "top" && table[i].name == name)
			return table[i]._class;
	}
	return _CLASS::NONE_CLASS;
}

/**
 *	@param	fun_name, name
 *	@return	type of name
 */
kinds Table::get_type(const string fun_name, const string name) {
	for (int i=0; i<table.size(); i++) {
		if (fun_name == "top") break;
		if (table[i].parent == fun_name && table[i].name == name) {
			return table[i].type;
		}
	}
	for (int i=0; i<table.size(); i++) {//在全局区找
		if (table[i].parent == "top" && table[i].name == name)
			return table[i].type;
	}
	return kinds::null;
}

int Table::get_value(const string fun_name, const string name) {
	for (int i=0; i<table.size(); i++) {
		if (fun_name == "top") break;
		if (table[i].parent == fun_name && table[i].name == name) {
			return table[i].value;
		}
	}
	for (int i=0; i<table.size(); i++) {//在全局区找
		if (table[i].parent == "top" && table[i].name == name)
			return table[i].value;
	}
	return 0;
}

int Table::get_dim(const string fun_name, const string name) {
	for (int i=0; i<table.size(); i++) {
		if (fun_name == "top") break;
		if (table[i].parent == fun_name && table[i].name == name) {
			return table[i].dim;
		}
	}
	for (int i=0; i<table.size(); i++) {//在全局区找
		if (table[i].parent == "top" && table[i].name == name)
			return table[i].dim;
	}
	return 0;
}

int Table::get_addr(const string fun_name, const string name) {
	for (int i=0; i<table.size(); i++) {
		if (fun_name == "top") break;
		if (table[i].parent == fun_name && table[i].name == name)
			return table[i].addr;
	}
	for (int i=0; i<table.size(); i++) {//在全局区找
		if (table[i].parent == "top" && table[i].name == name)
			return table[i].addr;
	}
	return 0;
}

bool Table::is_global(const string fun_name, const string name) {
	for (int i=0; i<table.size(); i++) {
		if (fun_name == "top") break;
		if (table[i].parent == fun_name && table[i].name == name)
			return false;//在函数fun_name数据区里找到了变量name
	}
	for (int i=0; i<table.size(); i++) {
		if (table[i].parent == "top" && table[i].name == name)
			return true;//没在函数数据区中找到，但在全局数据区找到了
		if (table[i].parent != "top")
			break;
	}
	return false;//这其实是没找到name变量，正常情况下不会执行此分支
}

int Table::get_fun_size(const string fun_name) {
	return get_value("top", fun_name);
}

string Table::get_parent(const string fun_name, const string name) {
	for (int i=0; i<table.size(); i++) {
		if (fun_name == "top") break;
		if (table[i].parent == fun_name && table[i].name == name) {
			return fun_name;
		}
	}
	for (int i=0; i<table.size(); i++) {//在全局区找
		if (table[i].parent == "top" && table[i].name == name)
			return "top";
	}
	return "";
}

vector<TableEntity> Table::get_para(const string name) {
	vector<TableEntity> para;
	for (int i=0; i < table.size(); i++) {
		if (table[i].name == name && (table[i]._class == FUN_IOC_CLASS || table[i]._class == FUN_VOID_CLASS)) {
			for (int j=i+1; j<=i+table[i].dim; j++)
				para.push_back(TableEntity(table[j]));
		}
	}
	return para;

}

void Table::print(char *path) {
	ofstream out(path);
	for(vector<TableEntity>::iterator iter = table.begin(); iter != table.end(); ++iter) {
		out << iter->name << "\t" << getSymbol(iter->type) << "\t" << int2str(iter->value) << "\taddr:" << int2str(iter->addr) << endl;;
	}
	out.close();
}

void Table::add_addr(const string fun_name, const string name, const string addr) {
	for (int i=0; i<table.size(); i++) {
		if (fun_name == "top") break;
		if (table[i].parent == fun_name && table[i].name == name) {
			for (vector<string>::iterator iter=table[i].address_descriptor.begin(); iter!=table[i].address_descriptor.end(); ++iter)
				if (*iter == addr) {
					return;
				}
			table[i].address_descriptor.push_back(addr);
			return;//在局部区找到了，就可以返回了
		}
	}
	for (int i=0; i<table.size(); i++) {//在全局区找
		if (table[i].parent == "top" && table[i].name == name) {
			for (vector<string>::iterator iter=table[i].address_descriptor.begin(); iter!=table[i].address_descriptor.end(); ++iter)
				if (*iter == addr) {
					return;
				}
			table[i].address_descriptor.push_back(addr);
			return;
		}
	}
}

void Table::del_addr(const string fun_name, const string name, const string addr) {
	for (int i=0; i<table.size(); i++) {
		if (fun_name == "top") break;
		if (table[i].parent == fun_name && table[i].name == name) {
			for (vector<string>::iterator iter = table[i].address_descriptor.begin(); iter != table[i].address_descriptor.end(); ++iter) {
				if (*iter == addr) {
					table[i].address_descriptor.erase(iter);
					return;
				}
			}
			return;//在局部区找到了，不管删不删除，都要返回
		}
	}
	for (int i=0; i<table.size(); i++) {//在全局区找
		if (table[i].parent == "top" && table[i].name == name) {
			for (vector<string>::iterator iter = table[i].address_descriptor.begin(); iter != table[i].address_descriptor.end(); ++iter) {
				if (*iter == addr) {
					table[i].address_descriptor.erase(iter);
					return;
				}
			}
			return;//找到并操作完成就可以返回了
		}
	}
}

bool Table::have_addr(const string fun_name, const string name, const string addr) {
	for (int i=0; i<table.size(); i++) {
		if (fun_name == "top") break;
		if (table[i].parent == fun_name && table[i].name == name) {
			for (vector<string>::iterator iter = table[i].address_descriptor.begin(); iter != table[i].address_descriptor.end(); ++iter) {
				if (*iter == addr) {
					return true;
				}
			}
			return false;
		}
	}
	for (int i=0; i<table.size(); i++) {//在全局区找
		if (table[i].parent == "top" && table[i].name == name) {
			for (vector<string>::iterator iter = table[i].address_descriptor.begin(); iter != table[i].address_descriptor.end(); ++iter) {
				if (*iter == addr) {
					return true;
				}
			}
			return false;
		}
	}
	return false;
}

void Table::clear_addr(const string fun_name, const string name) {
	for (int i=0; i<table.size(); i++) {
		if (fun_name == "top") break;
		if (table[i].parent == fun_name && table[i].name == name) {
			table[i].address_descriptor.clear();
			return;
		}
	}
	for (int i=0; i<table.size(); i++) {//在全局区找
		if (table[i].parent == "top" && table[i].name == name) {
			table[i].address_descriptor.clear();
			return;
		}
	}
}

void Table::add_stack_addr(const string fun_name, const string name) {
	for (int i=0; i<table.size(); i++) {
		if (fun_name == "top") break;
		if (table[i].parent == fun_name && table[i].name == name) {
			table[i].address_descriptor.push_back(int2str(table[i].addr));
			return;
		}
	}
	for (int i=0; i<table.size(); i++) {//在全局区找
		if (table[i].parent == "top" && table[i].name == name) {
			table[i].address_descriptor.push_back(int2str(table[i].addr));
			return;
		}
	}
}

bool Table::only_in_stack(const string fun_name, const string name) {
	for (int i=0; i<table.size(); i++) {
		if (fun_name == "top") break;
		if (table[i].parent == fun_name && table[i].name == name) {
			if (table[i].address_descriptor.size() == 1 && Translator::isnum(table[i].address_descriptor[0])) {
				return true;
			}
			return false;
		}
	}
	for (int i=0; i<table.size(); i++) {//在全局区找
		if (table[i].parent == "top" && table[i].name == name) {
			if (table[i].address_descriptor.size() == 1 && Translator::isnum(table[i].address_descriptor[0])) {
				return true;
			}
			return false;
		}
	}
	return false;
}

bool Table::only_here(const string fun_name, const string name, const string reg_name) {
	for (int i=0; i<table.size(); i++) {
		if (fun_name == "top") break;
		if (table[i].parent == fun_name && table[i].name == name) {
			if (table[i].address_descriptor.size() == 1 && table[i].address_descriptor[0] == reg_name) {
				return true;
			}
			return false;
		}
	}
	for (int i=0; i<table.size(); i++) {//在全局区找
		if (table[i].parent == "top" && table[i].name == name) {
			if (table[i].address_descriptor.size() == 1 && table[i].address_descriptor[0] == reg_name) {
				return true;
			}
			return false;
		}
	}
	return false;
}

bool Table::in_stack(const string fun_name, const string name) {
	for (int i=0; i<table.size(); i++) {
		if (fun_name == "top") break;
		if (table[i].parent == fun_name && table[i].name == name) {
			for (vector<string>::iterator iter = table[i].address_descriptor.begin(); iter!=table[i].address_descriptor.end(); ++iter) {
				if (Translator::isnum(*iter)) {
					return true;
				}
			}
			return false;
		}
	}
	for (int i=0; i<table.size(); i++) {//在全局区找
		if (table[i].parent == "top" && table[i].name == name) {
			for (vector<string>::iterator iter = table[i].address_descriptor.begin(); iter!=table[i].address_descriptor.end(); ++iter) {
				if (Translator::isnum(*iter)) {
					return true;
				}
			}
			return false;
		}
	}
	return false;
}

string Table::get_reg(const string fun_name, const string name) {
	for (int i=0; i<table.size(); i++) {
		if (fun_name == "top") break;
		if (table[i].parent == fun_name && table[i].name == name) {
			for (vector<string>::iterator iter = table[i].address_descriptor.begin(); iter != table[i].address_descriptor.end(); ++iter) {
				if (!Translator::isnum(*iter)) {
					return *iter;
				}
			}
			return int2str(table[i].addr);//按照约定，只有在寄存器中的变量才会被调用此方法，因此不会执行这个分支
		}
	}
	for (int i=0; i<table.size(); i++) {//在全局区找
		if (table[i].parent == "top" && table[i].name == name) {
			for (vector<string>::iterator iter = table[i].address_descriptor.begin(); iter != table[i].address_descriptor.end(); ++iter) {
				if (!Translator::isnum(*iter)) {
					return *iter;
				}
			}
			return int2str(table[i].addr);//按照约定，只有在寄存器中的变量才会被调用此方法，因此不会执行这个分支
		}
	}
	return "";//按照约定，只有在寄存器中的变量才会被调用此方法，因此不会执行这个分支
}

vector<string> Table::get_address_descriptor(const string fun_name, const string name) {
	for (int i=0; i<table.size(); i++) {
		if (fun_name == "top") break;
		if (table[i].parent == fun_name && table[i].name == name) {
			return table[i].address_descriptor;
		}
	}
	for (int i=0; i<table.size(); i++) {//在全局区找
		if (table[i].parent == "top" && table[i].name == name) {
			return table[i].address_descriptor;
		}
	}
	vector<string> v;
	return v;
}

bool Table::set_type(const string name, const enum kinds type) {
	for	(int i = cur_level_pointer; i < table.size(); i++)
		if (table[i].name == name) {
			table[i].type = type;
			return true;
		}
	return false;
}


