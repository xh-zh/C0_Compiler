#pragma once
class DAG_node
{
public:
	int cnt;
	string op;
	int child_cnt;//Ϊ1��ֻ��һ���ӽڵ㣬Ϊ0��ΪҶ�ڵ�
	vector<DAG_node*> parents;//�ڵ�����в�ֹһ�����ڵ�
	DAG_node *l;
	DAG_node *r;
	vector<string> vals;//��Ŵ˽ڵ����ı���
	DAG_node(string op, DAG_node *l, DAG_node *r, string val, int cnt);
	DAG_node();
	~DAG_node();
	void add_val(string val);
	void del_val(const string val);
};

