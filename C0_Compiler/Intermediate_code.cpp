#include "StdAfx.h"
#include "Intermediate_code.h"
#include "DAG_node.h"
#include <queue>
#include <stack>

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
	out.close();
}

void Intermediate_code::lable_combine() {
	//lable合并
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
	//消除无效跳转
	for (int i = 0; i < code.size() - 1; i++) {
		if ((code[i].op == "BZ" || code[i].op == "BNZ") &&
			code[i + 1].op == "LABLE") {
			if (code[i].para2 == code[i + 1].para1) {
				code[i].op = "NOP";
			}
		}
		else if (code[i].op == "GOTO" && code[i + 1].op == "LABLE") {
			if (code[i].para1 == code[i + 1].para1) {
				code[i].op = "NOP";
			}
		}
	}
	//删除死标签
	for (int i=0; i<code.size(); i++) {
		if (code[i].op == "LABLE") {
			bool flag = true;
			for (int j=0; j <code.size(); j++) {
				if ((code[j].op == "BZ" || code[j].op == "BNZ") && 
					code[j].para2 == code[i].para1) {
					flag = false;
					break;
				} 
				if (code[j].op == "GOTO" && code[j].para1 == code[i].para1) {
					flag = false;
					break;
				}
			}
			if (flag) {
				code[i].op = "NOP";
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
			code[i].op == "=" || code[i].op == "!=" ||
			code[i].op == "=[]" || code[i].op == "[]=") {
			const int begin = i;
			do {
				end = i++;
			}
			while (code[i].op == "+" || code[i].op == "-" || code[i].op == "*" ||
				code[i].op == "/" || code[i].op == "<" || code[i].op == "<=" ||
				code[i].op == ">" || code[i].op == ">=" || code[i].op == "==" ||
				code[i].op == "=" || code[i].op == "!=" ||
				code[i].op == "=[]" || code[i].op == "[]=");
			basic_block bb;
			bb.begin = begin;
			bb.end = end;
			blocks.push_back(bb);
		}
	}
}

vector<Quaternion> Intermediate_code::generate_DAG(const int begin, const int end) {
	int node_cnt = 0;//节点编号从0开始计
	map<string, int> node_list;//由变量名找到节点号
	vector<DAG_node*> nodes;//由节点号找到节点
	for (int i=begin; i<=end; i++) {
		//左右节点都在节点表里找，符号节点在DAG图中找
		const Quaternion q = code[i];
		DAG_node* lnode;
		DAG_node* rnode;
		//左节点
		if (node_list.find(q.para1) == node_list.end()) {//左节点不在节点表里，即不在DAG图中
			//这里应该先检查一下是否是整数、字符，整数、字符的话不需要加0
			const int lnode_cnt = node_cnt++;
			if (Translator::isnum(q.para1) || q.para1[0] == '$')
				lnode = new DAG_node(q.para1, nullptr, nullptr, q.para1, lnode_cnt);
			else
				lnode = new DAG_node(q.para1 + "0", nullptr, nullptr, q.para1, lnode_cnt);
			node_list[q.para1] = lnode_cnt;//节点表中是不用加0的
			nodes.push_back(lnode);
		} else {//左节点在节点表里，即在DAG图中
			lnode = nodes[node_list.find(q.para1)->second];//lnode指向那个node
		}
		//判断指令是否是单目运算符
		if (q.op == "=") {
			const int index = in_DAG(nodes, q.op, lnode, nullptr);
			if (-1 != index) {//存在这样的节点
				if (node_list.count(q.result) == 1) {//这个节点已经存在于节点表
					nodes[node_list[q.result]]->del_val(q.result);//删除原节点中对此变量的记录
				}
				node_list[q.result] = index;//设置当前变量对应的节点
				nodes[index]->add_val(q.result);//在当前节点记录变量
			} else {//不存在这样的节点，那就新建一个
				DAG_node *node = new DAG_node(q.op, lnode, nullptr, q.result, node_cnt);//如果是赋值，val就是被赋值符号
				node_list[q.result] = node_cnt++;
				nodes.push_back(node);
			}
			continue;//单目运算符处理结束
		}
		//右节点
		if (node_list.find(q.para2) == node_list.end()) {//右部不在节点表里，即不在DAG图中
			const int rnode_cnt = node_cnt++;
			if (Translator::isnum(q.para2) || q.para2[0] == '$')
				rnode = new DAG_node(q.para2, nullptr, nullptr, q.para2, rnode_cnt);
			else
				rnode = new DAG_node(q.para2 + "0", nullptr, nullptr, q.para2, rnode_cnt);
			node_list[q.para2] = rnode_cnt;//节点表中是不用加0的
			nodes.push_back(rnode);
		} else {//等式右部在节点表里，即在DAG图中
			rnode = nodes[node_list.find(q.para2)->second];//rnode指向那个node
		}
		//符号节点
		const int index = in_DAG(nodes, q.op, lnode, rnode);
		if (-1 != index) {//找到了这样的节点
			if (q.op != "[]=" && node_list.count(q.result) == 1) {//这个节点不是给数组元素赋值而且已经存在于节点表
				nodes[node_list[q.result]]->del_val(q.result);//删除原节点中对此变量的记录
			}
			node_list[q.result] = index;//设置当前变量对应的节点
			nodes[index]->add_val(q.result);//在当前节点记录变量
		} else {//没找到，那就新建一个
			DAG_node *node = new DAG_node(q.op, lnode, rnode, q.result, node_cnt);
			node_list[q.result] = node_cnt++;
			nodes.push_back(node);
		}
	}
	return generate(node_list, nodes, node_cnt);
}

int Intermediate_code::in_DAG(vector<DAG_node*> nodes, const string op, DAG_node* l, DAG_node* r) {
	for(int i=0; i<nodes.size(); i++)
		if (nodes[i]->op == op && nodes[i]->l == l && nodes[i]->r == r) {
			return i;
		}
	return -1;
}

vector<Quaternion> Intermediate_code::generate(map<string, int> node_list, vector<DAG_node*> nodes, int node_cnt) {
	stack<int> node_stack;
	vector<bool> in_que(nodes.size());
	map<DAG_node*, int> index_map;
	for (int i=0; i<nodes.size(); i++) {
		index_map[nodes[i]] = i;//初始化index_map
		in_que[i] = false;//初始化in_que数组
	}
		
	while (!all_in_que(in_que, nodes.size())) {//因为对节点的一次遍历不能保证所有的节点都被加入队列，因此要循环多次，直到所有节点都被加入队列
		for (int i=0; i<nodes.size(); i++) {
			if (!in_que[i] && all_parents_in_que(in_que, nodes[i]->parents, index_map)) {//选取一个尚未进入队列，但其所有父节点均已进入队列或没有父节点的中间节点
				node_stack.push(i);//入队
				in_que[i] = true;
				DAG_node *cur_node = nodes[i]->l;
				while (cur_node != nullptr ) {//沿着左子节点向下走
					int cur_index = index_map[cur_node];
					if (!in_que[cur_index] && all_parents_in_que(in_que, cur_node->parents, index_map)) {
						node_stack.push(cur_index);
						in_que[cur_index] = true;
						cur_node = cur_node->l;
					} else 
						break;
				}
			}
		}
	}
	vector<Quaternion> new_code;
	while (!node_stack.empty()) {
		DAG_node *cur_node = nodes[node_stack.top()];
		switch (cur_node->child_cnt) {
		case 0:
			break;
		case 1://=
			new_code.push_back(Quaternion("=", cur_node->l->vals[0], "", cur_node->vals[0]));
			break;
		case 2:
			for (vector<string>::iterator iter = cur_node->vals.begin(); iter != cur_node->vals.end(); ++iter)
				new_code.push_back(Quaternion(cur_node->op, cur_node->l->vals[0], cur_node->r->vals[0], *iter));
			break;
		default:
			cout << "Error in Intermediate_code::generate" << endl;
		}
		node_stack.pop();
	}
	for (int i=0; i<nodes.size(); i++)
		delete nodes[i];
	return new_code;
}

void Intermediate_code::print_blk(char* path) {
	for (vector<basic_block>::iterator iter = blocks.end()-1; iter >= blocks.begin(); --iter) {
		code.insert(code.begin()+iter->end, Quaternion("===== BLOCK", "   END  =====", "", ""));
		code.insert(code.begin()+iter->begin, Quaternion("===== BLOCK", "  BEGIN =====", "", ""));
	}
	ofstream out(path);
	for (vector<Quaternion>::iterator iter = code.begin(); iter != code.end(); ++iter) {
		if (iter->op == "===== BLOCK")
			out << iter->op << iter->para1 << endl;
		else if (iter->op != "NOP")//不打印删除后的中间代码
			out << iter->op << "\t" << iter->para1 << "\t" << iter->para2 << "\t" << iter->result << endl;
	}
	out.close();
}

void Intermediate_code::DAG_optimize() {
	divd_blk();
	for	(vector<basic_block>::iterator iter = blocks.begin(); iter != blocks.end(); ++iter) {
		vector<Quaternion> new_code = generate_DAG(iter->begin, iter->end);
		const int new_code_size = new_code.size();
		for (int i=iter->begin; i <= iter->end; i++) {
			if (i < new_code_size) {
				code[i] = new_code[i];
			} else {
				code[i].op = "NOP";
			}
		}
	}
}

bool Intermediate_code::all_in_que(const vector<bool> in_que, const int size) {
	for (int i=0; i<size; i++)
		if (!in_que[i]) 
			return false;
	return true;
}

bool Intermediate_code::all_parents_in_que(const vector<bool> in_que, const vector<DAG_node*> parents, map<DAG_node*, int> index_map) {
	if (parents.empty()) return true;
	for (int i = 0; i < parents.size(); i++)
		if (!in_que[index_map[parents[i]]]) return false;
	return true;
}