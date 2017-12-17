#include "StdAfx.h"
#include "Intermediate_code.h"

vector<Quaternion> Intermediate_code::code;
Intermediate_code::Intermediate_code(void)
{
}


Intermediate_code::~Intermediate_code(void)
{
}

void Intermediate_code::push_back(Quaternion q) {
	code.push_back(q);
}

void Intermediate_code::print(char* path) {
	ofstream out(path);
	for (vector<Quaternion>::iterator iter = code.begin(); iter != code.end(); ++iter) {
		out << iter->op << "\t" << iter->para1 << "\t" << iter->para2 << "\t" << iter->result << endl;
	}
}
