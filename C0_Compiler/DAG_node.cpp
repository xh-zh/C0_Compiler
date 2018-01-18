#include "StdAfx.h"
#include "DAG_node.h"


DAG_node::DAG_node(const string op, DAG_node* l, DAG_node* r, const string val, const int cnt) {
	this->op = op;
	this->l = l;
	this->r = r;
	this->cnt = cnt;
	if (val != "") add_val(val);
	if (l == nullptr) child_cnt = 0;
	else if (r == nullptr) {
		child_cnt = 1;
		l->parents.push_back(this);
	}
	else {
		child_cnt = 2;
		l->parents.push_back(this);
		r->parents.push_back(this);
	}
}

DAG_node::DAG_node() {
}

DAG_node::~DAG_node()
{
}

void DAG_node::add_val(const string val) {
	vals.push_back(val);
}

void DAG_node::del_val(const string val) {
	if (vals.size() <= 1) return;//防止生成代码时没有标识符用
	for (vector<string>::iterator iter = vals.begin(); iter!=vals.end(); ++iter)
		if (*iter == val) {
			vals.erase(iter);
			break;
		}
}
