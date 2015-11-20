#include <iostream>
using namespace std;
//오브젝트들 정보 담을 클래스
class Object_info{
private:
	float cpx, cpy, cpz;
	float sx, sy, sz;
	string entity_name, mesh_name, initial;

public:
	Object_info();
	~Object_info();

	void set_obj(float _cpx, float _cpy, float _cpz, float _sx, float _sy, float _sz, const char* _entity_name, const char* _mesh_name, const char* _initial);
	
	float getcpx();
	float getcpy();
	float getcpz();
	float getsx();
	float getsy();
	float getsz();
	string getentityname();
	string getmeshname();
	string getinitial();
};

class Gui_info{
private:
	string entity_name, mesh_name;
	float px, py;
	float sx, sy;
	

public:
	Gui_info();
	~Gui_info();

	void set_obj(float _px, float _py, float _sx, float _sy, const char* _entity_name, const char* _mesh_name);

	float getpx();
	float getpy();
	float getsx();
	float getsy();
	string getentityname();
	string getmeshname();
};
