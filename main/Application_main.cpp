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
	
	cli.run_client();
}

void Application_main::destroyScene(void){
	physics.TidyUp();
	BaseApplication::destroyScene();
}


bool Application_main::frameRenderingQueued(const Ogre::FrameEvent& evt){
	bool ret = BaseApplication::frameRenderingQueued(evt);
	//���� �ǽð����� �������ִ� �κ��ΰŰ���
	cli.transfer();
	//��Ʈ��ũ�� ���⿡ ������ ���������� �Ѵ�
	//�������� ��ǥ �޾ƿ;� �Ʒ����� �ٲ�..����?

	if (!processUnbufferedInput(evt))
		return false;

	//���⿡ ���� �浹ó�� �־���߰ڴ� ��ȭ���ΰ� ���ǵ帮���� ��ü�浹�� ���� ������������ �״� �����ϰ� ����
	//for (int i = 1; i < OBJ_NUM; i++){//2 ��� ���߿� OBJ_NUM�̰� ���ߵ�
	//	//pos[i] = ObjNode[i]->getPosition();

	//	//if ((pos[PLAYER].x - pos[i].x)*(pos[PLAYER].x - pos[i].x) <100.0)
	//	if (ObjSectionNum[PLAYER] == ObjSectionNum[i])
	//		physics.Simulate(evt.timeSinceLastFrame);
	//}
	physics.Simulate(evt.timeSinceLastFrame);

	//�ش� �浹�ڽ��� ���ų��� ���� �ؼ� ������ �Ǵ°Ű���

	//�̰Ŵ� ���߿� ����ġ�� ���� �ؼ� ���� �÷��̾��� �������ҵ�

	//��Ʈ��ũ�U ���׶����� ����
	//Ogre::Vector3 ppos(cli.ax, cli.ay, cli.az);
	//ObjNode[cli.other_num]->setPosition(ppos);
	//hkVector4 pp(ObjNode[cli.other_num]->getPosition().x, ObjNode[cli.other_num]->getPosition().y, ObjNode[cli.other_num]->getPosition().z);//�浹�ڽ� �̵��κ�
	//physics.setCubePosition(pp, cli.other_num);

	for (int i = 0; i < OBJ_NUM; i++){//2 ��� ���߿� OBJ_NUM�̰� ���ߵ�
		
		p[i] = physics.getCubePosition(i);
		pos[i] = Ogre::Vector3(p[i](0), p[i](1), p[i](2));
		ObjNode[i]->setPosition(pos[i]);

		if (pos[i].y < 2)
		{
			hkVector4 ps(pos[i].x, 100.0f, pos[i].z);
			physics.setCubePosition(ps , i);
		}

		/*for (int sx = -5; sx < 5; sx++){
			if (sx*SIZE_SECTION < pos[i].x <= (sx + 1)*SIZE_SECTION){
				for (int sz = -5; sz < 5; sz++){
					if (sz*SIZE_SECTION < pos[i].z <= (sz + 1)*SIZE_SECTION)
						ObjSectionNum[i] = sx + 100 * sz;
				}
			}
		}*/
	}
	
	return BaseApplication::frameRenderingQueued(evt);
}
void Application_main::set_obj(){
	callLua("lua_loader_o", lua_loader_o, "..\\resource\\set_obj.lua");//������ ���� �̸� ��ƽ�ũ��Ʈ���� �ϴ� ��ǥ������ �޾ƿ�

	physics.SetUp();//�������� �¾�

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


	//��Ʒ� �ҷ����ΰ� ��������Ʈ�� ����
	for (int i = 0; i < OBJ_NUM; i++){
		physics.addCuboid(obj_info[i].getcpx(), obj_info[i].getcpy(), obj_info[i].getcpz());//�̰� �� ������Ʈ�� �Ѱ��� ������ϴ°Ű���...xyz��ġ,�浹�ڽ�xyzũ�������ִµ�

		Ogre::Entity* ogreCube = mSceneMgr->createEntity(obj_info[i].getentityname(), obj_info[i].getmeshname());
		ObjNode[i] = mSceneMgr->getRootSceneNode()->createChildSceneNode(obj_info[i].getinitial());
		ObjNode[i]->setPosition(0, 0, 0);
		
		ObjNode[i]->attachObject(ogreCube);
		ObjNode[i]->scale(obj_info[i].getsx(), obj_info[i].getsy(), obj_info[i].getsz());

		p[i] = physics.getCubePosition(i);//�ش� �浹�ڽ��� �·Ḧ �ҷ���
		pos[i] = Ogre::Vector3(p[i](0), p[i](1), p[i](2));//�� �·Ḧ ���ų�忡 �Է�
		ObjNode[i]->setPosition(pos[i]);//����
	}


	//���콺 Ŀ����, �� Ŭ�� �̺�Ʈ, �׷��� ��������
}
void Application_main::set_button(){
	callLua("lua_loader_u", lua_loader_u, "..\\resource\\set_ui.lua");//������ ���� �̸� ��ƽ�ũ��Ʈ���� �ϴ� ��ǥ������ �޾ƿ�
	// you must set this on your camera, or any changes to the resolution or fov will mess up the alignment of any buttonMeshes.
	mCamera->setAutoAspectRatio(true);
	//create a text scheme
	textScheme myTextScheme("vipond", 20, 0, 1, 0, 1);
	//instance the buttonManager
	buttonMgr = new buttonGUI::buttonManager("myTextAreaMaterial", myTextScheme, mSceneMgr, "MainCam");
	ShowCursor(true);
	buttonMgr->setCursor("cursorMat5", 50, 50, 3, 3);

	//create a button
	for (int i = 0; i < UI_NUM; i++){
		buttonMgr->createButton(gui_info[i].getentityname(), gui_info[i].getmeshname(), buttonPosition(TOP_RIGHT, gui_info[i].getpx(), gui_info[i].getpy()), gui_info[i].getsx(), gui_info[i].getsy());
	}
	
	buttonMgr->resetScreenResolution();
}

void Application_main::event_button(){

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

	if (ObjNode[cli.player_num]->getPosition().y >= 0.0f)
	{
		//������Ʈ �̵� �Ŀ� �ݸ��� �̵��ؾ��Ѵ�..
		//��Ʈ��ũ�� ���׶����� ����
		//cli.set_pos(ObjNode[cli.player_num]->getPosition().x, ObjNode[cli.player_num]->getPosition().y, ObjNode[cli.player_num]->getPosition().z);
		//mSceneMgr->getSceneNode("HeadNode")->translate(//������Ʈ �̵��κ� 
		//	dirVec * fe.timeSinceLastFrame,
		//	Ogre::Node::TS_LOCAL);

		//hkVector4 p(ObjNode[cli.player_num]->getPosition().x, ObjNode[cli.player_num]->getPosition().y, ObjNode[cli.player_num]->getPosition().z);//�浹�ڽ� �̵��κ�
		//physics.setCubePosition(p, cli.player_num);

		cli.set_pos(ObjNode[PLAYER]->getPosition().x, ObjNode[PLAYER]->getPosition().y, ObjNode[PLAYER]->getPosition().z);
		mSceneMgr->getSceneNode("HeadNode")->translate(//������Ʈ �̵��κ� 
			dirVec * fe.timeSinceLastFrame,
			Ogre::Node::TS_LOCAL);

		hkVector4 p(ObjNode[PLAYER]->getPosition().x, ObjNode[PLAYER]->getPosition().y, ObjNode[PLAYER]->getPosition().z);//�浹�ڽ� �̵��κ�
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
			app.go();//���������� ��ƽ�ũ��Ʈ �ε� �� �� �״��� ������ �ݺ���
		
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
