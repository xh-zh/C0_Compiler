#pragma once
#include "Quaternion.h"
#include "DAG_node.h"

typedef struct
{
	int begin;
	int end;
}basic_block;
class Intermediate_code
{
private:
	static vector<basic_block> blocks;
public:
	static vector<Quaternion> code;
	Intermediate_code();
	~Intermediate_code();
	static void push_back(Quaternion q);
	static void print(char *path);
	static void lable_combine();//合并lable，删除无用跳转
	static void divd_blk();//划分基本块
	static void generate_DAG(int begin, int end);//生成DAG图
	static int in_DAG(vector<DAG_node> nodes, string op, DAG_node *l, DAG_node *r);//DAG图中是否存在这样一个节点，是的话返回索引，否的话返回-1，这个是查找符号节点用的
	static int in_DAG(vector<DAG_node> nodes, string op);//同上，只不过这个是查找左右节点用的
};

