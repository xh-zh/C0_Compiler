#pragma once
class DAG_node
{
public:
	int cnt;
	string op;
	int child_cnt;//为1即只有一个子节点，为0即为叶节点
	vector<DAG_node*> parents;//节点可以有不止一个父节点
	DAG_node *l;
	DAG_node *r;
	vector<string> vals;//存放此节点代表的变量
	DAG_node(string op, DAG_node *l, DAG_node *r, string val, int cnt);
	DAG_node();
	~DAG_node();
	void add_val(string val);
	void del_val(const string val);
};

