#include "Physics.h"

Physics::Physics(void)
{
	obj_num_cnt = 0;
}


Physics::~Physics(void)
{
}

void Physics::SetUp(void)
{
	// Perfrom platform specific initialization for this demo - you should already have something similar in your own code.
	//PlatformInit();

	// Need to have memory allocated for the solver. Allocate 1mb for it.
	hkMemoryRouter* memoryRouter = hkMemoryInitUtil::initDefault( hkMallocAllocator::m_defaultMallocAllocator, hkMemorySystem::FrameInfo(1024 * 1024) );
	hkBaseSystem::init( memoryRouter, errorReport );

	{
		world = new hkpWorld( hkpWorldCinfo() );

		// Register all collision agents
		// It's important to register collision agents before adding any entities to the world.
		hkpAgentRegisterUtil::registerAllAgents( world->getCollisionDispatcher() );
	}

}

void Physics::Simulate(float secTime){
	if(secTime>0.00001)// time of zero causes an exception 
		world->stepDeltaTime(secTime);
}

void Physics::TidyUp(void){

	// Release the reference on the world
	world->removeReference();

	hkBaseSystem::quit();
	hkMemoryInitUtil::quit();
}

void Physics::addPlane(void){
	//hkpRigidBody* rigidBody;
	
	// Create a box 1 by 2 by 3
	hkVector4 halfExtents; halfExtents.set(100.f, 1.f, 100.f);
	hkpBoxShape* boxShape = new hkpBoxShape(halfExtents);
		
	hkpRigidBodyCinfo bodyCinfo;
		
	bodyCinfo.m_motionType = hkpMotion::MOTION_FIXED;
	bodyCinfo.m_qualityType = HK_COLLIDABLE_QUALITY_FIXED;// default collision quality

	bodyCinfo.m_shape = boxShape;
	bodyCinfo.m_position = hkVector4(0.0f, -1.0f, 0.0f);

	// Create the rigid body
	platformShape = new hkpRigidBody(bodyCinfo);

	// No longer need the reference on the boxShape, as the rigidBody now owns it
	boxShape->removeReference();
	

	// Add the rigidBody to the world
	world->addEntity(platformShape);

	// No longer need the ref of rigidBody - as the world now owns it
	//rigidBody->removeReference();
}

void Physics::addCuboid(float posX, float posY, float posZ, float halfX, float halfY, float halfZ){
	
	hkVector4 pos(posX, posY, posZ);
	//hkpRigidBody* rigidBody;

	// Create a box 1 by 2 by 3
	hkVector4 halfExtents; halfExtents.set(halfX, halfY, halfZ);
	hkpBoxShape* boxShape = new hkpBoxShape(halfExtents);

	hkpRigidBodyCinfo bodyCinfo;
	bodyCinfo.m_motionType = hkpMotion::MOTION_DYNAMIC;
	bodyCinfo.m_qualityType = HK_COLLIDABLE_QUALITY_CHARACTER;// default collision quality

	bodyCinfo.m_shape = boxShape;
	bodyCinfo.m_position = pos;

	//  Calculate the mass properties for the shape
	const hkReal boxMass = 100.0f;
	hkMassProperties massProperties;
	hkpInertiaTensorComputer::computeShapeVolumeMassProperties(boxShape, boxMass, massProperties);

	bodyCinfo.setMassProperties(massProperties);

	// Create the rigid body
	cubeShape[obj_num_cnt] = new hkpRigidBody(bodyCinfo);

	// No longer need the reference on the boxShape, as the rigidBody now owns it
	boxShape->removeReference();
	
		
	// Add the rigidBody to the world
	world->addEntity(cubeShape[obj_num_cnt]);
	++obj_num_cnt;//왜이런지는 모르겠으나 메인에서 셋팅할때 불러오는 순서가 달라서 그런거같다 onc++ 이렇게하면 안되더라

	// No longer need the ref of rigidBody - as the world now owns it
	//rigidBody->removeReference();
}

void Physics::addHead(float posX, float posY, float posZ, float halfX, float halfY, float halfZ){

	hkVector4 pos(posX, posY, posZ);
	//hkpRigidBody* rigidBody;

	// Create a box 1 by 2 by 3
	hkVector4 halfExtents; halfExtents.set(halfX, halfY, halfZ);
	hkpBoxShape* boxShape = new hkpBoxShape(halfExtents);

	hkpRigidBodyCinfo bodyCinfo;
	bodyCinfo.m_motionType = hkpMotion::MOTION_DYNAMIC;//여기는 뭔가 충돌시 모션이랑 그 퀄리티를 정하는거같다
	bodyCinfo.m_qualityType = HK_COLLIDABLE_QUALITY_CHARACTER;// default collision quality

	bodyCinfo.m_shape = boxShape;
	bodyCinfo.m_position = pos;

	//  Calculate the mass properties for the shape
	const hkReal boxMass = 0.1f;//질량인데 충돌시 움직이는거에 영향 끼치겠지?
	hkMassProperties massProperties;
	hkpInertiaTensorComputer::computeShapeVolumeMassProperties(boxShape, boxMass, massProperties);

	bodyCinfo.setMassProperties(massProperties);

	// Create the rigid body
	headShape = new hkpRigidBody(bodyCinfo);

	// No longer need the reference on the boxShape, as the rigidBody now owns it
	boxShape->removeReference();


	// Add the rigidBody to the world
	world->addEntity(headShape);

	// No longer need the ref of rigidBody - as the world now owns it
	//rigidBody->removeReference();
}

//아래는 게터세터임 오거노드에 붙일때 그 충돌박스 좌표주고 움직일때 충돌박스위치를 오거노드 위치로 해줄때 씀
hkVector4 Physics::getCubePosition(int _index)
{
	return cubeShape[_index]->getPosition();
}

void Physics::setCubePosition(const hkVector4& newPos, int _index)
{
	cubeShape[_index]->setPosition(newPos);
}

hkVector4 Physics::getPlatPosition()
{
	return platformShape->getPosition();
}

hkVector4 Physics::getHeadPosition()
{
	return headShape->getPosition();
}

void Physics::setHeadPosition(const hkVector4& newPos)
{
	headShape->setPosition(newPos);
}