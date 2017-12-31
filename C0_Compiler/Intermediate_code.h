#pragma once
#include "Quaternion.h"
#include "DAG_node.h"
#include "map"

typedef struct
{
	int begin;
	int end;
}basic_block;
class Intermediate_code
{
private:
	static void divd_blk();//划分基本块
	static int in_DAG(vector<DAG_node*> nodes, string op, DAG_node *l, DAG_node *r);//DAG图中是否存在这样一个节点，是的话返回索引，否的话返回-1，这个是查找符号节点用的
	static bool all_in_que(const vector<bool> in_que, const int size);
	static bool	all_parents_in_que(const vector<bool> in_que, const vector<DAG_node*> parents, map<DAG_node*, int> index_map);
	static vector<Quaternion> generate_DAG(int begin, int end);//生成DAG图
	static vector<Quaternion> generate(map<string, int> node_list, vector<DAG_node*> nodes, int node_cnt);//从DAG图中生成优化后的中间代码
public:
	static vector<basic_block> blocks;
	static vector<Quaternion> code;
	Intermediate_code();
	~Intermediate_code();
	static void push_back(Quaternion q);
	static void print(char *path);
	static void lable_combine();//合并lable，删除无用跳转
	static void print_blk(char *path);
	static void DAG_optimize();
	static void peephole_optimize();
	static vector<Quaternion> repeated_assignment_optimize(vector<Quaternion> source_code);//删除相邻的重复赋值（result相同）
	static void del_nouse_val();//删除从未使用的变量
};

