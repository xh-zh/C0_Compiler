#pragma once
#include "Quaternion.h"

class Intermediate_code
{
public:
	static vector<Quaternion> code;
	Intermediate_code(void);
	~Intermediate_code(void);
	static void push_back(Quaternion q);
	static void print(char *path);
};

