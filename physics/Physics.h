#ifndef PHYSICS_H
#define PHYSICS_H

#include "Havok.h"
#include "../resource.h"

class Physics
{
private:
	hkpWorld* world;

	hkpRigidBody* cubeShape[OBJ_NUM];
	int obj_num_cnt;
	hkpRigidBody* platformShape;
public:
	Physics(void);
	~Physics(void);

	hkpWorld* GetPhysicsWorld(){return world;}
	void SetUp(void);
	
	void Simulate(float secTime);
	void TidyUp(void);
	void addPlane(void);
	void addCuboid(float posX = 0.0f, float posY = 10.0f, float posZ = 0.0f, float halfX =1.f, float halfY = 1.f, float halfZ = 1.f);
	
	hkVector4 getPlatPosition();
	hkVector4 getCubePosition(int _index);
	void setCubePosition(const hkVector4& newPos, int _index);
};

#endif