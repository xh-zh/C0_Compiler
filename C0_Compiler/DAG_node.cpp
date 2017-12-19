#include "StdAfx.h"
#include "DAG_node.h"


DAG_node::DAG_node(string op, DAG_node* l, DAG_node* r, const string val, const int cnt) {
	this->op = op;
	this->l = l;
	this->r = r;
	this->cnt = cnt;
	if (val != "") add_val(val);
	if (l == nullptr) child_cnt = 0;
	else if (r == nullptr) child_cnt = 1;
	else child_cnt = 2;
}

DAG_node::DAG_node() {
}

DAG_node::~DAG_node()
{
}

void DAG_node::add_val(const string val) {
	vals.push_back(val);
}
