#include "StdAfx.h"
#include "Intermediate_code.h"
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
		if (iter->op != "NOP")//����ӡɾ������м����
			out << iter->op << "\t" << iter->para1 << "\t" << iter->para2 << "\t" << iter->result << endl;
	}
}

void Intermediate_code::lable_combine() {
	for (int i = 0; i < code.size() - 1; i++) {
		if (code[i].op == "LABLE") {
			if (code[i + 1].op == "LABLE") { //����lable������
				const string org_lable = code[i + 1].para1;
				const string lat_lable = code[i].para1;
				code[i + 1].op = "NOP";//ɾ�������lable
				for (int j = 0; j < code.size(); j++) { //�滻֮ǰ��lable
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
			code[i].op == "=" || code[i].op == "!=" || code[i].op == "PRINT" ||
			code[i].op == "=[]" || code[i].op == "[]=") {
			const int begin = i;
			do {
				end = i++;
			}
			while (code[i].op == "+" || code[i].op == "-" || code[i].op == "*" ||
				code[i].op == "/" || code[i].op == "<" || code[i].op == "<=" ||
				code[i].op == ">" || code[i].op == ">=" || code[i].op == "==" ||
				code[i].op == "=" || code[i].op == "!=" || code[i].op == "PRINT" ||
				code[i].op == "=[]" || code[i].op == "[]=");
			basic_block bb;
			bb.begin = begin;
			bb.end = end;
			blocks.push_back(bb);
		}
	}
}

void Intermediate_code::generate_DAG(const int begin, const int end) {
	int node_cnt = 0;
	map<string, int> node_list;//�ɱ������ҵ��ڵ��
	vector<DAG_node> nodes;//�ɽڵ���ҵ��ڵ�
	for (int i=begin; i<=end; i++) {
		//���ҽڵ㶼�ڽڵ�����ң����Žڵ���DAGͼ����
		const Quaternion q = code[i];
		DAG_node* lnode;
		DAG_node* rnode;
		//��ڵ�
		if (node_list.find(q.para1) == node_list.end()) {//��ڵ㲻�ڽڵ���������DAGͼ��
			//����Ӧ���ȼ��һ���Ƿ����������ַ����������ַ��Ļ�����Ҫ��0
			const int lnode_cnt = node_cnt++;
			if (Translator::isnum(q.para1) || q.para1[0] == '$')
				lnode = new DAG_node(q.para1, nullptr, nullptr, "", lnode_cnt);
			else
				lnode = new DAG_node(q.para1 + "0", nullptr, nullptr, "", lnode_cnt);
			node_list[q.para1] = lnode_cnt;//�ڵ�����ǲ��ü�0��
			nodes.push_back(*lnode);
		} else {//��ڵ��ڽڵ�������DAGͼ��
			lnode = &nodes[node_list.find(q.para1)->second];//lnodeָ���Ǹ�node
		}
		//�ж�ָ���Ƿ��ǵ�Ŀ�����
		if (q.op == "=" || q.op == "PRINT") {
			const int index = in_DAG(nodes, q.op, lnode, nullptr);
			if (-1 != index) {//���������Ľڵ�
				node_list[q.result] = index;
			} else {//�����������Ľڵ㣬�Ǿ��½�һ��
				DAG_node *node = new DAG_node(q.op, lnode, nullptr, q.result, node_cnt);//����Ǹ�ֵ��val���Ǳ����Ʒ��ţ������print��val����""
				node_list[q.result] = node_cnt++;
				nodes.push_back(*node);
			}
			continue;//��Ŀ������������
		}
		//�ҽڵ�
		if (node_list.find(q.para2) == node_list.end()) {//�Ҳ����ڽڵ���������DAGͼ��
			const int rnode_cnt = node_cnt++;
			if (Translator::isnum(q.para2) || q.para2[0] == '$')
				rnode = new DAG_node(q.para2, nullptr, nullptr, "", rnode_cnt);
			else
				rnode = new DAG_node(q.para2 + "0", nullptr, nullptr, "", rnode_cnt);
			node_list[q.para2] = rnode_cnt;//�ڵ�����ǲ��ü�0��
			nodes.push_back(*rnode);
		} else {//��ʽ�Ҳ��ڽڵ�������DAGͼ��
			rnode = &nodes[node_list.find(q.para2)->second];//rnodeָ���Ǹ�node
		}
		//���Žڵ�
		const int index = in_DAG(nodes, q.op, lnode, rnode);
		if (-1 != index) {//�ҵ��������Ľڵ�
			node_list[q.result] = index;
		} else {//û�ҵ����Ǿ��½�һ��
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

void Intermediate_code::generate(map<string, int> node_list, vector<DAG_node> nodes, int node_cnt) {

}

