#include "Lua_loader.h"

Object_info::Object_info(){
	cpx = cpy = cpz = sx = sy = sz = 0.0f;
	entity_name = mesh_name = initial = "";
}
Object_info::~Object_info(){}

void Object_info::set_obj(float _cpx, float _cpy, float _cpz, float _sx, float _sy, float _sz, const char* _entity_name, const char* _mesh_name, const char* _initial)
{
	cpx = _cpx;	cpy = _cpy;	 cpz = _cpz;
	sx = _sx;	sy = _sy;	sz = _sz;
	entity_name = _entity_name;	mesh_name = _mesh_name;	initial = _initial;
}

float Object_info::getcpx(){
	return cpx;
}
float Object_info::getcpy(){
	return cpy;
}
float Object_info::getcpz(){
	return cpz;
}
float Object_info::getsx(){
	return sx;
}
float Object_info::getsy(){
	return sy;
}
float Object_info::getsz(){
	return sz;
}
const char* Object_info::getentityname(){
	return entity_name;
}
const char* Object_info::getmeshname(){
	return mesh_name;
}
const char* Object_info::getinitial(){
	return initial;
}

