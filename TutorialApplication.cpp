/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
___                 __    __ _ _    _ 
/___\__ _ _ __ ___  / / /\ \ (_) | _(_)
//  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
|___/                              
Tutorial Framework
http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/

#pragma comment(lib,"user32")
#include "TutorialApplication.h"


void TutorialApplication::callLua(const char* func_name, lua_CFunction func, const char* lua_file_name){

	/*luaL_openlibs(LS);

	lua_register(LS, func_name, func);
	luaL_dofile(LS, lua_file_name);

	lua_close(LS);*/
	LS = luaL_newstate();
	LS = lua_open();

	luaL_openlibs(LS);
	//lua_register(g_pLuaSt, "Lua_Avr_Sum", Lua_Avr_Sum);
	lua_register(LS, func_name, func);


	//luaL_dofile(g_pLuaSt, "sample.lua");
	luaL_dofile(LS, lua_file_name);
	lua_close(LS);
}

TutorialApplication::TutorialApplication(void){}

TutorialApplication::~TutorialApplication(void){}

void TutorialApplication::createScene(void)
{
	physics.SetUp();

	//add plane physically, then graphically
	physics.addPlane();

	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

	Ogre::Light* pointLight = mSceneMgr->createLight("PointLight");
	pointLight->setType(Ogre::Light::LT_POINT);
	pointLight->setPosition(250, 150, 250);
	pointLight->setDiffuseColour(Ogre::ColourValue::White);
	pointLight->setSpecularColour(Ogre::ColourValue::White);

	

	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
	entGround->setMaterialName("Examples/Rockwall");
	entGround->setCastShadows(false);
	
	physics.addCuboid(obj_info[0].getcpx(), obj_info[0].getcpy(), obj_info[0].getcpz());//�̰� �� ������Ʈ�� �Ѱ��� ������ϴ°Ű���...xyz��ġ,�浹�ڽ�xyzũ�������ִµ�

	Ogre::Entity* ogreCube = mSceneMgr->createEntity("Head", "ogrehead.mesh");
	cubeNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode");
	cubeNode->setPosition(0, 0, 0);

	cubeNode->attachObject(ogreCube);
	cubeNode->scale(obj_info[0].getsx(), obj_info[0].getsy(), obj_info[0].getsz());
	hkVector4 p(0, 0, 0);//�Ϻ��� ��ǥ
	p = physics.getCubePosition();//�ش� �浹�ڽ��� �·Ḧ �ҷ���
	Ogre::Vector3 pos = Ogre::Vector3(p(0), p(1), p(2));//�� �·Ḧ ���ų�忡 �Է�
	cubeNode->setPosition(pos);//����
	//add cube physically, then graphically
	//physics.addCuboid(5, 10, 0);//�̰� �� ������Ʈ�� �Ѱ��� ������ϴ°Ű���...xyz��ġ,�浹�ڽ�xyzũ�������ִµ�

	//Ogre::Entity* ogreCube = mSceneMgr->createEntity("Head", "ogrehead.mesh");
	//cubeNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode");
	//cubeNode->setPosition(5,10,0);

	//cubeNode->attachObject(ogreCube);
	//cubeNode->scale(0.02, 0.02, 0.02);
	//hkVector4 p(0,0,0);//�Ϻ��� ��ǥ
	//p = physics.getCubePosition();//�ش� �浹�ڽ��� �·Ḧ �ҷ���
	//Ogre::Vector3 pos = Ogre::Vector3(p(0),p(1),p(2));//�� �·Ḧ ���ų�忡 �Է�
	//cubeNode->setPosition(pos);//����

	//���콺 Ŀ����, �� Ŭ�� �̺�Ʈ, �׷��� ��������
	//�� �ٸ� �浹�ڽ��� ��� ����
	physics.addHead(0, 5, 0);

	Ogre::Entity* ninjaEntity = mSceneMgr->createEntity("ninja.mesh");
	ninjaNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("NinjaNode");
	ninjaNode->setPosition(0, 5, 0);

	ninjaNode->attachObject(ninjaEntity);
	ninjaNode->scale(0.02, 0.02, 0.02);
	hkVector4 p2(0,0,0);
	p2 = physics.getHeadPosition();
	Ogre::Vector3 pos2 = Ogre::Vector3(p2(0),p2(1), p2(2));
	ninjaNode->setPosition(pos2);
	

	// Create a Light and set its position

	Ogre::Light* light = mSceneMgr->createLight("MainLight");

	light->setPosition(20.0f, 80.0f, 50.0f);

	//ui
	set_button();


	//sound
	sound.set_sound();
}

void TutorialApplication::destroyScene(void){
	physics.TidyUp();
	BaseApplication::destroyScene();
}


bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& evt){
	bool ret = BaseApplication::frameRenderingQueued(evt);

	if (!processUnbufferedInput(evt))
		return false;

	physics.Simulate(evt.timeSinceLastFrame);
	//���� �ǽð����� �������ִ� �κ��ΰŰ���
	//�ش� �浹�ڽ��� ���ų��� ���� �ؼ� ������ �Ǵ°Ű���
	hkVector4 p(0,0,0);
	p = physics.getCubePosition();
	Ogre::Vector3 pos = Ogre::Vector3(p(0),p(1),p(2));
	cubeNode->setPosition(pos);

	hkVector4 p2(0, 0, 0);
	p2 = physics.getHeadPosition();
	Ogre::Vector3 pos2 = Ogre::Vector3(p2(0), p2(1), p2(2));
	ninjaNode->setPosition(pos2);


	return BaseApplication::frameRenderingQueued(evt);
}

void TutorialApplication::set_button(){
	// you must set this on your camera, or any changes to the resolution or fov will mess up the alignment of any buttonMeshes.
	mCamera->setAutoAspectRatio(true);
	//create a text scheme
	textScheme myTextScheme("vipond", 20, 0, 1, 0, 1);
	//instance the buttonManager
	buttonMgr = new buttonGUI::buttonManager("myTextAreaMaterial", myTextScheme, mSceneMgr, "MainCam");
	buttonMgr->showCursor();
	buttonMgr->createButton("cursor5", "cursorMat5", buttonPosition(TOP_RIGHT, 30, 200), 32, 32);
	buttonMgr->setCursor("cursorMat5", 50, 50, 200, 400);

	//create a button
	buttonMgr->createButton("building", "buildingMat", buttonPosition(TOP_RIGHT, 50, 400), 64, 64);


	buttonMgr->createButton("buildingOn", "buildingMat.onClick", buttonPosition(TOP_RIGHT, 100, 400), 64, 64);
	
	buttonMgr->createButton("textFieldAnim1", "darkInput.mouseOver", buttonPosition(TOP_RIGHT, 100, 300),256, 32);
	buttonMgr->createButton("textFieldAnim2", "darkInput.mouseOver", buttonPosition(TOP_RIGHT, 100, 200), 256, 32);
	buttonMgr->createButton("textFieldAnim3", "darkInput.mouseOver", buttonPosition(TOP_RIGHT, 100, 100), 256, 32);
	
	buttonMgr->resetScreenResolution();
}

//do something with the event
void TutorialApplication::handleButtonEvent(buttonEvent * e)
{
	std::string name;
	if (e->actionButton)
		name = *(e->actionButton->getName());  //store the name of the main button.

	if ((e->action == ONCLICK) && (name == "building"))
	{
		buttonMgr->createButton("dinoButton", "dinoMat", buttonPosition(TOP_RIGHT, 50, 600), 256, 256);
		//do stuff...
	}
}

bool TutorialApplication::processUnbufferedInput(const Ogre::FrameEvent& fe)
{
	//���� �Է¹��ۺκ��ε� Ű���� �Է��̳� ���콺 �Է� �����κ��̴�.

	static bool mouseDownLastFrame = false;
	static Ogre::Real toggleTimer = 0.0;
	static Ogre::Real rotate = .13;
	static Ogre::Real move = 10.0f;

	if (mouseCursor == false)
	{
		// First toggle method
		bool leftMouseDown = mMouse->getMouseState().buttonDown(OIS::MB_Left);

		if (leftMouseDown && !mouseDownLastFrame)
		{
			Ogre::Light* light = mSceneMgr->getLight("PointLight");
			light->setVisible(!light->isVisible());
		}

		mouseDownLastFrame = leftMouseDown;

		// Second toggle method
		toggleTimer -= fe.timeSinceLastFrame;

		if ((toggleTimer < 0) && mMouse->getMouseState().buttonDown(OIS::MB_Right))
		{
			toggleTimer = .5;

			Ogre::Light* light = mSceneMgr->getLight("PointLight");
			light->setVisible(!light->isVisible());
		}
	}

	// Moving the Ninja
	Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;
	if (mKeyboard->isKeyDown(OIS::KC_I))
		dirVec.z -= move;

	if (mKeyboard->isKeyDown(OIS::KC_K))
		dirVec.z += move;

	if (mKeyboard->isKeyDown(OIS::KC_U))
		dirVec.y += move;

	if (mKeyboard->isKeyDown(OIS::KC_O))
		dirVec.y -= move;

	if (mKeyboard->isKeyDown(OIS::KC_J))
	{
		if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			mSceneMgr->getSceneNode("HeadNode")->yaw(Ogre::Degree(5 * rotate));
		else
			dirVec.x -= move;
	}

	if (mKeyboard->isKeyDown(OIS::KC_L))
	{
		if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			mSceneMgr->getSceneNode("HeadNode")->yaw(Ogre::Degree(-5 * rotate));
		else
			dirVec.x += move;
	}
	/*hkVector4 p(0, 0, 0);
	p = physics.getCubePosition();
	Ogre::Vector3 pos = Ogre::Vector3(p(0), p(1), p(2));
	cubeNode->setPosition(pos);*/

	//hkVector4 p(cubeNode->getPosition().x + dirVec.x * fe.timeSinceLastFrame, cubeNode->getPosition().y + dirVec.y * fe.timeSinceLastFrame, cubeNode->getPosition().z + dirVec.z * fe.timeSinceLastFrame);
	if (cubeNode->getPosition().y >= 0.0f)
	{
		//������Ʈ �̵� �Ŀ� �ݸ��� �̵��ؾ��Ѵ�..
		mSceneMgr->getSceneNode("HeadNode")->translate(//������Ʈ �̵��κ� 
			dirVec * fe.timeSinceLastFrame,
			Ogre::Node::TS_LOCAL);

		hkVector4 p(cubeNode->getPosition().x, cubeNode->getPosition().y, cubeNode->getPosition().z);//�浹�ڽ� �̵��κ�
		physics.setCubePosition(p);
	}
	
	//ui update
	buttonEvent * e = buttonMgr->getEvent();			//THE FOLLOWING LOOP IS HOW TO GET EVENTS FROM buttonGUI

	while (e)
	{
		handleButtonEvent(e);
		e = buttonMgr->getEvent();
	}
	buttonMgr->update();

	return true;
}


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
	int main(int argc, char *argv[])
#endif
	{
		// Create application object
		TutorialApplication app;

		try {
			app.callLua("lua_loader", lua_loader, "set_obj.lua");//������ ���� �̸� ��ƽ�ũ��Ʈ���� �ϴ� ��ǥ������ �޾ƿ�
			app.go();//�״��� ������ �ݺ���
		
		} catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
			std::cerr << "An exception has occured: " <<
				e.getFullDescription().c_str() << std::endl;
#endif
		}

		return 0;
	}

#ifdef __cplusplus
}
#endif
