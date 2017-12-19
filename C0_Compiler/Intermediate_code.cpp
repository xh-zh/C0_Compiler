#include "StdAfx.h"
#include "Intermediate_code.h"
#include "map"
#include "DAG_node.h"

vector<Quaternion> Intermediate_code::code;
vector<basic_block> Intermediate_code::blocks;

Intermediate_code::Intermediate_code()
{
}

Intermediate_code::~Intermediate_code()
{
}

void Intermediate_code::push_back(const Quaternion q) {
	code.push_back(q);
}

void Intermediate_code::print(char* path) {
	ofstream out(path);
	for (vector<Quaternion>::iterator iter = code.begin(); iter != code.end(); ++iter) {
		if (iter->op != "NOP")//不打印删除后的中间代码
			out << iter->op << "\t" << iter->para1 << "\t" << iter->para2 << "\t" << iter->result << endl;
	}
}

void Intermediate_code::lable_combine() {
	for (int i = 0; i < code.size() - 1; i++) {
		if (code[i].op == "LABLE") {
			if (code[i + 1].op == "LABLE") { //两个lable紧挨着
				const string org_lable = code[i + 1].para1;
				const string lat_lable = code[i].para1;
				code[i + 1].op = "NOP";//删掉后面的lable
				for (int j = 0; j < code.size(); j++) { //替换之前的lable
					if ((code[j].op == "BZ" || code[j].op == "BNZ") &&
						(code[j].para2 == org_lable)) {
						code[j].para2 = lat_lable;
					}
					else if (code[j].op == "GOTO" && code[j].para1 == org_lable) {
						code[j].para1 = lat_lable;
					}
				}
			}
		}
	}
	for (int i = 0; i < code.size() - 1; i++) {
		if ((code[i].op == "BZ" || code[i].op == "BNZ") &&
			code[i + 1].op == "LABLE") {
			if (code[i].para2 == code[i + 1].para1) {
				code[i].op = "NOP";
				code[i + 1].op = "NOP";
			}
		}
		else if (code[i].op == "GOTO" && code[i + 1].op == "LABLE") {
			if (code[i].para1 == code[i + 1].para1) {
				code[i].op = "NOP";
				code[i + 1].op = "NOP";
			}
		}
	}
}

void Intermediate_code::divd_blk() {
	int end;
	for (int i = 0; i < code.size(); i++) {
		if (code[i].op == "+" || code[i].op == "-" || code[i].op == "*" ||
			code[i].op == "/" || code[i].op == "<" || code[i].op == "<=" ||
			code[i].op == ">" || code[i].op == ">=" || code[i].op == "==" ||
			code[i].op == "=" || code[i].op == "!=" || code[i].op == "PRINT") {
			const int begin = i;
			do {
				end = i++;
			}
			while (code[i].op == "+" || code[i].op == "-" || code[i].op == "*" ||
				code[i].op == "/" || code[i].op == "<" || code[i].op == "<=" ||
				code[i].op == ">" || code[i].op == ">=" || code[i].op == "==" ||
				code[i].op == "=" || code[i].op == "!=" || code[i].op == "PRINT");
			basic_block bb;
			bb.begin = begin;
			bb.end = end;
			blocks.push_back(bb);
		}
	}
}

void Intermediate_code::generate_DAG(const int begin, const int end) {
	int node_cnt = 0;
	map<string, int> node_list;//由变量名找到节点号
	vector<DAG_node> nodes;//由节点号找到节点
	for (int i=begin; i<=end; i++) {
		const Quaternion q = code[i];
		int lnode_cnt, rnode_cnt;
		DAG_node* lnode = nullptr;
		DAG_node* rnode = nullptr;
		//左节点
		if (node_list.find(q.para1) == node_list.end()) {//左节点不在节点表里，即不在DAG图中
			lnode_cnt = node_cnt++;
			lnode = new DAG_node(q.para1 + "0", nullptr, nullptr, "", lnode_cnt);
			node_list[q.para1] = lnode_cnt;//节点表中是不用加0的
			nodes.push_back(*lnode);
		} else {//左节点在节点表里，即在DAG图中
			lnode = &nodes[node_list.find(q.para1)->second];//lnode指向那个node
		}
		//判断指令是否是单目运算符
		if (q.op == "=" || q.op == "PRINT") {
			bool exist = false;
			const int index = in_DAG(nodes, q.op, lnode, nullptr);
			if (-1 != index) {//存在这样的节点
				node_list[q.result] = index;
			} else {//不存在这样的节点，那就新建一个
				DAG_node *node = new DAG_node(q.op, lnode, nullptr, q.result, node_cnt);//如果是赋值，val就是被复制符号；如果是print。val就是""
				node_list[q.result] = node_cnt++;
				nodes.push_back(*node);
			}
			continue;//单目运算符处理结束
		}
		//右节点
		if (node_list.find(q.para2) == node_list.end()) {//右部不在节点表里，即不在DAG图中
			rnode_cnt = node_cnt++;
			rnode = new DAG_node(q.para2 + "0", nullptr, nullptr, "", rnode_cnt);
			node_list[q.para2] = rnode_cnt;//节点表中是不用加0的
			nodes.push_back(*rnode);
		} else {//等式右部在节点表里，即在DAG图中
			rnode = &nodes[node_list.find(q.para2)->second];//rnode指向那个node
		}
		//符号节点
		const int index = in_DAG(nodes, q.op, lnode, rnode);
		if (-1 != index) {//找到了这样的节点
			node_list[q.result] = index;
		} else {//没找到，那就新建一个
			DAG_node *node = new DAG_node(q.op, lnode, rnode, q.result, node_cnt);
			node_list[q.result] = node_cnt++;
			nodes.push_back(*node);
		}
	}
}

int Intermediate_code::in_DAG(vector<DAG_node> nodes, const string op, DAG_node* l, DAG_node* r) {
	for(int i=0; i<nodes.size(); i++)
		if (nodes[i].op == op && nodes[i].l == l && nodes[i].r == r) {
			return i;
		}
	return -1;
}


