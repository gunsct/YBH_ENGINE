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
#include "Application_main.h"


void Application_main::callLua(const char* func_name, lua_CFunction func, const char* lua_file_name){

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

Application_main::Application_main(void){}

Application_main::~Application_main(void){}

void Application_main::createScene(void)
{
	//background sound
	sound.backgroud(1.0f);
	//obj setting
	set_obj();

	//ui
	set_button();
	
	
}

void Application_main::destroyScene(void){
	physics.TidyUp();
	BaseApplication::destroyScene();
}


bool Application_main::frameRenderingQueued(const Ogre::FrameEvent& evt){
	bool ret = BaseApplication::frameRenderingQueued(evt);

	if (!processUnbufferedInput(evt))
		return false;

	physics.Simulate(evt.timeSinceLastFrame);
	//여긴 실시간으로 갱신해주는 부분인거같다
	//해당 충돌박스랑 오거노드랑 같이 해서 놓으면 되는거같음

	for (int i = 0; i < OBJ_NUM; i++){//2 대신 나중에 OBJ_NUM이게 들어가야되
		p[i] = physics.getCubePosition(i);
		pos[i] = Ogre::Vector3(p[i](0), p[i](1), p[i](2));
		ObjNode[i]->setPosition(pos[i]);
	}

	return BaseApplication::frameRenderingQueued(evt);
}
void Application_main::set_obj(){
	callLua("lua_loader", lua_loader, "..\\resource\\set_obj.lua");//랜더링 전에 미리 루아스크립트에서 싹다 좌표같은거 받아옴

	physics.SetUp();//물리엔진 셋업

	//add plane physically, then graphically
	physics.addPlane();

	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
	entGround->setMaterialName("Examples/Rockwall");
	entGround->setCastShadows(false);

	// Create a Light and set its position
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

	Ogre::Light* pointLight = mSceneMgr->createLight("PointLight");
	pointLight->setType(Ogre::Light::LT_POINT);
	pointLight->setPosition(250, 150, 250);
	pointLight->setDiffuseColour(Ogre::ColourValue::White);
	pointLight->setSpecularColour(Ogre::ColourValue::White);

	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(20.0f, 80.0f, 50.0f);


	//루아로 불러들인것 헤드오브젝트들 생성
	for (int i = 0; i < OBJ_NUM; i++){
		physics.addCuboid(obj_info[i].getcpx(), obj_info[i].getcpy(), obj_info[i].getcpz());//이건 한 오브젝트에 한개씩 해줘야하는거같다...xyz위치,충돌박스xyz크기정해주는듯

		Ogre::Entity* ogreCube = mSceneMgr->createEntity(obj_info[i].getentityname(), obj_info[i].getmeshname());
		ObjNode[i] = mSceneMgr->getRootSceneNode()->createChildSceneNode(obj_info[i].getinitial());
		ObjNode[i]->setPosition(0, 0, 0);

		ObjNode[i]->attachObject(ogreCube);
		ObjNode[i]->scale(obj_info[i].getsx(), obj_info[i].getsy(), obj_info[i].getsz());

		p[i] = physics.getCubePosition(i);//해당 충돌박스의 좌료를 불러옴
		pos[i] = Ogre::Vector3(p[i](0), p[i](1), p[i](2));//그 좌료를 오거노드에 입력
		ObjNode[i]->setPosition(pos[i]);//셋팅
	}


	//마우스 커서랑, 뭐 클릭 이벤트, 그런거 공부하자
}
void Application_main::set_button(){
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
void Application_main::handleButtonEvent(buttonEvent * e)
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

bool Application_main::processUnbufferedInput(const Ogre::FrameEvent& fe)
{
	//여긴 입력버퍼부분인데 키보드 입력이나 마우스 입력 구현부분이다.

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
			sound.effect(CRASH, 1.0f);
		}

		mouseDownLastFrame = leftMouseDown;

		// Second toggle method
		toggleTimer -= fe.timeSinceLastFrame;

		if ((toggleTimer < 0) && mMouse->getMouseState().buttonDown(OIS::MB_Right))
		{
			toggleTimer = .5;

			Ogre::Light* light = mSceneMgr->getLight("PointLight");
			light->setVisible(!light->isVisible());
			sound.effect(ALARM, 1.0f);
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

	if (ObjNode[PLAYER]->getPosition().y >= 0.0f)
	{
		//오브젝트 이동 후에 콜리더 이동해야한다..
		mSceneMgr->getSceneNode("HeadNode")->translate(//오브젝트 이동부분 
			dirVec * fe.timeSinceLastFrame,
			Ogre::Node::TS_LOCAL);

		hkVector4 p(ObjNode[PLAYER]->getPosition().x, ObjNode[PLAYER]->getPosition().y, ObjNode[PLAYER]->getPosition().z);//충돌박스 이동부분
		physics.setCubePosition(p, PLAYER);
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
		Application_main app;

		try {
			app.go();//씬생성에서 루아스크립트 로드 다 함 그다음 랜더링 반복함
		
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
