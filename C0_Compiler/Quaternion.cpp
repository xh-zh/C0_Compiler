#include "StdAfx.h"
#include "Quaternion.h"


Quaternion::Quaternion(const string op, const string para1, const string para2, const string result)
{
	this->op = op;
	this->para1 = para1;
	this->para2 = para2;
	this->result = result;
}


Quaternion::~Quaternion()
{
}
