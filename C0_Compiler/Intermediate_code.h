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
	static void lable_combine();//�ϲ�lable��ɾ��������ת
	static void divd_blk();//���ֻ�����
	static void generate_DAG(int begin, int end);//����DAGͼ
	static int in_DAG(vector<DAG_node> nodes, string op, DAG_node *l, DAG_node *r);//DAGͼ���Ƿ��������һ���ڵ㣬�ǵĻ�������������Ļ�����-1������ǲ��ҷ��Žڵ��õ�
	static int in_DAG(vector<DAG_node> nodes, string op);//ͬ�ϣ�ֻ��������ǲ������ҽڵ��õ�
};

