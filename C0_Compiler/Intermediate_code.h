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
	static void divd_blk();//���ֻ�����
	static int in_DAG(vector<DAG_node*> nodes, string op, DAG_node *l, DAG_node *r);//DAGͼ���Ƿ��������һ���ڵ㣬�ǵĻ�������������Ļ�����-1������ǲ��ҷ��Žڵ��õ�
	static bool all_in_que(const vector<bool> in_que, const int size);
	static bool	all_parents_in_que(const vector<bool> in_que, const vector<DAG_node*> parents, map<DAG_node*, int> index_map);
	static vector<Quaternion> generate_DAG(int begin, int end);//����DAGͼ
	static vector<Quaternion> generate(map<string, int> node_list, vector<DAG_node*> nodes, int node_cnt);//��DAGͼ�������Ż�����м����
public:
	static vector<basic_block> blocks;
	static vector<Quaternion> code;
	Intermediate_code();
	~Intermediate_code();
	static void push_back(Quaternion q);
	static void print(char *path);
	static void lable_combine();//�ϲ�lable��ɾ��������ת
	static void print_blk(char *path);
	static void DAG_optimize();
	static void peephole_optimize();
	static vector<Quaternion> repeated_assignment_optimize(vector<Quaternion> source_code);//ɾ�����ڵ��ظ���ֵ��result��ͬ��
	static void del_nouse_val();//ɾ����δʹ�õı���
};

