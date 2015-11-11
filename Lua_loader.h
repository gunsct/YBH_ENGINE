//오브젝트들 정보 담을 클래스
class Object_info{
private:
	float cpx, cpy, cpz;
	float sx, sy, sz;
	const char *entity_name, *mesh_name, *initial;

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
	const char* getentityname();
	const char* getmeshname();
	const char* getinitial();
};


