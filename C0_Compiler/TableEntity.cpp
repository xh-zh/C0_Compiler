#include "StdAfx.h"
#include "TableEntity.h"


TableEntity::TableEntity(void)
{
	name = "";
	addr = 0;
	_class = _CLASS::NONE_CLASS;
	type = kinds::null;
	value = 0;
	dim = 0;
	parent = "";
}

TableEntity::TableEntity(const string name, const int addr, const _CLASS _class, const kinds type, const int value, const int dim , const string parent) {
	this->name = name;
	this->addr = addr;
	this->_class = _class;
	this->type = type;
	this->value = value;
	this->dim = dim;
	this->parent = parent;
	this->address_descriptor.push_back(int2str(addr));
}


TableEntity::~TableEntity(void)
{
}
